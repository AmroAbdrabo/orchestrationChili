/*
 * Copyright (C) 2016 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file HexTileMap.cpp
 * @brief Source for a hexagonal multi-tile map
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#include "HexTileMap.h"

#include "HexTile.h"
#include "../util/math/CelluloMathUtil.h"

#include <QDebug>
#include <limits>

namespace Cellulo{

HexTileMap::HexTileMap(QQuickItem* parent) : PoseRemapper(parent),
    toScreenSize(this),
    toScreenCoords(this)
{
    autoBuild = false;
    autoBuildKnownCoordsExist = false;
    autoBuildUnknownStdCoords = nullptr;

    physicalTopLeft = QVector2D(-50.0f, -57.73502691896257645092f);
    physicalSize = QVector2D(100.0f, 115.47005383792515290183f);

    connect(this, SIGNAL(widthChanged()),           this, SLOT(updateToScreenSize()));
    connect(this, SIGNAL(heightChanged()),          this, SLOT(updateToScreenSize()));
    connect(this, SIGNAL(physicalSizeChanged()),    this, SLOT(updateToScreenSize()));

    connect(this, SIGNAL(widthChanged()),           this, SLOT(updateToScreenCoords()));
    connect(this, SIGNAL(heightChanged()),          this, SLOT(updateToScreenCoords()));
    connect(this, SIGNAL(physicalSizeChanged()),    this, SLOT(updateToScreenCoords()));
    connect(this, SIGNAL(physicalTopLeftChanged()), this, SLOT(updateToScreenCoords()));

    connect(this, SIGNAL(toScreenSizeChanged()),    this, SIGNAL(markedDirty()));
    connect(this, SIGNAL(toScreenCoordsChanged()),  this, SIGNAL(markedDirty()));
}

HexTileMap::~HexTileMap(){ }

void HexTileMap::setPhysicalSize(QVector2D const& physicalSize){
    if(physicalSize.x() > 0 && physicalSize.y() > 0){
        this->physicalSize = physicalSize;
        emit physicalSizeChanged();
    }
    else
        qCritical() << "HexTileMap::setPhysicalSize(): Physical size must have positive width and height!";
}

void HexTileMap::setPhysicalTopLeft(QVector2D const& physicalTopLeft){
    this->physicalTopLeft = physicalTopLeft;
    emit physicalTopLeftChanged();
}

void HexTileMap::setAutoBuild(bool autoBuild){
    if(this->autoBuild != autoBuild){
        this->autoBuild = autoBuild;
        if(autoBuild)
            resetAutoBuild();
        emit autoBuildChanged();
    }
}

void HexTileMap::itemChange(ItemChange change, const ItemChangeData& value){
    if(change == ItemChange::ItemChildAddedChange){
        HexTile* newTile = qobject_cast<HexTile*>(value.item);
        if(newTile)
            addTile(newTile);
    }

    QQuickItem::itemChange(change, value);
}

void HexTileMap::updateToScreenSize(){
    toScreenSize.setInputSize(physicalSize);
    toScreenSize.setOutputSize(QVector2D(width(), height()));
    emit toScreenSizeChanged();
}

void HexTileMap::updateToScreenCoords(){
    toScreenCoords.setInputSize(physicalSize);
    toScreenCoords.setInputOrigin(physicalTopLeft);
    toScreenCoords.setOutputSize(QVector2D(width(), height()));
    toScreenCoords.setOutputOrigin(QVector2D(0, 0));
    emit toScreenCoordsChanged();
}

QVector3D HexTileMap::remapPose(QVector3D const& pose){
    QVector2D sourcePosition = pose.toVector2D();
    HexTile* tile = getTile(sourcePosition);

    //Position is on a known tile
    if(tile){
        QVector2D resultPosition = tile->sourceCoordinates(sourcePosition) + tile->getCoords()->hexOffset();
        processKnownTile(resultPosition, tile->getCoords());

        QVector3D resultPose = resultPosition.toVector3D();
        resultPose.setZ(pose.z());
        return resultPose;
    }

    //Unknown tile encountered
    else
        return processUnknownTile(pose);
}

void HexTileMap::resetAutoBuild(){
    autoBuildKnownHistory.clear();
    autoBuildUnknownHistory.clear();
    autoBuildKnownCoordsExist = false;
    if(autoBuildUnknownStdCoords){
        delete autoBuildUnknownStdCoords;
        autoBuildUnknownStdCoords = nullptr;
    }
}

void HexTileMap::processKnownTile(QVector2D const& position, AxialHexCoords* coords){
    if(autoBuildKnownCoordsExist){
        if(autoBuildKnownCoords.getQ() != coords->getQ() || autoBuildKnownCoords.getR() != coords->getR()){
            autoBuildKnownCoords.copyFrom(*coords);
            autoBuildKnownHistory.clear();
        }
    }
    else{
        autoBuildKnownCoordsExist = true;
        autoBuildKnownCoords.copyFrom(*coords);
    }
    autoBuildKnownHistory.append(position);
    if(autoBuildKnownHistory.size() > autoBuildKnownHistorySize)
        autoBuildKnownHistory.removeFirst();
}

QVector3D HexTileMap::processUnknownTile(QVector3D const& sourcePose){
    QVector2D sourcePosition = sourcePose.toVector2D();
    QVector3D result(0,0,0);

    //Get the standard tile coords of the unknown position
    HexTileStandardCoords* newUnknownStdCoords = new HexTileStandardCoords();
    if(newUnknownStdCoords->estimateFromCoords(sourcePosition)){

        //Update old std coords if necessary and position history
        if(autoBuildUnknownStdCoords){
            if(autoBuildUnknownStdCoords->equals(*newUnknownStdCoords)){
                delete newUnknownStdCoords;
                autoBuildUnknownHistory.append(sourcePosition);
                if(autoBuildUnknownHistory.size() > autoBuildUnknownHistorySize)
                    autoBuildUnknownHistory.removeFirst();
            }
            else{
                delete autoBuildUnknownStdCoords;
                autoBuildUnknownStdCoords = newUnknownStdCoords;
                autoBuildUnknownHistory.clear();
                autoBuildUnknownHistory.append(sourcePosition);
            }
        }
        else{
            autoBuildUnknownStdCoords = newUnknownStdCoords;
            autoBuildUnknownHistory.clear();
            autoBuildUnknownHistory.append(sourcePosition);
        }

        //Build imaginary tile
        HexTile* imaginaryTile = new HexTile(); //No need for screen rendering now, no need for parent
        imaginaryTile->setStandardCoords(autoBuildUnknownStdCoords);

        //This is the first tile ever, assume q=0 and r=0
        if(!autoBuildKnownCoordsExist){
            result = (imaginaryTile->sourceCoordinates(sourcePosition) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
            result.setZ(sourcePose.z());

            //Add this tile
            if(autoBuild && autoBuildUnknownHistory.size() >= autoBuildUnknownHistorySize){
                autoBuildUnknownStdCoords = nullptr; //Detach std coords from the map, rests only with imaginaryTile
                imaginaryTile->setParent(this);
                imaginaryTile->setParentItem(this); //Child added detection will call addTile(), no need to call here
                resetAutoBuild();
            }
            else
                delete imaginaryTile;
        }

        //There are existing tiles
        else{
            QVector<QVector2D> corners;
            autoBuildKnownCoords.cornerList(corners);
            int deltaQ = 0;
            int deltaR = 0;
            static QVector<int> deltaQs = {0,   -1, -1, 0,  1,  1};
            static QVector<int> deltaRs = {-1,  0,  1,  1,  0,  -1};

            if(autoBuildKnownHistory.length() >= 2){

                //Detect raycast exit to estimate unknown coordinates for a short while
                //Order: top-left, left, bottom-left, bottom-right, right, top-right
                QVector2D origin(0,0);
                for(QVector2D const& vec : autoBuildKnownHistory)
                    origin += vec;
                origin /= autoBuildKnownHistory.length();
                QVector2D mainVec = autoBuildKnownHistory.last() - autoBuildKnownHistory.first();
                for(int i=0;i<6;i++)
                    if(CelluloMathUtil::rayCrossesLineSeg(origin, mainVec, corners[i], corners[(i + 1) % 6])){
                        deltaQ = deltaQs[i];
                        deltaR = deltaRs[i];
                        break;
                    }
                imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + deltaQ);
                imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + deltaR);
                result = (imaginaryTile->sourceCoordinates(sourcePosition) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
                result.setZ(sourcePose.z());
            }

            //Enough samples on the known and unknown tiles, pick best direction
            if(autoBuild && autoBuildUnknownHistory.size() >= autoBuildUnknownHistorySize && autoBuildKnownHistory.size() >= autoBuildKnownHistoryMinSize){

                //Directions on the known tile
                QList<QVector2D> knownVecs;
                for(auto it = autoBuildKnownHistory.begin() + 1; it != autoBuildKnownHistory.end(); it++){
                    QVector2D vec = *it - *(it - 1);
                    if(vec.length() > autoBuildMinVecSize)
                        knownVecs.append(vec);
                }

                //Directions on the unknown tile calculated from the raw source coordinates, will result in the same if calculated from remapped coordinates
                QList<QVector2D> unknownVecs;
                for(auto it = autoBuildUnknownHistory.begin() + 1; it != autoBuildUnknownHistory.end(); it++){
                    QVector2D vec = *it - *(it - 1);
                    if(vec.length() > autoBuildMinVecSize)
                        unknownVecs.append(vec);
                }

                float bestScore = std::numeric_limits<float>::infinity();
                deltaQ = 0;
                deltaR = 0;
                for(int i=0;i<6;i++){
                    float hypotDeltaQ = deltaQs[i];
                    float hypotDeltaR = deltaRs[i];
                    imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + hypotDeltaQ);
                    imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + hypotDeltaR);

                    //Passage direction from the known tile to the unknown tile
                    QVector2D fromKnownToUnknownDir =
                        (imaginaryTile->sourceCoordinates(autoBuildUnknownHistory.first()) + imaginaryTile->getCoords()->hexOffset()) - autoBuildKnownHistory.last();

                    //Score is the sum of angles between all direction pairs, minimum score wins
                    float score = 0;
                    for(auto it = knownVecs.begin(); it != knownVecs.end(); it++){

                        //Known-known pairs
                        for(auto jt = it + 1; jt != knownVecs.end(); jt++)
                            score += CelluloMathUtil::angleBetween(*it, *jt);

                        //Known-passage pairs
                        score += CelluloMathUtil::angleBetween(*it, fromKnownToUnknownDir);

                        //Known-unknown pairs
                        for(auto jt = unknownVecs.begin(); jt != unknownVecs.end(); jt++)
                            score += CelluloMathUtil::angleBetween(*it, *jt);
                    }
                    for(auto it = unknownVecs.begin(); it != unknownVecs.end(); it++){

                        //Passage-unknown pairs
                        score += CelluloMathUtil::angleBetween(*it, fromKnownToUnknownDir);

                        //Unknown-unknown pairs
                        for(auto jt = it + 1; jt != unknownVecs.end(); jt++)
                            score += CelluloMathUtil::angleBetween(*it, *jt);
                    }
                    if(score < bestScore){
                        bestScore = score;
                        deltaQ = hypotDeltaQ;
                        deltaR = hypotDeltaR;
                    }
                }

                //Add tile
                if(deltaQ != 0 || deltaR != 0){
                    imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + deltaQ);
                    imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + deltaR);
                    result = (imaginaryTile->sourceCoordinates(sourcePosition) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
                    result.setZ(sourcePose.z());
                    //TODO: TRANSFER UNKNOWN TO KNOWN
                    autoBuildUnknownStdCoords = nullptr; //Detach std coords from the map, rests only with imaginaryTile
                    imaginaryTile->setParent(this);
                    imaginaryTile->setParentItem(this); //Child added detection will call addTile(), no need to call here
                }
                resetAutoBuild();
            }
            else
                delete imaginaryTile;
        }
    }

    //Estimate somehow failed
    else{
        delete newUnknownStdCoords;
        qCritical() << "HexTileMap::processUnknownTile(): Standard coordinate estimate somehow failed.";
    }

    return result;
}

HexTile* HexTileMap::getTile(int q, int r){
    //TODO: More efficient lookup by axial coords possible?
    for(auto const& tileVariant : tiles){
        HexTile* tile = tileVariant.value<HexTile*>();
        if(tile){
            if(tile->getCoords()->getQ() == q && tile->getCoords()->getR() == r)
                return tile;
        }
        else
            qCritical() << "HexTileMap::remapPose(): tiles can only contain HexTile type!";
    }
    return nullptr;
}

HexTile* HexTileMap::getTile(QVector2D const& position){
    //TODO: More efficient lookup by standard source coords!!!
    for(auto const& tileVariant : tiles){
        HexTile* tile = tileVariant.value<HexTile*>();
        if(tile){
            if(tile->sourceContains(position))
                return tile;
        }
        else
            qCritical() << "HexTileMap::remapPose(): tiles can only contain HexTile type!";
    }
    return nullptr;
}

void HexTileMap::addTile(HexTile* newTile){
    if(!tiles.contains(QVariant::fromValue(newTile))){
        removeTile(newTile->getCoords()->getQ(), newTile->getCoords()->getR());
        tiles.append(QVariant::fromValue(newTile));
        emit tileAdded(newTile);
    }
    else
        qInfo() << "HexTileMap::addNewTile(): Not adding already existing identical tile.";
}

bool HexTileMap::removeTile(HexTile* oldTile){
    //TODO: More efficient lookup by axial coords possible?
    for(QVariantList::iterator tileVariantIt = tiles.begin(); tileVariantIt != tiles.end(); tileVariantIt++){
        HexTile* tile = (*tileVariantIt).value<HexTile*>();
        if(tile){
            if(tile == oldTile){
                tiles.erase(tileVariantIt);
                emit tileRemoved(tile->getCoords()->getQ(), tile->getCoords()->getR());
                tile->deleteLater();
                resetAutoBuild(); //Too expensive to check whether this tile was involved with autobuild...
                return true;
            }
        }
        else
            qCritical() << "HexTileMap::removeTile(): tiles can only contain HexTile type!";
    }
    return false;
}

bool HexTileMap::removeTile(int q, int r){
    //TODO: More efficient lookup by axial coords possible?
    for(QVariantList::iterator tileVariantIt =  tiles.begin(); tileVariantIt != tiles.end(); tileVariantIt++){
        HexTile* tile = (*tileVariantIt).value<HexTile*>();
        if(tile){
            if(tile->getCoords()->getQ() == q && tile->getCoords()->getR() == r){
                tiles.erase(tileVariantIt);
                emit tileRemoved(q, r);
                tile->deleteLater();
                resetAutoBuild(); //Too expensive to check whether this tile was involved with autobuild...
                return true;
            }
        }
        else
            qCritical() << "HexTileMap::removeTile(): tiles can only contain HexTile type!";
    }
    return false;
}

void HexTileMap::clearTiles(){
    for(QVariantList::iterator tileVariantIt = tiles.begin(); tileVariantIt != tiles.end(); tileVariantIt++){
        HexTile* tile = (*tileVariantIt).value<HexTile*>();
        if(tile){
            tiles.erase(tileVariantIt);
            emit tileRemoved(tile->getCoords()->getQ(), tile->getCoords()->getR());
            tile->deleteLater();
        }
        else
            qCritical() << "HexTileMap::removeTile(): tiles can only contain HexTile type!";
    }
    resetAutoBuild();
}

}
