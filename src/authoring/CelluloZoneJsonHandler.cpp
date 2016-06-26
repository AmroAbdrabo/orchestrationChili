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
 * @file CelluloZoneJsonHandler.cpp
 * @brief Source for zone JSON tools
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZoneJsonHandler.h"

bool CelluloZoneJsonHandler::saveQMLZones(QList<QVariant> qmlZones, QString path, const float mmPgdWidth, const float mmPgdHeight){
    QList<CelluloZone*> zones;
    foreach (QVariant qmlZone, qmlZones) {
        CelluloZone* zone = qvariant_cast<CelluloZone*>(qmlZone);
        zones.append(zone);
    }
    return saveZones(zones, path, mmPgdWidth, mmPgdHeight);
}

bool CelluloZoneJsonHandler::saveZones(QList<CelluloZone*> zones, QString path, const float mmPgdWidth, const float mmPgdHeight){
    QFile saveFile(path);

    if(!saveFile.open(QIODevice::WriteOnly)){
        qWarning("Couldn't write into file.");
        return false;
    }

    QJsonObject authoredZonesObject;
    if(write(authoredZonesObject, zones, mmPgdWidth, mmPgdHeight)){
        QJsonDocument saveDoc(authoredZonesObject);
        saveFile.write(saveDoc.toJson());
        return true;
    }
    else{
        return false;
    }
}

QMap<QString, QVariant> CelluloZoneJsonHandler::loadQMLZones(QString path){
    return loadZones(path);
}

QMap<QString, QVariant> CelluloZoneJsonHandler::loadZones(QString path){
    QFile loadFile(path);

    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open save file.");
        return QMap<QString, QVariant>();
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    return read(loadDoc.object());
}

bool CelluloZoneJsonHandler::write(QJsonObject &json, QList<CelluloZone*> zones, const float mmPgdWidth, const float mmPgdHeight){
    QJsonObject mmPlaygroundSize;
    mmPlaygroundSize["width"] = mmPgdWidth;
    mmPlaygroundSize["height"] = mmPgdHeight;

    QJsonArray zoneArray;
    foreach (CelluloZone* zone, zones) {
        qDebug() << "Writing zone" << zone->getName() << "to json file";
        QJsonObject zoneObject;
        zone->write(zoneObject);
        zoneArray.append(zoneObject);
    }
    json["playgoundSizeInmm"] = mmPlaygroundSize;
    json["zones"] = zoneArray;

    return true;
}

QMap<QString, QVariant> CelluloZoneJsonHandler::read(const QJsonObject &json){
    QMap<QString, QVariant> readResult;
    QList<QVariant> zones;
    QJsonObject mmPlaygroundSize = json["playgoundSizeInmm"].toObject();
    double mmPlaygroundWidth = mmPlaygroundSize["width"].toDouble();
    double mmPlaygroundHeight= mmPlaygroundSize["height"].toDouble();
    if(!std::isnan(mmPlaygroundWidth)){
        readResult.insert("realPlaygroundWidth",mmPlaygroundWidth);
    }
    if(!std::isnan(mmPlaygroundHeight)){
        readResult.insert("realPlaygroundHeight",mmPlaygroundHeight);
    }
    QJsonArray zoneArray = json["zones"].toArray();
    for(int zoneIndex = 0; zoneIndex < zoneArray.size(); ++zoneIndex){
        QJsonObject zoneObject = zoneArray[zoneIndex].toObject();
        CelluloZoneTypes::ZoneType type = CelluloZoneTypes::typeFromString(zoneObject["type"].toString());

        if(type != -1){
            CelluloZone* zone;
            switch(type){
                case CelluloZoneTypes::CIRCLEINNER:
                    zone = new CelluloZoneCircleInner();
                    break;
                case CelluloZoneTypes::CIRCLEBORDER:
                    zone = new CelluloZoneCircleBorder();
                    break;
                case CelluloZoneTypes::CIRCLEDISTANCE:
                    zone = new CelluloZoneCircleDistance();
                    break;
                case CelluloZoneTypes::RECTANGLEINNER:
                    zone = new CelluloZoneRectangleInner();
                    break;
                case CelluloZoneTypes::RECTANGLEBORDER:
                    zone = new CelluloZoneRectangleBorder();
                    break;
                case CelluloZoneTypes::RECTANGLEDISTANCE:
                    zone = new CelluloZoneRectangleDistance();
                    break;
                case CelluloZoneTypes::LINEINNER:
                    zone = new CelluloZoneLineInner();
                    break;
                case CelluloZoneTypes::LINEDISTANCE:
                    zone = new CelluloZoneLineDistance();
                    break;
                case CelluloZoneTypes::POINTDISTANCE:
                    zone = new CelluloZonePointDistance();
                    break;
                case CelluloZoneTypes::RPOLYGONINNER:
                    zone = new CelluloZoneRegularPolygonInner();
                    break;
                case CelluloZoneTypes::RPOLYGONBORDER:
                    zone = new CelluloZoneRegularPolygonBorder();
                    break;
                case CelluloZoneTypes::RPOLYGONDISTANCE:
                    zone = new CelluloZoneRegularPolygonDistance();
                    break;
                case CelluloZoneTypes::IRPOLYGONINNER:
                    zone = new CelluloZoneIrregularPolygonInner();
                    break;
                case CelluloZoneTypes::IRPOLYGONBORDER:
                    zone = new CelluloZoneIrregularPolygonBorder();
                    break;
                case CelluloZoneTypes::IRPOLYGONDISTANCE:
                    zone = new CelluloZoneIrregularPolygonDistance();
                    break;
                default:
                    qDebug() << "Forgot to handle an enum case";
                    return QMap<QString, QVariant>();
                    break;
            }
            zone->read(zoneObject);
            qDebug() << "Reading zone" << zone->getName() << "from json file";
            zones.append(QVariant::fromValue(zone));
        }
        else{
            qDebug() << "Corrupted json type field";
        }
    }
    readResult.insert("zones",zones);
    return readResult;
}
