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
 * @file BluetoothLocalDevice.h
 * @brief Header of QtQuick wrapper around QBluetoothLocalDevice
 * @author Ayberk Özgür
 * @date 2016-11-07
 */

#ifndef BLUETOOTHLOCALDEVICE_H
#define BLUETOOTHLOCALDEVICE_H

#include <QQuickItem>
#include <QBluetoothLocalDevice>

#include "BluetoothLocalDeviceEnums.h"

/**
 * @brief QtQuick wrapper for QBluetoothLocalDevice
 */
class BluetoothLocalDevice : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(BluetoothLocalDeviceEnums::HostMode hostMode READ getHostMode NOTIFY hostModeChanged)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString address READ getAddress CONSTANT)

public:

    /**
     * @brief Creates a new BluetoothLocalDevice
     *
     * @param parent Parent of this QML item
     */
    explicit BluetoothLocalDevice(QQuickItem* parent = 0);

    /**
     * @brief Destroys this BluetoothLocalDevice
     */
    virtual ~BluetoothLocalDevice();

    /**
     * @brief Gets the host mode
     *
     * @return Host mode
     */
    BluetoothLocalDeviceEnums::HostMode getHostMode() const;

    /**
     * @brief Gets the local adapter name
     *
     * @return Local adapter name
     */
    QString getName() const;

    /**
     * @brief Gets the local adapter address
     *
     * @return Local address in the form "XX:XX:XX:XX:XX:XX"
     */
    QString getAddress() const;

signals:

    /**
     * @brief Emitted when the host mode changes
     */
    void hostModeChanged();

public slots:

    /**
     * @brief Gets whether this local adapter exists
     *
     * @return Whether this local adapter exists and is available
     */
    bool isValid() const;

    /**
     * @brief Sets whether to blast same robots
     *
     * @param continuous Whether to blast same robots
     */
    void powerOn();

private:

    QBluetoothLocalDevice localDevice;  ///< Local device interface

};

#endif // BLUETOOTHLOCALDEVICE_H
