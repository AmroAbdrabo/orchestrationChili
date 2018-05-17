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
    QVector2D position = pose.toVector2D();
    HexTile* tile = getTile(position);

    //Position is on a known tile
    if(tile){
        QVector2D resultSourcePosition = tile->sourceCoordinates(position);
        processKnownTile(resultSourcePosition, tile->getCoords());

        QVector3D resultPose = (resultSourcePosition + tile->getCoords()->hexOffset()).toVector3D();
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

void HexTileMap::processKnownTile(QVector2D const& sourcePosition, AxialHexCoords* coords){
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
    autoBuildKnownHistory.append(sourcePosition);
    if(autoBuildKnownHistory.size() > autoBuildKnownHistorySize)
        autoBuildKnownHistory.removeFirst();
}

QVector3D HexTileMap::processUnknownTile(QVector3D const& pose){
    QVector2D position = pose.toVector2D();

    //Get the standard tile coords of the unknown position
    HexTileStandardCoords* newUnknownStdCoords = new HexTileStandardCoords();
    if(newUnknownStdCoords->estimateFromCoords(position)){

        //Update old std coords if necessary and position history
        if(autoBuildUnknownStdCoords){
            if(autoBuildUnknownStdCoords->equals(*newUnknownStdCoords)){
                delete newUnknownStdCoords;
                autoBuildUnknownHistory.append(position);
                if(autoBuildUnknownHistory.size() > autoBuildUnknownHistorySize)
                    autoBuildUnknownHistory.removeFirst();
            }
            else{
                delete autoBuildUnknownStdCoords;
                autoBuildUnknownStdCoords = newUnknownStdCoords;
                autoBuildUnknownHistory.clear();
                autoBuildUnknownHistory.append(position);
            }
        }
        else{
            autoBuildUnknownStdCoords = newUnknownStdCoords;
            autoBuildUnknownHistory.clear();
            autoBuildUnknownHistory.append(position);
        }

        //This is the first tile ever, assume q=0 and r=0
        if(!autoBuildKnownCoordsExist){
            HexTile* imaginaryTile = new HexTile(); //No need for screen rendering now, no need for parent
            //imaginaryTile->setQ(0); imaginaryTile->setR(0); //No need for these, default coordinates are 0,0
            imaginaryTile->setStandardCoords(autoBuildUnknownStdCoords);
            QVector3D result = (imaginaryTile->sourceCoordinates(position) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
            result.setZ(pose.z());

            //Add this tile
            if(autoBuild && autoBuildUnknownHistory.size() >= autoBuildUnknownHistorySize){
                autoBuildUnknownStdCoords = nullptr; //Detach std coords from the map, rests only with tile
                imaginaryTile->setParent(this);
                imaginaryTile->setParentItem(this); //Child added detection will call addTile()
                //addTile(imaginaryTile);
                resetAutoBuild();
            }
            else
                delete imaginaryTile;

            return result;
        }
        else{
            float minDist = std::numeric_limits<float>::infinity();
            QVector<QVector2D> edgeMids;
            autoBuildKnownCoords.edgeMidList(edgeMids);
            int deltaQ = 0;
            int deltaR = 0;
            float dist;

            //Detect by closest exit edge
            //Order: top-left, left, bottom-left, bottom-right, right, top-right
            static QVector<int> deltaQs = {0,   -1, -1, 0,  1,  1};
            static QVector<int> deltaRs = {-1,  0,  1,  1,  0,  -1};
            static QVector<QVector2D> deltaHalfSegs = {
                0.5f*autoBuildExitSegWidth*QVector2D(-0.5f,                                     0.86602540378443864676f /* sqrt(3)/2 */),
                0.5f*autoBuildExitSegWidth*QVector2D(0.0f,                                      -1.0f),
                0.5f*autoBuildExitSegWidth*QVector2D(-0.86602540378443864676f /* sqrt(3)/2 */,  -0.5f),
                0.5f*autoBuildExitSegWidth*QVector2D(-0.86602540378443864676f /* sqrt(3)/2 */,  0.5f),
                0.5f*autoBuildExitSegWidth*QVector2D(0.0,                                       1.0f),
                0.5f*autoBuildExitSegWidth*QVector2D(0.86602540378443864676f /* sqrt(3)/2 */,   0.5f)
            };
            for(int i=0;i<6;i++){
                dist = CelluloMathUtil::pointToSegmentDist(autoBuildKnownHistory.last(), edgeMids[i] + deltaHalfSegs[i], edgeMids[i] - deltaHalfSegs[i]);
                if(dist < minDist){
                    minDist = dist;
                    if(dist < autoBuildExitMargin){
                        deltaQ = deltaQs[i];
                        deltaR = deltaRs[i];
                    }
                }
            }
            if(deltaQ != 0 || deltaR != 0){

                //First estimate new position on this imaginary tile
                HexTile* imaginaryTile = new HexTile(); //No need for screen rendering now, no need for parent
                imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + deltaQ);
                imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + deltaR);
                imaginaryTile->setStandardCoords(autoBuildUnknownStdCoords);
                QVector3D result = (imaginaryTile->sourceCoordinates(position) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
                result.setZ(pose.z());

                //Consider adding this tile
                if(autoBuild && autoBuildUnknownHistory.size() >= autoBuildUnknownHistorySize){
                    autoBuildUnknownStdCoords = nullptr; //Detach std coords from the map, rests only with tile
                    imaginaryTile->setParent(this);
                    imaginaryTile->setParentItem(this); //Child added detection will call addTile()
                    //addTile(imaginaryTile);
                    resetAutoBuild();
                }
                else
                    delete imaginaryTile;

                return result;
            }

            //Exit cannot be detected through closeness to edge, try to detect through exit ray
            else{
                qDebug() << "Trying ray intersection...";

                if(autoBuildKnownHistory.size() < 2){
                    qDebug() << "Too few known points";
                    return QVector3D(0,0,0);
                }

                //Get main direction
                QVector2D mainVec = autoBuildKnownHistory.last() - autoBuildKnownHistory.first();
                if(mainVec.length() < autoBuildMinVecSize){
                    qDebug() << "mainVec too short";
                    return QVector3D(0,0,0);
                }

                //Check if all directions agree with main direction, also get mean of all positions as origin of ray
                QVector2D origin = autoBuildKnownHistory.first();
                for(QList<QVector2D>::iterator it = autoBuildKnownHistory.begin() + 1; it != autoBuildKnownHistory.end(); it++){
                    QVector2D vec = *it - *(it - 1);
                    if(vec.length() > autoBuildMinVecSize)
                        if(CelluloMathUtil::angleBetween(mainVec, vec) > autoBuildMinVecAngle){
                            qDebug() << "Angles don't agree";
                            return QVector3D(0,0,0);
                        }

                    origin += *it;
                }
                origin /= autoBuildKnownHistory.length();

                //Intersect exit ray with all edges
                for(int i=0;i<6;i++)
                    if(CelluloMathUtil::rayCrossesLineSeg(origin, mainVec, edgeMids[i] + deltaHalfSegs[i], edgeMids[i] - deltaHalfSegs[i])){
                        deltaQ = deltaQs[i];
                        deltaR = deltaRs[i];
                        qDebug() << "crosses at " << i;
                        break;
                    }

                //Exit cannot be detected...
                if(deltaQ == 0 && deltaR == 0)
                    return QVector3D(0,0,0);

                //First estimate new position on this imaginary tile
                HexTile* imaginaryTile = new HexTile(); //No need for screen rendering now, no need for parent
                imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + deltaQ);
                imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + deltaR);
                imaginaryTile->setStandardCoords(autoBuildUnknownStdCoords);
                QVector3D result = (imaginaryTile->sourceCoordinates(position) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
                result.setZ(pose.z());

                //Consider adding this tile if unknown tile ray edge intersection also agrees with the known tile ray
                if(autoBuild && autoBuildUnknownHistory.size() >= autoBuildUnknownHistorySize){

                    //Get main direction
                    QVector2D unkMainVec = autoBuildUnknownHistory.last() - autoBuildUnknownHistory.first();
                    if(unkMainVec.length() < autoBuildMinVecSize){
                        qDebug() << "Unknown mainVec too short: " << autoBuildUnknownHistory;
                        delete imaginaryTile;
                        return result;
                    }

                    //Check if all directions agree with main direction, also get mean of all positions as origin of ray
                    QVector2D unkOrigin = autoBuildUnknownHistory.first();
                    for(QList<QVector2D>::iterator it = autoBuildUnknownHistory.begin() + 1; it != autoBuildUnknownHistory.end(); it++){
                        QVector2D vec = *it - *(it - 1);
                        if(vec.length() > autoBuildMinVecSize)
                            if(CelluloMathUtil::angleBetween(unkMainVec, vec) > autoBuildMinVecAngle){
                                qDebug() << "Unknown Angles don't agree: " << autoBuildUnknownHistory;
                                delete imaginaryTile;
                                return result;
                            }

                        unkOrigin += *it;
                    }
                    unkOrigin /= autoBuildUnknownHistory.length();

                    //Intersect entry ray with all edges
                    unkMainVec = -unkMainVec;
                    int unkDeltaQ = 0;
                    int unkDeltaR = 0;
                    for(int i=0;i<6;i++)
                        if(CelluloMathUtil::rayCrossesLineSeg(unkOrigin, unkMainVec, edgeMids[i] + deltaHalfSegs[i], edgeMids[i] - deltaHalfSegs[i])){
                            unkDeltaQ = deltaQs[i];
                            unkDeltaR = deltaRs[i];
                            qDebug() << "Unknown crosses at " << i;
                            break;
                        }

                    //Entry cannot be detected...
                    if(unkDeltaQ == 0 && unkDeltaR == 0){
                        delete imaginaryTile;
                        return result;
                    }

                    //Check whether entry and exit edges agree
                    if(unkDeltaQ == -deltaQ && unkDeltaR == -deltaR){
                        qDebug() << "Entry and exit edges agree";
                        autoBuildUnknownStdCoords = nullptr; //Detach std coords from the map, rests only with tile
                        imaginaryTile->setParent(this);
                        imaginaryTile->setParentItem(this); //Child added detection will call addTile()
                        //addTile(imaginaryTile);
                    }
                    else
                        qDebug() << "Entry and exit edges DONT agree";

                    //Reset autobuild for safety even if data doesn't work
                    resetAutoBuild();
                }
                else
                    delete imaginaryTile;

                return result;
            }
        }
    }

    //Estimate somehow failed
    else{
        delete newUnknownStdCoords;
        qCritical() << "HexTileMap::processUnknownTile(): Standard coordinate estimate somehow failed.";
        return QVector3D(0,0,0);
    }
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
