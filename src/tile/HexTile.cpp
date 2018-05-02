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

    standardCoords = NULL;

    connect(this, SIGNAL(standardCoordsChanged()), this, SLOT(updateFromStandardCoords()));
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

void HexTile::setStandardCoords(Cellulo::HexTileStandardCoords* standardCoords){
    if(standardCoords != this->standardCoords){
        if(this->standardCoords)
            this->standardCoords->disconnectHexTileChangedSignals(this);
        this->standardCoords = standardCoords;
        if(this->standardCoords)
            this->standardCoords->connectHexTileChangedSignals(this);
        emit standardCoordsChanged();
    }
}

void HexTile::updateFromStandardCoords(){
    if(standardCoords){
        float sourceLeft = standardCoords->getI()*210.0f;
        float sourceRight = sourceLeft;
        float sourceTop = standardCoords->getJ()*260.0f;
        float sourceBottom = sourceTop;
        float sourceCenterX;
        float sourceCenterY;

        if(standardCoords->getU() == 0){
            sourceLeft += 0.0f;
            sourceRight += 105.7f;
            sourceCenterX = 54.3f;
        }
        else{ // == 1
            sourceLeft += 105.7f;
            sourceRight += 210.0f;
            sourceCenterX = 50.0f;
        }

        if(standardCoords->getV() == 0){
            sourceTop += 0.0f;
            sourceBottom += 130.0f;
            sourceCenterY = 67.0f;
        }
        else{ // == 1
            sourceTop += 130.0f;
            sourceBottom += 260.0f;
            sourceCenterY = 67.0f;
        }

        if(this->sourceLeft != sourceLeft){
            this->sourceLeft = sourceLeft;
            emit sourceLeftChanged();
        }
        if(this->sourceRight != sourceRight){
            this->sourceRight = sourceRight;
            emit sourceRightChanged();
        }
        if(this->sourceTop != sourceTop){
            this->sourceTop = sourceTop;
            emit sourceTopChanged();
        }
        if(this->sourceBottom != sourceBottom){
            this->sourceBottom = sourceBottom;
            emit sourceBottomChanged();
        }
        if(this->sourceCenterX != sourceCenterX){
            this->sourceCenterX = sourceCenterX;
            emit sourceCenterXChanged();
        }
        if(this->sourceCenterY != sourceCenterY){
            this->sourceCenterY = sourceCenterY;
            emit sourceCenterYChanged();
        }
    }
}

}
