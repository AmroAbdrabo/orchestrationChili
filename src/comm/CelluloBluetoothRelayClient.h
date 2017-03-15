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
 * @file CelluloBluetoothRelayClient.h
 * @brief Relays packets between a server and virtual robot objects
 * @author Ayberk Özgür
 * @date 2016-11-22
 */

#ifndef CELLULOBLUETOOTHRELAYCLIENT_H
#define CELLULOBLUETOOTHRELAYCLIENT_H

#include <QQuickItem>
#include <QTcpServer>
#include <QTcpSocket>

#include "CelluloBluetoothPacket.h"
#include "CelluloBluetooth.h"

class CelluloBluetooth;

class CelluloBluetoothRelayClient : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(QString serverAddress READ getServerAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)

    friend class CelluloBluetooth;

public:

    /**
     * @brief Creates a new BluetoothSocketExtended with the given QML parent
     *
     * @param parent The QML parent
     */
    CelluloBluetoothRelayClient(QQuickItem* parent = 0);

    /**
     * @brief Destroys this CelluloBluetoothRelayClient
     */
    ~CelluloBluetoothRelayClient();

    /**
     * @brief Gets the current server's MAC address
     *
     * @return Current server MAC address, e.g "XX:XX:XX:XX:XX:XX"
     */
    QString getServerAddress() const { return serverAddress; }

    /**
     * @brief Sets the server MAC address to connect to
     *
     * @param peer The new server MAC address, e.g "XX:XX:XX:XX:XX:XX"
     */
    void setServerAddress(QString serverAddress);

    /**
     * @brief Gets the current port
     *
     * @return Current port
     */
    int getPort() const { return port; }

    /**
     * @brief Sets the port
     *
     * @param port The new port, must be in [0,65535]
     */
    void setPort(int port);

public slots:

    /**
     * @brief Initiates a connection to the service on the server
     */
    void connectToServer();

    /**
     * @brief Starts closing the socket
     */
    void disconnectFromServer();

    /**
     * @brief Adds the robot to the robots list, sets the robot's relay client to this object
     *
     * @param robot New robot
     */
    void addRobot(CelluloBluetooth* robot);

signals:

    /**
     * @brief Emitted when the server address changes
     */
    void serverAddressChanged();

    /**
     * @brief Emitted whe the port changes
     */
    void portChanged();

    /**
     * @brief Emitted when the server socket is connected
     */
    void connected();

    /**
     * @brief Emitted when the server socket is disconected
     */
    void disconnected();

private slots:

    /**
     * @brief Load the server data into a packet to be processed
     */
    void incomingServerData();

private:

    /**
     * @brief Relays the packet from the server to the robot, or queues for relay, or sets target robot
     */
    void processServerPacket();

    /**
     * @brief Relays the packet from the robot to the server, or queues for relay
     *
     * @param macAddr Full MAC address of the target robot on the server
     * @param packet The packet to relay
     */
    void sendToServer(QString macAddr, CelluloBluetoothPacket const& packet);

    QString serverAddress;               ///< Server's address, e.g "127.0.0.1"
    quint16 port;                        ///< Port to connect to on the server

    QTcpSocket serverSocket;             ///< TCP socket to server that handles communication
    CelluloBluetoothPacket serverPacket; ///< Server's incoming packet

    int currentRobot;                    ///< Current robot index to relay messages to, set by a CmdPacketTypeSetAddress
    QList<CelluloBluetooth*> robots;     ///< List of robots to relay to/from

    QString lastMacAddr;                 ///< MAC address of the last CmdPacketTypeSetAddress packet sent to the server

};

#endif // CELLULOBLUETOOTHRELAYCLIENT_H
