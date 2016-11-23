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
 * @file CelluloBluetoothRelayClient.cpp
 * @brief Relays packets between a server and virtual robot objects
 * @author Ayberk Özgür
 * @date 2016-11-22
 */

#include "CelluloBluetoothRelayClient.h"

CelluloBluetoothRelayClient::CelluloBluetoothRelayClient(QQuickItem* parent):
    QQuickItem(parent),
    serverSocket(QBluetoothServiceInfo::RfcommProtocol, this)
{
    currentRobot = -1;
    serverAddress = "00:00:00:00:00:00";
    uuid = "{00001101-0000-1000-8000-00805F9B34FB}";

    connect(&serverSocket, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(&serverSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(&serverSocket, static_cast<void (QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error),
            [=](QBluetoothSocket::SocketError error){ qDebug() << "CelluloBluetoothRelayClient serverSocket error: " << error; });
    connect(&serverSocket, SIGNAL(readyRead()), this, SLOT(incomingServerData()));
}

CelluloBluetoothRelayClient::~CelluloBluetoothRelayClient(){
    serverSocket.close();
}

void CelluloBluetoothRelayClient::setServerAddress(QString serverAddress){
    if(serverAddress != this->serverAddress){
        if(serverSocket.state() != QBluetoothSocket::UnconnectedState)
            qWarning() << "CelluloBluetoothRelayClient::setServerAddress(): Can only set server address while disconnected.";
        else{
            this->serverAddress = serverAddress;
            emit serverAddressChanged();
        }
    }
}

void CelluloBluetoothRelayClient::connectToServer(){
    serverSocket.connectToService(QBluetoothAddress(serverAddress), QBluetoothUuid(uuid));
}

void CelluloBluetoothRelayClient::disconnectFromServer(){
    serverSocket.disconnectFromService();
}

void CelluloBluetoothRelayClient::addRobot(CelluloBluetooth* robot){
    if(!robots.contains(robot)){
        robots.append(robot);
        robot->setRelayClient(this);
    }
}

void CelluloBluetoothRelayClient::incomingServerData(){
    QByteArray message = serverSocket.readAll();

    for(int i=0; i<message.length(); i++)

        //Load byte as part of an event message and check end of packet
        if(serverPacket.loadEventByte(message[i]))
            processServerPacket();
}

void CelluloBluetoothRelayClient::processServerPacket(){

    //Set target robot command
    if(serverPacket.getEventPacketType() == CelluloBluetoothPacket::EventPacketTypeSetAddress){
        quint8 fifthOctet = serverPacket.unloadUInt8();
        quint8 sixthOctet = serverPacket.unloadUInt8();
        QString suffix = QString::number(fifthOctet, 16) + ":" + QString::number(sixthOctet, 16);

        int newRobot = -1;
        for(int i=0;i<robots.size();i++)
            if(robots[i]->getMacAddr().endsWith(suffix, Qt::CaseInsensitive)){
                newRobot = i;
                break;
            }

        if(newRobot < 0)
            qWarning() << "CelluloBluetoothRelayClient::processServerPacket(): Received EventPacketTypeSetAddress with address suffix " << suffix << ", but no such robot is known to the client.";
        else
            currentRobot = newRobot;
    }

    //Some other command but no robot selected yet
    else if(currentRobot < 0)
        qWarning() << "CelluloBluetoothRelayClient::processServerPacket(): Received event packet but no robot is chosen yet, EventPacketTypeSetAddress must be sent first. Dropping this packet.";

    //Some other command and there is already a target robot
    else{

        //IMMEDIATE SEND FOR NOW

        robots[currentRobot]->processResponse(serverPacket);
    }

    serverPacket.clear();
}

void CelluloBluetoothRelayClient::sendToServer(QString macAddr, CelluloBluetoothPacket const& packet){

    //IMMEDIATE SEND FOR NOW

    QStringList octets = macAddr.split(':');
    if(octets.size() < 2){
        qWarning() << "CelluloBluetoothRelayClient::sendToServer(): Provided MAC address is in the wrong format.";
        return;
    }

    quint8 fifthOctet = (quint8)(octets[octets.size() - 2].toUInt(NULL, 16));
    quint8 sixthOctet = (quint8)(octets[octets.size() - 1].toUInt(NULL, 16));

    CelluloBluetoothPacket setAddressPacket;
    setAddressPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetAddress);
    setAddressPacket.load(fifthOctet);
    setAddressPacket.load(sixthOctet);
    serverSocket.write(setAddressPacket.getCmdSendData());

    serverSocket.write(packet.getCmdSendData());
}
