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
 * @file BluetoothLocalDevice.cpp
 * @brief Source of QtQuick wrapper around QBluetoothLocalDevice
 * @author Ayberk Özgür
 * @date 2016-11-07
 */

#include "BluetoothLocalDevice.h"

BluetoothLocalDevice::BluetoothLocalDevice(QQuickItem* parent) : QQuickItem(parent){
    connect(&localDevice, SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)), this, SIGNAL(hostModeChanged()));
}

BluetoothLocalDevice::~BluetoothLocalDevice(){ }

BluetoothLocalDeviceEnums::HostMode BluetoothLocalDevice::getHostMode() const {
    return (BluetoothLocalDeviceEnums::HostMode)localDevice.hostMode();
}

bool BluetoothLocalDevice::isValid() const {
    return localDevice.isValid();
}

void BluetoothLocalDevice::powerOn(){
    localDevice.powerOn();
}

QString BluetoothLocalDevice::getName() const {
    return localDevice.name();
}

QString BluetoothLocalDevice::getAddress() const {
    return localDevice.address().toString();
}
