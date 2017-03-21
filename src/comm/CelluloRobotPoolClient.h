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
 * @file CelluloRobotPoolClient.h
 * @brief Uses the robots at a cellulo-robot-pool
 * @author Ayberk Özgür
 * @date 2017-03-21
 */

#ifndef CELLULOROBOTPOOLCLIENT_H
#define CELLULOROBOTPOOLCLIENT_H

#include "CelluloLocalRelayClient.h"

#include "CelluloBluetooth.h"

#include <QJSValue>

class CelluloRobotPoolClient : public CelluloLocalRelayClient {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(QJSValue createRobot READ getCreateRobot WRITE setCreateRobot NOTIFY createRobotChanged)

public:

    /**
     * @brief Creates a new CelluloRobotPoolClient with the given QML parent
     *
     * @param parent The QML parent
     */
    CelluloRobotPoolClient(QQuickItem* parent = 0);

    /**
     * @brief Destroys this CelluloRobotPoolClient
     */
    virtual ~CelluloRobotPoolClient();

    /**
     * @brief Gets the createRobot function
     *
     * @return The createRobot function
     */
    QJSValue getCreateRobot() const { return createRobotFunction; }

    /**
     * @brief Sets the createRobot function
     *
     * @param function The createRobot function that takes a string and returns a CelluloBluetooth pointer or CelluloBluetooth-derived object pointer
     */
    void setCreateRobot(QJSValue const& function);

signals:

    /**
     * @brief Emitted when the createRobot function changes
     */
    void createRobotChanged();

private slots:

    /**
     * @brief Creates, adds and selects a given robot
     *
     * @param macAddr MAC address of the robot object to create
     */
    void createAddSelectRobot(QString macAddr);

private:

     QJSValue createRobotFunction;  ///< A Javascript function that takes a string and returns a CelluloBluetooth pointer or CelluloBluetooth-derived object pointer

};

#endif // CELLULOROBOTPOOLCLIENT_H
