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
 * @file CelluloTcpRelayServer.h
 * @brief Relays packets between a client and robots over TCP
 * @author Ayberk Özgür
 * @date 2016-11-18
 */

#ifndef CELLULOTCPRELAYSERVER_H
#define CELLULOTCPRELAYSERVER_H

#include <QQuickItem>
#include <QTcpServer>
#include <QTcpSocket>

#include "CelluloBluetoothPacket.h"
#include "CelluloBluetooth.h"

class CelluloBluetooth;

class CelluloTcpRelayServer : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(QString address READ getAddress WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)

    friend class CelluloBluetooth;

public:

    static const int DEFAULT_RELAY_PORT = 2556;         ///< Default TCP port for Cellulo relay communication
    static const QString DEFAULT_ROBOT_MAC_ADDR_PREFIX; ///< Default prefix of Cellulo robot MAC addresses

    /**
     * @brief Creates a new CelluloTcpRelayServer with the given QML parent
     *
     * @param parent The QML parent
     */
    CelluloTcpRelayServer(QQuickItem* parent = 0);

    /**
     * @brief Destroys this CelluloTcpRelayServer
     */
    ~CelluloTcpRelayServer();

    /**
     * @brief Gets whether the server is listening
     *
     * @return Whether the server is listening
     */
    bool isListening() const;

    /**
     * @brief Enables/disables listening
     *
     * @param enable Whether to listen or close the server and stop listening
     */
    void setListening(bool enable);

    /**
     * @brief Gets the current host address
     *
     * @return Current host address, e.g "127.0.0.1"
     */
    QString getAddress() const { return address; }

    /**
     * @brief Sets the host address
     *
     * @param host The new host address, e.g "127.0.0.1"
     */
    void setAddress(QString address);

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

signals:

    /**
     * @brief Emitted when the host address changes
     */
    void addressChanged();

    /**
     * @brief Emitted whe the port changes
     */
    void portChanged();

    /**
     * @brief Emitted when a new client connects
     */
    void clientConnected();

    /**
     * @brief Emitted when the client disconnects
     */
    void clientDisconnected();

    /**
     * @brief Emitted when a new robot is added to the server
     *
     * @param macAddr MAC address of the added robot
     */
    void robotAdded(QString macAddr);

    /**
     * @brief Emitted when a robot is removed from the server
     *
     * @param macAddr MAC address of the removed robot
     */
    void robotRemoved(QString macAddr);

public slots:

    /**
     * @brief Adds robot to the robots list, sets the robot's relay server to this object
     *
     * @param robot New robot
     */
    void addRobot(CelluloBluetooth* robot);

    /**
     * @brief Removes the robot from the robots list
     *
     * @param robot Existing robot
     */
    void removeRobot(CelluloBluetooth* robot);

    /**
     * @brief Closes the client's socket
     */
    void disconnectClient();

private slots:

    /**
     * @brief Gets the incoming connections and adds them to the client list
     */
    void addClient();

    /**
     * @brief Directly deletes the client socket because it was closed remotely
     */
    void deleteClient();

    /**
     * @brief Load client message into a packet to be processed
     */
    void incomingClientData();

private:

    /**
     * @brief Relays the packet from the client to the robot, or queues for relay, or sets target robot
     */
    void processClientPacket();

    /**
     * @brief Relays the packet from the robot to the client, or queues for relay
     *
     * @param macAddr Full MAC address of the target robot on the client
     * @param packet The packet to relay
     */
    void sendToClient(QString macAddr, CelluloBluetoothPacket const& packet);

    QString address;                     ///< Host address, e.g "127.0.0.1"
    quint16 port;                        ///< Port to listen to
    QTcpServer server;                   ///< TCP server that listens to clients

    QTcpSocket* clientSocket;            ///< TCP socket to client that handles communication
    CelluloBluetoothPacket clientPacket; ///< Client's incoming packet

    int currentRobot;                    ///< Current robot index to relay messages to, set by a CmdPacketTypeSetAddress
    QList<CelluloBluetooth*> robots;     ///< List of robots to relay to/from

    QString lastMacAddr;                 ///< MAC address of the last EventPacketTypeSetAddress packet sent to the server

};

#endif // CELLULOTCPRELAYSERVER_H
