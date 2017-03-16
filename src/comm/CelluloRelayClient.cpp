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
 * @file CelluloRelayClient.cpp
 * @brief Relays packets between a server and virtual robot objects
 * @author Ayberk Özgür
 * @date 2016-11-22
 */

#include "CelluloRelayClient.h"

CelluloRelayClient::CelluloRelayClient(CelluloRelayCommon::PROTOCOL protocol, QQuickItem* parent) :
    QQuickItem(parent)
{
    lastMacAddr = "";
    currentRobot = -1;

    this->protocol = protocol;
    switch(protocol){
        case CelluloRelayCommon::PROTOCOL::LOCAL:
            serverAddress = "cellulo_relay";
            port = -1;
            serverSocket = new QLocalSocket(this);
            connect((QLocalSocket*)serverSocket, static_cast<void (QLocalSocket::*)(QLocalSocket::LocalSocketError)>(&QLocalSocket::error),
                    [=](QLocalSocket::LocalSocketError error){ qDebug() << "CelluloRelayClient serverSocket error: " << error; });
            break;

        case CelluloRelayCommon::PROTOCOL::TCP:
            serverAddress = "localhost";
            port = CelluloRelayCommon::DEFAULT_RELAY_PORT;
            serverSocket = new QTcpSocket(this);
            connect((QTcpSocket*)serverSocket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
                    [=](QTcpSocket::SocketError error){ qDebug() << "CelluloRelayClient serverSocket error: " << error; });
            break;
    }

    connect(serverSocket, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(serverSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(incomingServerData()));
}

CelluloRelayClient::~CelluloRelayClient(){
    serverSocket->close();
    delete serverSocket;
}

void CelluloRelayClient::setServerAddress(QString serverAddress){
    if(serverAddress != this->serverAddress){
        bool unconnected = false;
        switch(protocol){
            case CelluloRelayCommon::PROTOCOL::LOCAL:
                unconnected = ((QLocalSocket*)serverSocket)->state() != QLocalSocket::UnconnectedState;
                break;

            case CelluloRelayCommon::PROTOCOL::TCP:
                unconnected = ((QTcpSocket*)serverSocket)->state() != QTcpSocket::UnconnectedState;
                break;
        }

        if(!unconnected)
            qWarning() << "CelluloRelayClient::setServerAddress(): Can only set server address while disconnected.";
        else{
            this->serverAddress = serverAddress;
            emit serverAddressChanged();
        }
    }
}

void CelluloRelayClient::setPort(int port){
    if(protocol != CelluloRelayCommon::PROTOCOL::TCP){
        qWarning() << "CelluloRelayClient::setPort(): Port only meaningful for TCP sockets.";
        return;
    }

    if(port < 0){
        qWarning() << "CelluloRelayClient::setPort(): port given was negative, setting to 0.";
        port = 0;
    }
    else if(port > 0xFFFF){
        qWarning() << "CelluloRelayClient::setPort(): port given was larger than 65535, setting to 65535.";
        port = 0xFFFF;
    }

    if(port != this->port){
        if(((QTcpSocket*)serverSocket)->state() != QTcpSocket::UnconnectedState)
            qWarning() << "CelluloRelayClient::setPort(): Can only set port while disconnected.";
        else{
            this->port = port;
            emit portChanged();
        }
    }
}

void CelluloRelayClient::connectToServer(){
    lastMacAddr = "";
    switch(protocol){
        case CelluloRelayCommon::PROTOCOL::LOCAL:
            ((QLocalSocket*)serverSocket)->connectToServer(serverAddress);
            break;

        case CelluloRelayCommon::PROTOCOL::TCP:
            ((QTcpSocket*)serverSocket)->connectToHost(serverAddress, port);
            break;
    }
}

void CelluloRelayClient::disconnectFromServer(){
    lastMacAddr = "";
    switch(protocol){
        case CelluloRelayCommon::PROTOCOL::LOCAL:
            ((QLocalSocket*)serverSocket)->disconnectFromServer();
            break;

        case CelluloRelayCommon::PROTOCOL::TCP:
            ((QTcpSocket*)serverSocket)->disconnectFromHost();
            break;
    }
}

void CelluloRelayClient::addRobot(CelluloBluetooth* robot){
    if(!robots.contains(robot)){
        robots.append(robot);
        robot->setRelayClient(this);
    }
}

void CelluloRelayClient::incomingServerData(){
    QByteArray message = serverSocket->readAll();

    for(int i=0; i<message.length(); i++)

        //Load byte as part of an event message and check end of packet
        if(serverPacket.loadEventByte(message[i]))
            processServerPacket();
}

void CelluloRelayClient::processServerPacket(){
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
            qWarning() << "CelluloRelayClient::processServerPacket(): Received EventPacketTypeSetAddress with address suffix " << suffix << ", but no such robot is known to the client.";







            //HANDLE UNRELATED ROBOTS BETTER










        else
            currentRobot = newRobot;
    }

    //Some other command but no robot selected yet
    else if(currentRobot < 0)
        qWarning() << "CelluloRelayClient::processServerPacket(): Received event packet but no robot is chosen yet, EventPacketTypeSetAddress must be sent first. Dropping this packet.";

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

void CelluloRelayClient::sendToServer(QString macAddr, CelluloBluetoothPacket const& packet){

    //Send MAC address only if another robot is targeted
    if(lastMacAddr != macAddr){
        QStringList octets = macAddr.split(':');
        if(octets.size() < 2){
            qWarning() << "CelluloRelayClient::sendToServer(): Provided MAC address is in the wrong format.";
            return;
        }

        quint8 fifthOctet = (quint8)(octets[octets.size() - 2].toUInt(NULL, 16));
        quint8 sixthOctet = (quint8)(octets[octets.size() - 1].toUInt(NULL, 16));

        CelluloBluetoothPacket setAddressPacket;
        setAddressPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetAddress);
        setAddressPacket.load(fifthOctet);
        setAddressPacket.load(sixthOctet);
        serverSocket->write(setAddressPacket.getCmdSendData());

        lastMacAddr = macAddr;
    }

    //If connect/disconnect requested, need to resend MAC addr in the future
    if(packet.getCmdPacketType() == CelluloBluetoothPacket::CmdPacketTypeSetConnectionStatus)
        lastMacAddr = "";

    //Send actual packet
    serverSocket->write(packet.getCmdSendData());
}
