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
 * @file CelluloZoneJsonHandler.h
 * @brief Header for zone JSON tools
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONEJSONHANDLER_H
#define CELLULOZONEJSONHANDLER_H

#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "src/zones/CelluloZone.h"
#include "src/zones/CelluloZoneCircle.h"
#include "src/zones/CelluloZoneRectangle.h"
#include "src/zones/CelluloZoneLine.h"
#include "src/zones/CelluloZonePoint.h"
#include "src/zones/CelluloZonePolygon.h"

class CelluloZoneJsonHandler : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /**
     * @brief Save zones in JSON file from QML side
     *
     * @param qmlZones zones to be saved from QML world
     * @param path path of the JSON file where to save the zones
     * @param mmPgdWidth width of real playground in mm
     * @param mmPgdHeight height of real playground in mm
     *
     * @return  true if operation was successful, 0 otherwise
     */
    Q_INVOKABLE static bool saveQMLZones(QList<QVariant> qmlZones, QString path, const float mmPgdWidth, const float mmPgdHeight);

    /**
     * @brief Load zones from JSON file from QML side
     *
     * @param path path of the JSON file where to load the zones
     *
     * @return  map containing playground size (width and height) under "playgoundSizeInmm" and retrieved zones under "zones"
     */
    Q_INVOKABLE static QMap<QString, QVariant> loadQMLZones(QString path);

    /**
     * @brief Save zones in JSON file from QT side
     *
     * @param zones zones to be saved from QML world
     * @param path path of the JSON file where to save the zones
     * @param mmPgdWidth width of real playground in mm
     * @param mmPgdHeight height of real playground in mm
     *
     * @return true if operation was successful, 0 otherwise
     */
    bool static saveZones(QList<CelluloZone*> zones, QString path, const float mmPgdWidth, const float mmPgdHeight);

    /**
     * @brief Load zones from JSON file from QML side
     *
     * @param path path of the JSON file where to load the zones
     *
     * @return map containing playground size (width and height) under "playgoundSizeInmm" and retrieved zones under "zones"
     */
    QMap<QString, QVariant> static loadZones(QString path);

private:

    /**
     * @brief write write function to serialise member variables
     *
     * @param json json object to be filled
     * @param zones zones to serialize
     * @param mmPgdWidth width of real playground in mm
     * @param mmPgdHeight height of real playground in mm
     *
     * @return true if operation was successful, 0 otherwise
     */
    bool static write(QJsonObject &json, QList<CelluloZone*> zones, const float mmPgdWidth, const float mmPgdHeight);

    /**
     * @brief read read function to retrieved serialised member variables
     *
     * @param json json object where infor are extracted
     *
     * @return map containing playground size (width and height) under "playgoundSizeInmm" and retrieved zones under "zones"
     */
    QMap<QString, QVariant> static read(const QJsonObject &json);

};

#endif // CELLULOZONEJSONHANDLER_H
