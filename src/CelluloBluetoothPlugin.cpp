/*
 * Copyright (C) 2015 EPFL
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
 * @file CelluloBluetoothPlugin.cpp
 * @brief Source for exposing Cellulo Bluetooth communication as a QML object
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-20
 */

#include "CelluloBluetoothPlugin.h"



#include<QQmlEngine>

#include"CameraFrameImageProvider.h"

void CelluloBluetoothPlugin::registerTypes(const char *uri){
    qmlRegisterType<CelluloBluetooth>(uri, 1, 0, "CelluloBluetooth");

    qmlRegisterType<CelluloZoneCircleInner>(uri, 1, 0, "CelluloZoneCircleInner");
    qmlRegisterType<CelluloZoneCircleBorder>(uri, 1, 0, "CelluloZoneCircleBorder");
    qmlRegisterType<CelluloZoneCircleDistance>(uri, 1, 0, "CelluloZoneCircleDistance");

    qmlRegisterType<CelluloZoneRectangleInner>(uri, 1, 0, "CelluloZoneRectangleInner");
    qmlRegisterType<CelluloZoneRectangleBorder>(uri, 1, 0, "CelluloZoneRectangleBorder");
    qmlRegisterType<CelluloZoneRectangleDistance>(uri, 1, 0, "CelluloZoneRectangleDistance");

    qmlRegisterType<CelluloZoneLineInner>(uri, 1, 0, "CelluloZoneLineInner");
    qmlRegisterType<CelluloZoneLineDistance>(uri, 1, 0, "CelluloZoneLineDistance");

    qmlRegisterType<CelluloZonePointInner>(uri, 1, 0, "CelluloZonePointInner");
    qmlRegisterType<CelluloZonePointDistance>(uri, 1, 0, "CelluloZonePointDistance");

    qmlRegisterType<CelluloZoneIrregularPolygonInner>(uri, 1, 0, "CelluloZoneIrregularPolygonInner");
    qmlRegisterType<CelluloZoneIrregularPolygonBorder>(uri, 1, 0, "CelluloZoneIrregularPolygonBorder");
    qmlRegisterType<CelluloZoneIrregularPolygonDistance>(uri, 1, 0, "CelluloZoneIrregularPolygonDistance");

    qmlRegisterType<CelluloZoneRegularPolygonInner>(uri, 1, 0, "CelluloZoneRegularPolygonInner");
    qmlRegisterType<CelluloZoneRegularPolygonBorder>(uri, 1, 0, "CelluloZoneRegularPolygonBorder");
    qmlRegisterType<CelluloZoneRegularPolygonDistance>(uri, 1, 0, "CelluloZoneRegularPolygonDistance");


    qmlRegisterType<CelluloZoneEngine>(uri, 1, 0, "CelluloZoneEngine");
    qmlRegisterType<CelluloZoneJsonHandler>(uri, 1, 0, "CelluloZoneJsonHandler");
    qmlRegisterType<CelluloZoneTypes>(uri, 1, 0, "CelluloZoneTypes");

}

void CelluloBluetoothPlugin::initializeEngine(QQmlEngine *engine, const char *uri __attribute__((unused))){
    engine->addImageProvider("cameraFrame", new CameraFrameImageProvider());
}
