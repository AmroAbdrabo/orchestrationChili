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

CelluloZonePaintedItem::CelluloZonePaintedItem(QQuickItem* parent) : QQuickPaintedItem(parent){
    associatedZone = NULL;
}

void CelluloZonePaintedItem::paint(QPainter* painter){
    if(associatedZone)
        associatedZone->paint(painter, boundingRect().width(), boundingRect().height());
    else
        qWarning() << "CelluloZonePaintedItem::paint(): No associatedZone set.";
}
