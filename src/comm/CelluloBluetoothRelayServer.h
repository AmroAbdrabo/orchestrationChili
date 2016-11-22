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

class CelluloBluetoothRelayServer : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(bool listen READ isListening WRITE setListening NOTIFY listeningChanged)

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

signals:

    /**
     * @brief Emitted when listening changes
     */
    void listeningChanged();

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
     * @brief Adds robot to the robots list
     *
     * @param robot New robot
     */
    void addRobot(CelluloBluetooth* robot);

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

    QString uuid;                                           ///< Service uuid, e.g "{00001101-0000-1000-8000-00805F9B34FB}"
    QString name;                                           ///< Service name
    QBluetoothServer server;                                ///< The QBluetoothServer object to wrap
    QBluetoothServiceInfo service;                          ///< Service that is opened by listen()

    QBluetoothSocket* clientSocket;                         ///< Bluetooth socket connected to the client
    CelluloBluetoothPacket clientPacket;                    ///< Client's incoming packet

    int currentRobot;                                       ///< Current robot index to relay messages to, set by a CmdPacketTypeSetAddress
    QList<CelluloBluetooth*> robots;                        ///< List of robots to relay to/from
    //QList<QQueue<CelluloBluetoothPacket> > robotPackets;    ///< Packets to send to all robots
    //QList<QQueue<CelluloBluetoothPacket> > clientPackets;   ///< Packets coming from all robots

};

#endif // CELLULOBLUETOOTHRELAYSERVER_H
