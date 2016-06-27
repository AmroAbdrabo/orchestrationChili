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
 * @file CelluloZoneEngine.cpp
 * @brief Source for the zone engine
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include <QTimer>
#include <QQmlProperty>
#include <QSignalMapper>

#include "CelluloZoneEngine.h"

CelluloZoneEngine::CelluloZoneEngine(QQuickItem* parent) :
    QQuickItem(parent)
{
}

CelluloZoneEngine::~CelluloZoneEngine(){
    //TODO: FIGURE OUT HOW TO DELETE CLIENTS AND ZONES IN THE LISTS, THEY MAY HAVE BEEN CREATED IN QML BY STATIC CODE
}

void CelluloZoneEngine::bindClientToZone(CelluloZoneClient* client, CelluloZone* zone){
    connect(client, SIGNAL(poseChanged(qreal,qreal,qreal)), zone, SLOT(onClientPoseChanged(qreal,qreal,qreal)));
}

void CelluloZoneEngine::addNewClient(CelluloZoneClient* newClient){
    if(clients.contains(newClient))
        qDebug() << "CelluloZoneEngine::addNewClient(): Client already exists, not adding.";
    else{
        clients += newClient;
        for(auto zone : zones)
            bindClientToZone(newClient, zone);
    }
}

void CelluloZoneEngine::addNewZone(CelluloZone* newZone){
    if(zones.contains(newZone))
        qDebug() << "CelluloZoneEngine::addNewZone(): Zone already exists, not adding.";
    else{
        zones += newZone;
        for(auto client : clients)
            bindClientToZone(client, newZone);
    }
}

void CelluloZoneEngine::itemChange(ItemChange change, const ItemChangeData& value){
    if(change == ItemChange::ItemChildAddedChange){
        CelluloZone* newZone = qobject_cast<CelluloZone*>(value.item);
        if(newZone){
            addNewZone(newZone);
            qDebug() << "CelluloZoneEngine::itemChange(): Child zone " + newZone->getName() + " automatically added.";
        }
    }

    QQuickItem::itemChange(change, value);
}

/*bool CelluloZoneEngine::addNewZoneFromJSON(QString path){
    QMap<QString, QVariant> result = CelluloZoneJsonHandler::loadZones(path);
    QList<CelluloZone*> zonesFromJSON;
    QList<QVariant> list = result["zones"].toList();
    for(int i=0; i<list.length(); i++){
        CelluloZone* zone = qvariant_cast<CelluloZone*>(list[i]);
        zonesFromJSON.append(zone);
    }
    if(zonesFromJSON.length()>0){
        foreach (CelluloZone* zone, zonesFromJSON) {
            if(zone){
                setParentToZone(zone);
                emit(newZoneCreatedReadyForVisualization(zone->getType(), zone->getRatioProperties(realPlaygroundWidth, realPlaygroundHeight), this->children().size(), vRplaygroundWidth, vRplaygroundHeight));
                double jsonRealPlaygroundWidth = qvariant_cast<double>(result["realPlaygroundWidth"]);
                if(jsonRealPlaygroundWidth){
                    if(realPlaygroundWidth != -1 && realPlaygroundWidth!=jsonRealPlaygroundWidth){
                        qDebug() << "Real width value you provided: " << realPlaygroundWidth <<"and the one from the JSON file: " << jsonRealPlaygroundWidth <<" differ. Taking JSON file value";
                    }
                    realPlaygroundWidth = jsonRealPlaygroundWidth;
                    emit realPlaygroundWidthChanged();
                }
                else{
                    qDebug() << "Problem no width of playground given by jsonHandler";
                    return false;
                }
                double jsonRealPlaygroundHeight = qvariant_cast<double>(result["realPlaygroundHeight"]);
                if(jsonRealPlaygroundHeight){
                    if(realPlaygroundHeight != -1 && realPlaygroundHeight!=jsonRealPlaygroundHeight){
                        qDebug() << "Real height value you provided: " << realPlaygroundHeight <<"and the one from the JSON file: " << jsonRealPlaygroundHeight <<" differ. Taking JSON file value";
                    }
                    realPlaygroundHeight = jsonRealPlaygroundHeight;
                    emit realPlaygroundHeightChanged();
                }
                else{
                    qDebug() << "Problem no height of playground given by jsonHandler";
                    return false;
                }
            }
            else{
                qDebug() << "Problem when casting zone from json representation";
                return false;
            }
        }
    }
    else{
        qDebug() << "Problem when loading zone with jsonHandler";
        return false;
    }

    for(int var = 0; var < this->children().size(); ++var){
        qDebug() << "zones added from JSON file" << this->children().at(var)->metaObject()->className();
    }
    return true;
}*/

QList<CelluloZone*> CelluloZoneEngine::getAllZones(){
    return zones.toList();
}

QStringList CelluloZoneEngine::getAllZoneNames(){
    QStringList zoneNames;
    for(CelluloZone* zone : zones)
        zoneNames.append(zone->getName());
    return zoneNames;
}

QObject* CelluloZoneEngine::getZoneByName(QString name){
    for(CelluloZone* zone : zones)
        if(zone->getName() == name)
            return zone;
    return NULL;
}

/*
bool CelluloZoneEngine::getAllZonesAndSaveThem(QString path){
    QList<CelluloZone*> zones = this->parent()->findChildren<CelluloZone *>();
    return CelluloZoneJsonHandler::saveZones(zones, path, realPlaygroundWidth, realPlaygroundHeight);
}*/
