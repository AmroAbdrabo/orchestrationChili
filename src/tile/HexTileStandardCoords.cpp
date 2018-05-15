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
 * @brief Source for a hexagonal tile standard coordinates definition
 * @author Ayberk Özgür
 * @date 2018-05-02
 */

#include "HexTileStandardCoords.h"

#include<QDebug>

#include<cmath>

namespace Cellulo{

HexTileStandardCoords::HexTileStandardCoords(QQuickItem* parent) : QQuickItem(parent){
    i = 0;
    j = 0;
    u = 0;
    v = 0;
}

HexTileStandardCoords::~HexTileStandardCoords(){}

void HexTileStandardCoords::setI(int i){
    if(i >= 0){
        if(i != this->i){
            this->i = i;
            emit iChanged();
        }
    }
    else
        qCritical() << "HexTileStandardCoords::setI(): i cannot be negative!";
}

void HexTileStandardCoords::setJ(int j){
    if(j >= 0){
        if(j != this->j){
            this->j = j;
            emit jChanged();
        }
    }
    else
        qCritical() << "HexTileStandardCoords::setJ(): j cannot be negative!";
}

void HexTileStandardCoords::setU(int u){
    if(u == 0 || u == 1){
        if(u != this->u){
            this->u = u;
            emit uChanged();
        }
    }
    else
        qCritical() << "HexTileStandardCoords::setU(): u can only be 0 or 1!";
}

void HexTileStandardCoords::setV(int v){
    if(v == 0 || v == 1){
        if(v != this->v){
            this->v = v;
            emit vChanged();
        }
    }
    else
        qCritical() << "HexTileStandardCoords::setV(): v can only be 0 or 1!";
}

void HexTileStandardCoords::connectHexTileChangedSignals(Cellulo::HexTile* tile){
    connect(this, SIGNAL(iChanged()), tile, SIGNAL(standardCoordsChanged()));
    connect(this, SIGNAL(jChanged()), tile, SIGNAL(standardCoordsChanged()));
    connect(this, SIGNAL(uChanged()), tile, SIGNAL(standardCoordsChanged()));
    connect(this, SIGNAL(vChanged()), tile, SIGNAL(standardCoordsChanged()));
}

void HexTileStandardCoords::disconnectHexTileChangedSignals(Cellulo::HexTile* tile){
    disconnect(this, SIGNAL(iChanged()), tile, SIGNAL(standardCoordsChanged()));
    disconnect(this, SIGNAL(jChanged()), tile, SIGNAL(standardCoordsChanged()));
    disconnect(this, SIGNAL(uChanged()), tile, SIGNAL(standardCoordsChanged()));
    disconnect(this, SIGNAL(vChanged()), tile, SIGNAL(standardCoordsChanged()));
}

bool HexTileStandardCoords::estimateFromCoords(QVector2D const& coords){
    if(coords.x() >= 0 && coords.y() >= 0){
        setI((int)(coords.x()/210.0));
        setJ((int)(coords.y()/260.0));
        setU((coords.x() - getI()*210.0) <= 105.7 ? 0 : 1);
        setV((coords.y() - getJ()*260.0) <= 130.0 ? 0 : 1);
        return true;
    }
    else{
        qCritical() << "HexTileStandardCoords::estimateFromCoords(): Coordinates must not be negative!";
        return false;
    }
}

bool HexTileStandardCoords::equals(HexTileStandardCoords const& other) const {
    return
        getI() == other.getI() &&
        getJ() == other.getJ() &&
        getU() == other.getU() &&
        getV() == other.getV();
}

}
