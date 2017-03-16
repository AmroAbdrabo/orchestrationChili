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
 * @file CelluloBluetoothScanner.cpp
 * @brief Scans for Cellulo robots
 * @author Ayberk Özgür
 * @date 2017-03-16
 */

#include "CelluloBluetoothScanner.h"

#include "CelluloRelayCommon.h"

CelluloBluetoothScanner::CelluloBluetoothScanner(QQuickItem* parent) : QQuickItem(parent){
    running = false;

    connect(&scanner, SIGNAL(finished()), this, SLOT(decideRestart()));
    connect(&scanner, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo const&)), this, SLOT(onDeviceDiscovered(QBluetoothDeviceInfo const&)));
}

CelluloBluetoothScanner::~CelluloBluetoothScanner(){}

void CelluloBluetoothScanner::setRunning(bool running){
    if(this->running != running){
        this->running = running;

        if(running)
            scanner.start();
        else
            scanner.stop();

        emit runningChanged();
    }
}

void CelluloBluetoothScanner::clear(){
    if(!foundRobots.isEmpty()){
        foundRobots.clear();
        emit foundRobotsChanged();
    }
}

void CelluloBluetoothScanner::decideRestart(){
    if(running)
        scanner.start();
}

void CelluloBluetoothScanner::onDeviceDiscovered(QBluetoothDeviceInfo const& info){
    QString macAddr = info.address().toString().toUpper();
    if(macAddr.startsWith(CelluloRelayCommon::DEFAULT_ROBOT_MAC_ADDR_PREFIX) && !foundRobots.contains(macAddr)){
        foundRobots.append(macAddr);
        emit foundRobotsChanged();
    }
}
