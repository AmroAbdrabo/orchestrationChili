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

#include <QDebug>


namespace Cellulo{

HexTileMap::HexTileMap(QQuickItem* parent) : PoseRemapper(parent),
    toScreenSize(this),
    toScreenCoords(this)
{
    autoBuild = false;
    autoBuildKnownCoordsExist = false;

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
        if(newTile){






            //TODO: BETTER STORAGE
            if(!tiles.contains(QVariant::fromValue(newTile)))
                tiles.append(QVariant::fromValue(newTile));











            //addNewZone(newTile);
            qDebug() << "HexTileMap::itemChange(): Child tile " << /*newTile->getName()*/ "" << " automatically added.";
        }
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









    //TODO: REPLACE LOOKUP WITH HASH<HASH<TILE>>
    //Lookup of existing tiles
    for(auto const& tileVariant : tiles){
        HexTile* tile = tileVariant.value<HexTile*>();
        if(tile){
            if(tile->sourceContains(position)){
                QVector2D resultPosition = tile->sourceCoordinates(position) + tile->hexOffset();
                processKnownTile(resultPosition, tile->getQ(), tile->getR());

                QVector3D resultPose = resultPosition.toVector3D();
                resultPose.setZ(pose.z());
                return resultPose;
            }
        }
        else
            qCritical() << "HexTileMap::remapPose(): tiles can only contain HexTile type!";
    }

    //Unknown tile encountered
    return processUnknownTile(position);
}

void HexTileMap::resetAutoBuild(){
    autoBuildKnownHistory.clear();
    autoBuildUnknownHistory.clear();
    autoBuildKnownCoordsExist = false;
}

void HexTileMap::processKnownTile(QVector2D const& position, int q, int r){





}

QVector3D HexTileMap::processUnknownTile(QVector2D const& position){













    qCritical() << "HexTileMap::remapPose(): Unknown tile!";






    return QVector3D(0,0,0);
}



}
