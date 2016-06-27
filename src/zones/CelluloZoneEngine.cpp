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

CelluloZoneEngine::CelluloZoneEngine(QQuickItem* parent) : QQuickItem(parent){
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
        emit zonesChanged();
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

QVariantList CelluloZoneEngine::getZonesList(){
    QVariantList variantList;
    for(const auto& zone : zones)
        variantList.append(QVariant::fromValue(zone));
    return variantList;
}

void CelluloZoneEngine::addNewZones(QList<CelluloZone*> newZones){
    for(const auto& zone : newZones)
        addNewZone(zone);
}

void CelluloZoneEngine::addNewZones(QVariantList newZones){
    for(const auto& zone : newZones)
        addNewZone(zone.value<CelluloZone*>());
}
