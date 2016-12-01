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

CelluloBluetoothRelayClient::CelluloBluetoothRelayClient(QQuickItem* parent) :
    QQuickItem(parent),
    serverSocket(QBluetoothServiceInfo::RfcommProtocol, this)
{
    lastMacAddr = "";
    currentRobot = -1;
    serverAddress = "00:00:00:00:00:00";
    uuid = "{00001101-0000-1000-8000-00805F9B34FB}";

    connect(&serverSocket, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(&serverSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(&serverSocket, static_cast<void (QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error),
            [=](QBluetoothSocket::SocketError error){ qDebug() << "CelluloBluetoothRelayClient serverSocket error: " << error; });
    connect(&serverSocket, SIGNAL(readyRead()), this, SLOT(incomingServerData()));

    broadcastPeriod = 0;
    connect(&broadcastTimer, SIGNAL(timeout()), this, SLOT(broadcastToServer()));
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

void CelluloBluetoothRelayClient::setBroadcastPeriod(qreal broadcastPeriod){
    if(this->broadcastPeriod != broadcastPeriod){
        this->broadcastPeriod = broadcastPeriod;

        if(broadcastPeriod == 0){
            broadcastTimer.stop();
            broadcastToServer();
        }
        else{
            broadcastTimer.stop();
            broadcastTimer.setInterval(broadcastPeriod);
            broadcastTimer.start();
        }

        emit broadcastPeriodChanged();
    }
}

void CelluloBluetoothRelayClient::connectToServer(){
    lastMacAddr = "";
    serverSocket.connectToService(QBluetoothAddress(serverAddress), QBluetoothUuid(uuid));
}

void CelluloBluetoothRelayClient::disconnectFromServer(){
    lastMacAddr = "";
    serverSocket.disconnectFromService();
}

void CelluloBluetoothRelayClient::addRobot(CelluloBluetooth* robot){
    if(!robots.contains(robot)){
        robots.append(robot);
        serverPackets.append(new QQueue<CelluloBluetoothPacket*>());
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
    CelluloBluetoothPacket::EventPacketType packetType = serverPacket.getEventPacketType();

    //Set target robot command
    if(packetType == CelluloBluetoothPacket::EventPacketTypeSetAddress){
        quint8 fifthOctet = serverPacket.unloadUInt8();
        quint8 sixthOctet = serverPacket.unloadUInt8();
        QString suffix = (fifthOctet <= 0xF ? "0" : "") + QString::number(fifthOctet, 16) + ":" + (sixthOctet <= 0xF ? "0" : "") + QString::number(sixthOctet, 16);

        int newRobot = -1;
        for(int i=0; i<robots.size(); i++)
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

    //Connection status announcement
    else if(packetType == CelluloBluetoothPacket::EventPacketTypeAnnounceConnectionStatus){
        CelluloBluetoothEnums::ConnectionStatus newStatus = (CelluloBluetoothEnums::ConnectionStatus)serverPacket.unloadUInt8();
        if(robots[currentRobot]->connectionStatus != newStatus){
            robots[currentRobot]->connectionStatus = newStatus;
            emit robots[currentRobot]->connectionStatusChanged();
        }
    }

    //Some other command and there is already a target robot
    else
        robots[currentRobot]->processResponse(serverPacket);

    serverPacket.clear();
}

void CelluloBluetoothRelayClient::sendToServer(QString macAddr, CelluloBluetoothPacket const& packet){

    //Immediate send
    if(broadcastPeriod <= 0)
        sendToServerNow(macAddr, packet);

    //Queue for sending on broadcast
    else{
        for(int i=0; i<robots.size(); i++)
            if(robots[i]->macAddr == macAddr){
                serverPackets[i]->enqueue(packet.clone());
                return;
            }

        qWarning() << "CelluloBluetoothRelayClient::sendToServer(): Provided MAC address does not match any in the robot list.";
    }
}

void CelluloBluetoothRelayClient::sendToServerNow(QString macAddr, CelluloBluetoothPacket const& packet){

    //Send MAC address only if another robot is targeted
    if(lastMacAddr != macAddr){
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

        lastMacAddr = macAddr;
    }

    //Send actual packet
    serverSocket.write(packet.getCmdSendData());
}

void CelluloBluetoothRelayClient::broadcastToServer(){
    for(int i=0;i<robots.size();i++){
        QString macAddr = robots[i]->macAddr;
        while(!serverPackets[i]->isEmpty()){
            CelluloBluetoothPacket* packet = serverPackets[i]->dequeue();
            sendToServerNow(macAddr, *packet);
            delete packet;
        }
    }
}
