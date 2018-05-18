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
            resetAutoBuilders();
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

QVector3D HexTileMap::remapPose(QVector3D const& pose, QObject* sender){
    QVector2D sourcePosition = pose.toVector2D();
    HexTile* tile = getTile(sourcePosition);
    HexTileMapAutoBuilder* builder = autoBuilders.value(sender, nullptr);
    if(!builder){
        builder = new HexTileMapAutoBuilder(this);
        autoBuilders.insert(sender, builder);











        //connect kidnappedchanged
    }

    //Position is on a known tile
    if(tile){
        QVector2D resultPosition = tile->sourceCoordinates(sourcePosition) + tile->getCoords()->hexOffset();
        builder->processKnownTile(resultPosition, tile->getCoords());

        QVector3D resultPose = resultPosition.toVector3D();
        resultPose.setZ(pose.z());
        return resultPose;
    }

    //Unknown tile encountered
    else
        return builder->processUnknownTile(pose, autoBuild, tiles.isEmpty(), this);
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
                resetAutoBuilders(); //Too expensive to check whether this tile was involved with autobuild...
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
                resetAutoBuilders(); //Too expensive to check whether this tile was involved with autobuild...
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
    resetAutoBuilders();
}

void HexTileMap::resetAutoBuilders(){
    for(HexTileMapAutoBuilder* builder : autoBuilders)
        builder->resetAutoBuild();
}

}
