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
 * @file CelluloBluetoothRelayServer.cpp
 * @brief Relays packets between a client and robots
 * @author Ayberk Özgür
 * @date 2016-11-18
 */

#include "CelluloBluetoothRelayServer.h"

#include <QBluetoothUuid>

CelluloBluetoothRelayServer::CelluloBluetoothRelayServer(QQuickItem* parent):
    QQuickItem(parent),
    server(QBluetoothServiceInfo::RfcommProtocol, this)
{
    currentRobot = -1;
    clientSocket = NULL;
    uuid = "{00001101-0000-1000-8000-00805F9B34FB}";
    name = "Cellulo Bluetooth Relay Server";
    connect(&server, SIGNAL(newConnection()), this, SLOT(addClient()));
}

CelluloBluetoothRelayServer::~CelluloBluetoothRelayServer(){
    service.unregisterService();
    server.close();
    disconnectClient();
}

bool CelluloBluetoothRelayServer::isListening() const{
    return server.isListening();
}

void CelluloBluetoothRelayServer::setListening(bool enable){
    bool wasListening = server.isListening();

    if(enable){
        if(clientSocket != NULL)
            qWarning() << "BluetoothServer::setListening(): Can't start listening while client is connected, only one client is allowed.";
        else{
            service = server.listen(QBluetoothUuid(uuid), name);
            if(!service.isValid())
                qWarning() << "BluetoothServer::setListening(): Couldn't start listening: " << server.error();
        }
    }
    else{
        service.unregisterService();
        server.close();
    }

    if(wasListening != server.isListening())
        emit listeningChanged();
}

void CelluloBluetoothRelayServer::addRobot(CelluloBluetooth* robot){
    if(!robots.contains(robot)){
        robots.append(robot);
        robot->setRelayServer(this);
    }
}

void CelluloBluetoothRelayServer::addClient(){
    if(clientSocket == NULL && server.hasPendingConnections()){
        clientSocket = server.nextPendingConnection();

        connect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        connect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));
        connect(clientSocket, static_cast<void (QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error),
                [=](QBluetoothSocket::SocketError error){ qDebug() << "CelluloBluetoothRelayServer clientSocket error: " << error; });

        setListening(false);
        emit clientConnected();
    }

    //Discard rest of the connections
    while(server.hasPendingConnections()){
        QBluetoothSocket* trash = server.nextPendingConnection();
        connect(trash, SIGNAL(disconnected()), trash, SLOT(deleteLater()));
        trash->close();
    }
}

void CelluloBluetoothRelayServer::deleteClient(){
    if(clientSocket != NULL){
        disconnect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));

        clientSocket->deleteLater();
        clientSocket = NULL;
        emit clientDisconnected();
    }
}

void CelluloBluetoothRelayServer::disconnectClient(){
    if(clientSocket != NULL){
        disconnect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));

        connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
        clientSocket->close();
        clientSocket = NULL;
        emit clientDisconnected();
    }
}

void CelluloBluetoothRelayServer::incomingClientData(){
    QByteArray message = clientSocket->readAll();

    for(int i=0; i<message.length(); i++)

        //Load byte as part of a command message and check end of packet
        if(clientPacket.loadCmdByte(message[i]))
            processClientPacket();
}

void CelluloBluetoothRelayServer::processClientPacket(){

    //Set target robot command
    if(clientPacket.getCmdPacketType() == CelluloBluetoothPacket::CmdPacketTypeSetAddress){
        quint8 fifthOctet = clientPacket.unloadUInt8();
        quint8 sixthOctet = clientPacket.unloadUInt8();
        QString suffix = QString::number(fifthOctet, 16) + ":" + QString::number(sixthOctet, 16);

        int newRobot = -1;
        for(int i=0;i<robots.size();i++)
            if(robots[i]->getMacAddr().endsWith(suffix, Qt::CaseInsensitive)){
                newRobot = i;
                break;
            }

        if(newRobot < 0)
            qWarning() << "CelluloBluetoothRelayServer::processClientPacket(): Received CmdPacketTypeSetAddress with address suffix " << suffix << ", but no such robot is known to the server.";
        else
            currentRobot = newRobot;
    }

    //Some other command but no robot selected yet
    else if(currentRobot < 0)
        qWarning() << "CelluloBluetoothRelayServer::processClientPacket(): Received command packet but no robot is chosen yet, CmdPacketTypeSetAddress must be sent first. Dropping this packet.";

    //Some other command and there is already a target robot
    else{
        //QUEUE OR IMMEDIATE SEND

        robots[currentRobot]->sendCommand(clientPacket);
    }

    clientPacket.clear();
}

void CelluloBluetoothRelayServer::sendToClient(QString macAddr, CelluloBluetoothPacket const& packet){

    //IMMEDIATE SEND FOR NOW
    if(clientSocket != NULL){
        QStringList octets = macAddr.split(':');
        if(octets.size() < 2){
            qWarning() << "CelluloBluetoothRelayServer::sendToClient(): Provided MAC address is in the wrong format.";
            return;
        }

        quint8 fifthOctet = (quint8)(octets[octets.size() - 2].toUInt(NULL, 16));
        quint8 sixthOctet = (quint8)(octets[octets.size() - 1].toUInt(NULL, 16));

        CelluloBluetoothPacket setAddressPacket;
        setAddressPacket.setEventPacketType(CelluloBluetoothPacket::EventPacketTypeSetAddress);
        setAddressPacket.load(fifthOctet);
        setAddressPacket.load(sixthOctet);
        clientSocket->write(setAddressPacket.getEventSendData());

        clientSocket->write(packet.getEventSendData());
    }
    else
        qWarning() << "CelluloBluetoothRelayServer::sendToClient(): Trying to relay packet but no client connected yet.";
}
