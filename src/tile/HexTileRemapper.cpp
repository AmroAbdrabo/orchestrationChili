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
 * @file HexTileRemapper.cpp
 * @brief Source for a hexagonal multi-tile remapper
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#include "HexTileRemapper.h"

#include "HexTile.h"

#include <QDebug>


namespace Cellulo{

HexTileRemapper::HexTileRemapper(QQuickItem* parent) : PoseRemapper(parent){

}

HexTileRemapper::~HexTileRemapper(){}

QVector3D HexTileRemapper::remapPose(QVector3D const& pose){
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
            qCritical() << "HexTileRemapper::remapPose(): tiles can only contain HexTile type!";
    }

    qCritical() << "HexTileRemapper::remapPose(): Unknown tile!";

    return QVector3D(0,0,0);
}

}
