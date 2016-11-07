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
 * @file BluetoothLocalDeviceEnums.h
 * @brief Header for exposing QBluetoothLocalDevice enums to QML
 * @author Ayberk Özgür
 * @date 2016-11-07
 */

#ifndef BLUETOOTHLOCALDEVICEENUMS_H
#define BLUETOOTHLOCALDEVICEENUMS_H

#include <QObject>
#include <QBluetoothLocalDevice>

#include "../CelluloEnumDecl.h"

/**
 * @brief Singleton wrapper for exposing QBluetoothLocalDevice enums to QML
 */
class BluetoothLocalDeviceEnums : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    BluetoothLocalDeviceEnums(QObject* parent = 0);
    ~BluetoothLocalDeviceEnums();

    enum HostMode {
        HostModePoweredOff = QBluetoothLocalDevice::HostPoweredOff,
        HostModeConnectable = QBluetoothLocalDevice::HostConnectable,
        HostModeDiscoverable = QBluetoothLocalDevice::HostDiscoverable,
        HostModeDiscoverableLimitedInquiry = QBluetoothLocalDevice::HostDiscoverableLimitedInquiry
    };
    Q_ENUM(HostMode)
    CELLULO_ENUM_DECL(HostMode)
};

Q_DECLARE_METATYPE(BluetoothLocalDeviceEnums::HostMode)

#endif // CELLULOBLUETOOTHENUMS_H
