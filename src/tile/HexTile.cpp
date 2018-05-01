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
 * @file HexTile.cpp
 * @brief Source for a hexagonal tile definition
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#include "HexTile.h"

#include<QDebug>

#include<cmath>

namespace Cellulo{

HexTile::HexTile(QQuickItem* parent) : QQuickItem(parent){
    q = 0;
    r = 0;
    sourceLeft = 0;
    sourceTop = 0;
    sourceRight = 0;
    sourceBottom = 0;
    sourceCenterX = 0;
    sourceCenterY = 0;
}

HexTile::~HexTile(){}

bool HexTile::sourceContains(QVector2D const& point){
    return
        sourceLeft < point.x() &&  point.x() <= sourceRight &&
        sourceTop < point.y() &&   point.y() <= sourceBottom;
}

QVector2D HexTile::hexOffset(float tileWidth){
    return tileWidth*QVector2D(
        (float)q + (float)r*0.5f,
        (float)r*0.86602540378443864676f //sqrt(3)/2
    );
}

QVector2D HexTile::sourceCoordinates(QVector2D const& point){
    return point - QVector2D(sourceLeft + sourceCenterX, sourceTop + sourceCenterY);
}

}
