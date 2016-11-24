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
 * @file CelluloBluetoothRelayServer.h
 * @brief Relays packets between a client and robots
 * @author Ayberk Özgür
 * @date 2016-11-18
 */

#ifndef CELLULOBLUETOOTHRELAYSERVER_H
#define CELLULOBLUETOOTHRELAYSERVER_H

#include <QQuickItem>
#include <QBluetoothServer>

#include "CelluloBluetoothPacket.h"
#include "CelluloBluetooth.h"

class CelluloBluetooth;

class CelluloBluetoothRelayServer : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(bool listen READ isListening WRITE setListening NOTIFY listeningChanged)
    Q_PROPERTY(qreal broadcastPeriod READ getBroadcastPeriod WRITE setBroadcastPeriod NOTIFY broadcastPeriodChanged)

    friend class CelluloBluetooth;

public:

    /**
     * @brief Creates a new CelluloBluetoothRelayServer with the given QML parent
     *
     * @param parent The QML parent
     */
    CelluloBluetoothRelayServer(QQuickItem* parent = 0);

    /**
     * @brief Destroys this CelluloBluetoothRelayServer
     */
    ~CelluloBluetoothRelayServer();

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
     * @brief Gets the broadcast period
     *
     * @return Broadcast period in milliseconds
     */
    qreal getBroadcastPeriod() const { return broadcastPeriod; }

    /**
     * @brief Sets the broadcast period
     *
     * If set to greater than zero, the server will queue all packets coming from robots and broadcast them to the client periodically.
     *
     * @param broadcastPeriod The broadcast period in milliseconds
     */
    void setBroadcastPeriod(qreal broadcastPeriod);

signals:

    /**
     * @brief Emitted when listening changes
     */
    void listeningChanged();

    /**
     * @brief Emitted when the broadcast period changes
     */
    void broadcastPeriodChanged();

    /**
     * @brief Emitted when a new client connects
     */
    void clientConnected();

    /**
     * @brief Emitted when the client disconnects
     */
    void clientDisconnected();

public slots:

    /**
     * @brief Adds robot to the robots list, sets the robot's relay server to this object
     *
     * @param robot New robot
     */
    void addRobot(CelluloBluetooth* robot);

    /**
     * @brief Gets the client MAC address
     *
     * @return The client MAC address, empty string if not connected
     */
    QString getClientAddress();

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

    /**
     * @brief Sends all packets in the clientPackets queues to the client
     */
    void broadcastToClient();

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

    /**
     * @brief Relays the packet from the robot to the client
     *
     * @param macAddr Full MAC address of the target robot on the client
     * @param packet The packet to relay
     */
    void sendToClientNow(QString macAddr, CelluloBluetoothPacket const& packet);

    QString uuid;                                          ///< Service uuid
    QString name;                                          ///< Service name
    QBluetoothServer server;                               ///< The QBluetoothServer object to wrap
    QBluetoothServiceInfo service;                         ///< Service that is opened by listen()

    QBluetoothSocket* clientSocket;                        ///< Bluetooth socket connected to the client
    CelluloBluetoothPacket clientPacket;                   ///< Client's incoming packet

    int currentRobot;                                      ///< Current robot index to relay messages to, set by a CmdPacketTypeSetAddress
    QList<CelluloBluetooth*> robots;                       ///< List of robots to relay to/from

    QString lastMacAddr;                                   ///< MAC address of the last EventPacketTypeSetAddress packet sent to the server

    qreal broadcastPeriod;                                 ///< Delays and broadcasts all packets with this period (milliseconds); default is 0 which disables this congestion control
    QList<QQueue<CelluloBluetoothPacket*>*> clientPackets; ///< Packets coming from all robots, to be sent to the client
    QTimer broadcastTimer;                                 ///< Timer that signals broadcasts

};

#endif // CELLULOBLUETOOTHRELAYSERVER_H
