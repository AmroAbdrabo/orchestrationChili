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
  * @file CelluloZonePaintedItem.cpp
  * @brief Source for a QML compatible QQuickPaintedItem for Cellulo zones
  * @author Ayberk Özgür
  * @date 2016-06-28
  */

#include "CelluloZonePaintedItem.h"

#include <QVariant>

CelluloZonePaintedItem::CelluloZonePaintedItem(QQuickItem* parent) : QQuickPaintedItem(parent){
    associatedZone = NULL;

    if(parent){
        connect(parent, SIGNAL(widthChanged()), this, SLOT(parentWidthChanged()));
        connect(parent, SIGNAL(heightChanged()), this, SLOT(parentHeightChanged()));
        setWidth(parent->width());
        setHeight(parent->height());
    }
    else
        qWarning() << "CelluloZonePaintedItem::CelluloZonePaintedItem(): CelluloZonePaintedItem must be initialized with a parent.";
}

void CelluloZonePaintedItem::parentWidthChanged(){
    setWidth(parentItem()->width());
    qDebug() << "setting width...";
}

void CelluloZonePaintedItem::parentHeightChanged(){
    setHeight(parentItem()->height());
    qDebug() << "setting height...";
}

/**
 * @brief Sets the associated zone
 *
 * @param associatedZone The CelluloZone that will take care of painting
 */
void CelluloZonePaintedItem::setAssociatedZone(CelluloZone* zone){
    if(associatedZone != zone){
        associatedZone = zone;
        emit associatedZoneChanged();

        /*QVariant scaleCoeffVariant = parent()->property("scaleCoeff");
        if(scaleCoeffVariant.isValid()){
            qreal scaleCoeff = scaleCoeffVariant.value<qreal>();
            setX(100*scaleCoeff);
            setY(100*scaleCoeff);
            setWidth(100*scaleCoeff);
            setWidth(100*scaleCoeff);
        }
        else
            qWarning() << "CelluloZonePaintedItem::paint(): Parent of CelluloZonePaintedItem must contain a real scaleCoeff property.";*/
    }
}

void CelluloZonePaintedItem::paint(QPainter* painter){
    if(associatedZone){
        qDebug() << "painting";
        associatedZone->paint(painter, width(), height());
    }
    else
        qWarning() << "CelluloZonePaintedItem::paint(): No associatedZone set.";
}
