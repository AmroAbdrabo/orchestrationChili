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
 * @file AxialHexCoords.cpp
 * @brief Source for a hexagonal tile axial coordinates definition
 * @author Ayberk Özgür
 * @date 2018-05-16
 */

#include "AxialHexCoords.h"

namespace Cellulo{

AxialHexCoords::AxialHexCoords(QQuickItem* parent) : QQuickItem(parent){
    physicalWidth = PHYSICAL_WIDTH_DEFAULT;
    connect(this, SIGNAL(physicalWidthChanged()), this, SIGNAL(physicalHeightChanged()));

    q = 0;
    r = 0;
}

AxialHexCoords::~AxialHexCoords(){}

void AxialHexCoords::setPhysicalWidth(float physicalWidth){
    if(physicalWidth > 0){
        this->physicalWidth = physicalWidth;
        emit physicalWidthChanged();
    }
    else
        qCritical() << "AxialHexCoords::setPhysicalWidth(): Physical width must be positive!";
}

void AxialHexCoords::setQ(int q){
    this->q = q;
    emit qChanged();
}

void AxialHexCoords::setR(int r){
    this->r = r;
    emit rChanged();
}

QVector2D AxialHexCoords::hexOffset(){
    return physicalWidth*QVector2D(
        (float)q + (float)r*0.5f,
        (float)r*0.86602540378443864676f //sqrt(3)/2
    );
}

}
