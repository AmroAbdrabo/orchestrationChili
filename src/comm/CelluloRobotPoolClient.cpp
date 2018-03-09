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
 * @file CelluloRobotPoolClient.cpp
 * @brief Uses the robots at a cellulo-robot-pool
 * @author Ayberk Özgür
 * @date 2017-03-21
 */

#include "CelluloRobotPoolClient.h"

#include <QMetaObject>
#include <QVariant>

namespace Cellulo{

CelluloRobotPoolClient::CelluloRobotPoolClient(QQuickItem* parent) : CelluloLocalRelayClient(parent){
    createRobotFunction = QJSValue(QJSValue::NullValue);
    connect(this, SIGNAL(unknownRobotAtServer(QString)), this, SLOT(createAddSelectRobot(QString)));
    connectToServer();
}

CelluloRobotPoolClient::~CelluloRobotPoolClient(){}

void CelluloRobotPoolClient::setCreateRobot(QJSValue const& function){
    if(!function.isCallable()){
        qWarning() << "CelluloRobotPoolClient::setCreateRobot(): Passed object must be a callable function.";
        return;
    }

    createRobotFunction = function;
    emit createRobotChanged();
}

void CelluloRobotPoolClient::createAddSelectRobot(QString macAddr){
    if(createRobotFunction.isNull()){
        qWarning() << "CelluloRobotPoolClient::createAddSelectRobot(): In order for CelluloRobotPoolClient to work, createRobot property must be set to a function that takes a MAC address (string) and returns a newly created CelluloBluetooth or CelluloBluetooth-derived object.";
        return;
    }

    QJSValue retval = createRobotFunction.call(QJSValueList() << QJSValue(macAddr));
    if(retval.isError()){
        qWarning() << "CelluloRobotPoolClient::createAddSelectRobot(): Error while calling function at createRobot: " << retval.toString();
        return;
    }

    QObject* obj = retval.toQObject();
    if(obj == NULL){
        qWarning() << "CelluloRobotPoolClient::createAddSelectRobot(): Function at createRobot must return a non-null CelluloBluetooth or CelluloBluetooth-derived object.";
        return;
    }

    CelluloBluetooth* robot = qobject_cast<CelluloBluetooth*>(obj);
    if(robot == NULL){
        qWarning() << "CelluloRobotPoolClient::createAddSelectRobot(): Function at createRobot must return a newly created CelluloBluetooth or CelluloBluetooth-derived object (such as CelluloRobot).";
        return;
    }

    addRobot(robot, true);
}

}
