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
 * @brief Source for exposing Cellulo objects as QML objects
 * @author Ayberk Özgür
 * @date 2016-06-26
 */

#include "CelluloPlugin.h"

#include <QQmlEngine>
#include <qqml.h>

#include "comm/CelluloBluetooth.h"
#include "comm/CelluloTcpRelayClient.h"
#include "comm/CelluloTcpRelayServer.h"
#include "comm/CelluloBluetoothEMP.h"
#include "comm/CelluloBluetoothEnums.h"
#include "comm/CameraFrameImageProvider.h"
#include "zones/CelluloZone.h"
#include "zones/CelluloZoneClient.h"
#include "zones/CelluloZonePolyBezier.h"
#include "zones/CelluloZonePolygon.h"
#include "zones/CelluloZonePoint.h"
#include "zones/CelluloZoneLine.h"
#include "zones/CelluloZoneCircle.h"
#include "zones/CelluloZoneRectangle.h"
#include "zones/CelluloZoneAngle.h"
#include "zones/CelluloZoneAngleInterval.h"
#include "zones/CelluloZoneEngine.h"
#include "zones/CelluloZoneJsonHandler.h"
#include "zones/CelluloZoneTypes.h"
#include "zones/CelluloZonePaintedItem.h"
#include "util/math/CelluloMathUtil.h"
#include "util/svg/CelluloSVGUtil.h"
#include "util/lang/TranslationTool.h"

void CelluloPlugin::registerTypes(const char *uri){
    qmlRegisterType<CelluloBluetooth>(uri, 1, 0, "CelluloBluetooth");
    qmlRegisterType<CelluloTcpRelayClient>(uri, 1, 0, "CelluloTcpRelayClient");
    qmlRegisterType<CelluloTcpRelayServer>(uri, 1, 0, "CelluloTcpRelayServer");
    qmlRegisterType<CelluloBluetoothEMP>(uri, 1, 0, "CelluloBluetoothEMP");

    qmlRegisterSingletonType<CelluloBluetoothEnums>(uri, 1, 0, "CelluloBluetoothEnums",
                                                    [] (QQmlEngine* qmlEngine, QJSEngine* jsEngine)->QObject* {
                                                        Q_UNUSED(qmlEngine)
                                                        Q_UNUSED(jsEngine)
                                                        return new CelluloBluetoothEnums();
                                                    });

    qmlRegisterType<CelluloZoneClient>(uri, 1, 0, "CelluloZoneClient");
    qmlRegisterType<CelluloZoneEngine>(uri, 1, 0, "CelluloZoneEngine");
    qmlRegisterSingletonType<CelluloZoneJsonHandler>(uri, 1, 0, "CelluloZoneJsonHandler",
                                                     [] (QQmlEngine* qmlEngine, QJSEngine* jsEngine)->QObject* {
                                                         Q_UNUSED(qmlEngine)
                                                         Q_UNUSED(jsEngine)
                                                         return new CelluloZoneJsonHandler();
                                                     });
    qmlRegisterSingletonType<CelluloZoneTypes>(uri, 1, 0, "CelluloZoneTypes",
                                               [] (QQmlEngine* qmlEngine, QJSEngine* jsEngine)->QObject* {
                                                   Q_UNUSED(qmlEngine)
                                                   Q_UNUSED(jsEngine)
                                                   return new CelluloZoneTypes();
                                               });

    qmlRegisterType<CelluloZoneCircleInner>(uri, 1, 0, "CelluloZoneCircleInner");
    qmlRegisterType<CelluloZoneCircleBorder>(uri, 1, 0, "CelluloZoneCircleBorder");
    qmlRegisterType<CelluloZoneCircleDistance>(uri, 1, 0, "CelluloZoneCircleDistance");

    qmlRegisterType<CelluloZoneRectangleInner>(uri, 1, 0, "CelluloZoneRectangleInner");
    qmlRegisterType<CelluloZoneRectangleBorder>(uri, 1, 0, "CelluloZoneRectangleBorder");
    qmlRegisterType<CelluloZoneRectangleDistance>(uri, 1, 0, "CelluloZoneRectangleDistance");

    qmlRegisterType<CelluloZoneAngleDifference>(uri, 1, 0, "CelluloZoneAngleDifference");

    qmlRegisterType<CelluloZoneAngleIntervalInner>(uri, 1, 0, "CelluloZoneAngleIntervalInner");
    qmlRegisterType<CelluloZoneAngleIntervalBorder>(uri, 1, 0, "CelluloZoneAngleIntervalBorder");
    qmlRegisterType<CelluloZoneAngleIntervalDistance>(uri, 1, 0, "CelluloZoneAngleIntervalDistance");

    qmlRegisterType<CelluloZoneLineSegmentDistance>(uri, 1, 0, "CelluloZoneLineSegmentDistance");
    qmlRegisterType<CelluloZoneLineDistanceSigned>(uri, 1, 0, "CelluloZoneLineDistanceSigned");
    qmlRegisterType<CelluloZoneLineBorder>(uri, 1, 0, "CelluloZoneLineBorder");

    qmlRegisterType<CelluloZonePointDistance>(uri, 1, 0, "CelluloZonePointDistance");

    qmlRegisterType<CelluloZoneIrregularPolygonInner>(uri, 1, 0, "CelluloZoneIrregularPolygonInner");
    qmlRegisterType<CelluloZoneIrregularPolygonBorder>(uri, 1, 0, "CelluloZoneIrregularPolygonBorder");
    qmlRegisterType<CelluloZoneIrregularPolygonDistance>(uri, 1, 0, "CelluloZoneIrregularPolygonDistance");

    qmlRegisterType<CelluloZoneRegularPolygonInner>(uri, 1, 0, "CelluloZoneRegularPolygonInner");
    qmlRegisterType<CelluloZoneRegularPolygonBorder>(uri, 1, 0, "CelluloZoneRegularPolygonBorder");
    qmlRegisterType<CelluloZoneRegularPolygonDistance>(uri, 1, 0, "CelluloZoneRegularPolygonDistance");

    qmlRegisterType<CelluloZonePolyBezierDistance>(uri, 1, 0, "CelluloZonePolyBezierDistance");
    qmlRegisterType<CelluloZonePolyBezierBorder>(uri, 1, 0, "CelluloZonePolyBezierBorder");
    qmlRegisterType<CelluloZonePolyBezierInner>(uri, 1, 0, "CelluloZonePolyBezierInner");

    qmlRegisterType<CelluloZonePaintedItem>(uri, 1, 0, "CelluloZonePaintedItem");

    qmlRegisterSingletonType<CelluloMathUtil>(uri, 1, 0, "CelluloMathUtil",
                                              [] (QQmlEngine* qmlEngine, QJSEngine* jsEngine)->QObject* {
                                                  Q_UNUSED(qmlEngine)
                                                  Q_UNUSED(jsEngine)
                                                  return new CelluloMathUtil();
                                              });

    qmlRegisterSingletonType<CelluloSVGUtil>(uri, 1, 0, "CelluloSVGUtil",
                                             [] (QQmlEngine* qmlEngine, QJSEngine* jsEngine)->QObject* {
                                                 Q_UNUSED(qmlEngine)
                                                 Q_UNUSED(jsEngine)
                                                 return new CelluloSVGUtil();
                                             });

    qmlRegisterType<TranslationTool>(uri, 1, 0, "TranslationTool");
}

void CelluloPlugin::initializeEngine(QQmlEngine *engine, const char *uri){
    Q_UNUSED(uri)
    engine->addImageProvider("cameraFrame", new CameraFrameImageProvider());
}
