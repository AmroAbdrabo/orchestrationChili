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
 * @file CelluloRelayClient.h
 * @brief Relays packets between a server and virtual robot objects
 * @author Ayberk Özgür
 * @date 2016-11-22
 */

#ifndef CELLULORELAYCLIENT_H
#define CELLULORELAYCLIENT_H

#include <QQuickItem>
#include <QIODevice>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLocalServer>
#include <QLocalSocket>

#include "CelluloBluetooth.h"
#include "CelluloBluetoothPacket.h"
#include "CelluloRelayCommon.h"

class CelluloBluetooth;

class CelluloRelayClient : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(QString serverAddress READ getServerAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)

    friend class CelluloBluetooth;

public:

    /**
     * @brief Creates a new CelluloRelayClient with the given QML parent
     *
     * @param protocol Underlying transfer protocol to use
     * @param parent The QML parent
     */
    CelluloRelayClient(CelluloRelayCommon::PROTOCOL protocol, QQuickItem* parent = 0);

    /**
     * @brief Destroys this CelluloRelayClient
     */
    virtual ~CelluloRelayClient();

    /**
     * @brief Gets the current server's address
     *
     * @return Current server address, e.g `127.0.0.1` for TCP
     */
    QString getServerAddress() const { return serverAddress; }

    /**
     * @brief Sets the server address to connect to
     *
     * @param peer The new server address, e.g `127.0.0.1` for TCP
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

    CelluloRelayCommon::PROTOCOL protocol; ///< Underlying transfer protocol

    QString serverAddress;                       ///< Server's address, e.g "127.0.0.1"
    quint16 port;                                ///< Port to connect to on the server

    QIODevice* serverSocket;                     ///< Socket to server that handles communication
    CelluloBluetoothPacket serverPacket;         ///< Server's incoming packet

    int currentRobot;                            ///< Current robot index to relay messages to, set by a CmdPacketTypeSetAddress
    QList<CelluloBluetooth*> robots;             ///< List of robots to relay to/from

    QString lastMacAddr;                         ///< MAC address of the last CmdPacketTypeSetAddress packet sent to the server

};

#endif // CELLULORELAYCLIENT_H
