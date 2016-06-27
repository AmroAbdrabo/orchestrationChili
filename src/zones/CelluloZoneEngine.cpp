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
    vRplaygroundWidth = -1;
    vRplaygroundHeight = -1;
    realPlaygroundWidth = -1;
    realPlaygroundHeight = -1;
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

/*
bool CelluloZoneEngine::addNewZoneFromQML(int type, QVariantMap properties){
    QQuickItem *childrenItem;
    switch(type){
        case CelluloZoneTypes::CIRCLEINNER:
            childrenItem = new CelluloZoneCircleInner();
            break;
        case CelluloZoneTypes::CIRCLEBORDER:
            childrenItem = new CelluloZoneCircleBorder();
            break;
        case CelluloZoneTypes::CIRCLEDISTANCE:
            childrenItem = new CelluloZoneCircleDistance();
            break;
        case CelluloZoneTypes::RECTANGLEINNER:
            childrenItem = new CelluloZoneRectangleInner();
            break;
        case CelluloZoneTypes::RECTANGLEBORDER:
            childrenItem = new CelluloZoneRectangleBorder();
            break;
        case CelluloZoneTypes::RECTANGLEDISTANCE:
            childrenItem = new CelluloZoneRectangleDistance();
            break;
        case CelluloZoneTypes::LINEDISTANCE:
            childrenItem = new CelluloZoneLineDistance();
            break;
        case CelluloZoneTypes::POINTDISTANCE:
            childrenItem = new CelluloZonePointDistance();
            break;
        case CelluloZoneTypes::RPOLYGONINNER:
            childrenItem = new CelluloZoneRegularPolygonInner();
            break;
        case CelluloZoneTypes::RPOLYGONBORDER:
            childrenItem = new CelluloZoneRegularPolygonBorder();
            break;
        case CelluloZoneTypes::RPOLYGONDISTANCE:
            childrenItem = new CelluloZoneRegularPolygonDistance();
            break;
        case CelluloZoneTypes::IRPOLYGONINNER:
            childrenItem = new CelluloZoneIrregularPolygonInner();
            break;
        case CelluloZoneTypes::IRPOLYGONBORDER:
            childrenItem = new CelluloZoneIrregularPolygonBorder();
            break;
        case CelluloZoneTypes::IRPOLYGONDISTANCE:
            childrenItem = new CelluloZoneIrregularPolygonDistance();
            break;
        default:
            qDebug() << "Forgot to handle an enum case";
            return false;
            break;
    }

    CelluloZone* zone = qobject_cast<CelluloZone *>(childrenItem);

    if(zone){
        Q_FOREACH(QString property, properties.keys()){
            if(zone->getRatioProperties(realPlaygroundWidth,realPlaygroundHeight).contains(property.toStdString().c_str())){
                zone->setProperty(property.toStdString().c_str(), properties[property]);
            } else {
                qDebug() << "Problem when setting property to the zone, property '" << property.toStdString().c_str() << "' not valid for this zone";
                return false;
            }
        }
        zone->setProperty("realPlaygroundWidth", realPlaygroundWidth);
        zone->setProperty("realPlaygroundHeight", realPlaygroundHeight);
        setParentToZone(zone);
        emit(newZoneCreatedReadyForVisualization(zone->getType(), zone->getRatioProperties(realPlaygroundWidth, realPlaygroundHeight), this->children().size(), vRplaygroundWidth, vRplaygroundHeight));
        return true;

    }
    else{
        qDebug() << "Problem when casting object to CelluloZone";
        return false;
    }
}*/

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
QVariant CelluloZoneEngine::getZoneFromName(QString name){
    QList<CelluloZone*> list = this->findChildren<CelluloZone *>();
    QVariant returnedZone;
    foreach(CelluloZone *z, list) {
        QString zoneName = z->getName();
        if(zoneName == name){
            switch(z->getType()){
                case CelluloZoneTypes::CIRCLEINNER:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneCircleInner *>(z));
                    break;
                case CelluloZoneTypes::CIRCLEBORDER:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneCircleBorder *>(z));
                    break;
                case CelluloZoneTypes::CIRCLEDISTANCE:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneCircleDistance *>(z));
                    break;
                case CelluloZoneTypes::RECTANGLEINNER:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneRectangleInner *>(z));
                    break;
                case CelluloZoneTypes::RECTANGLEBORDER:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneRectangleBorder *>(z));
                    break;
                case CelluloZoneTypes::LINEDISTANCE:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneLineDistance *>(z));
                    break;
                case CelluloZoneTypes::POINTDISTANCE:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZonePointDistance *>(z));
                    break;
                case CelluloZoneTypes::RPOLYGONINNER:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneRegularPolygonInner *>(z));
                    break;
                case CelluloZoneTypes::IRPOLYGONINNER:
                    returnedZone = QVariant::fromValue(dynamic_cast<CelluloZoneIrregularPolygonInner *>(z));
                    break;
                default:
                    qDebug() << "Forgot to handle an enum case";
                    return QVariant();
                    break;
            }
            return returnedZone;
        }
    }
    qDebug() << "No zone handled by this engine";
    return QVariant();
}*/

/*
bool CelluloZoneEngine::getAllZonesAndSaveThem(QString path){
    QList<CelluloZone*> zones = this->parent()->findChildren<CelluloZone *>();
    return CelluloZoneJsonHandler::saveZones(zones, path, realPlaygroundWidth, realPlaygroundHeight);
}*/
