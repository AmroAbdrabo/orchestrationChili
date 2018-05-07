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

HexTileMap::HexTileMap(QQuickItem* parent) : PoseRemapper(parent){
    physicalArea = QRectF(-50.0f, -57.73502691896257645092f, 100.0f, 115.47005383792515290183f);

    connect(this, SIGNAL(physicalAreaChanged()),    this, SIGNAL(markedDirty()));
    connect(this, SIGNAL(widthChanged()),           this, SIGNAL(markedDirty()));
    connect(this, SIGNAL(heightChanged()),          this, SIGNAL(markedDirty()));
}

HexTileMap::~HexTileMap(){}

void HexTileMap::setPhysicalArea(QRectF const& physicalArea){
    if(physicalArea.width() > 0 && physicalArea.height() > 0){
        this->physicalArea = physicalArea;
        emit physicalAreaChanged();
    }
    else
        qCritical() << "HexTileMap::setPhysicalArea(): Physical area must have positive width and height!";
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

QVector2D HexTileMap::toScreenSize(QVector2D const& physicalSize) const {
    return QVector2D(width()/physicalArea.width(), height()/physicalArea.height())*physicalSize;
}

QVector2D HexTileMap::toScreenCoords(QVector2D const& physicalCoords) const {
    return QVector2D(width()/physicalArea.width(), height()/physicalArea.height())*(physicalCoords - QVector2D(physicalArea.x(), physicalArea.y()));
}

QVector3D HexTileMap::remapPose(QVector3D const& pose){
    QVector2D position = pose.toVector2D();









    //TODO: REPLACE LOOKUP WITH HASH<HASH<TILE>>
    for(auto const& tileVariant : tiles){
        HexTile* tile = tileVariant.value<HexTile*>();
        if(tile){
            if(tile->sourceContains(position)){
                QVector3D result = (tile->sourceCoordinates(position) + tile->hexOffset()).toVector3D();
                result.setZ(pose.z());
                return result;
            }
        }
        else
            qCritical() << "HexTileMap::remapPose(): tiles can only contain HexTile type!";
    }

    qCritical() << "HexTileMap::remapPose(): Unknown tile!";

    return QVector3D(0,0,0);
}

}
