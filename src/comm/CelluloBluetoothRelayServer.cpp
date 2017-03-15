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

CelluloBluetoothRelayServer::CelluloBluetoothRelayServer(QQuickItem* parent) :
    QQuickItem(parent),
    server(this)
{
    lastMacAddr = "";
    currentRobot = -1;

    address = "localhost";
    port = DEFAULT_RELAY_PORT;

    clientSocket = NULL;
    connect(&server, SIGNAL(newConnection()), this, SLOT(addClient()));
}

CelluloBluetoothRelayServer::~CelluloBluetoothRelayServer(){
    server.close();
    disconnectClient();
}

bool CelluloBluetoothRelayServer::isListening() const {
    return server.isListening();
}

void CelluloBluetoothRelayServer::setListening(bool enable){
    bool wasListening = server.isListening();

    if(enable){
        if(clientSocket != NULL)
            qWarning() << "BluetoothServer::setListening(): Can't start listening while client is connected, only one client is allowed.";
        else{
            if(!server.listen(QHostAddress(address), port))
                qWarning() << "TcpServer::setListening(): Couldn't start listening: " << server.errorString();
        }
    }
    else
        server.close();

    if(wasListening != server.isListening())
        emit listeningChanged();
}

void CelluloBluetoothRelayServer::setAddress(QString address){
    if(address != this->address){
        bool wasListening = isListening();
        setListening(false);
        this->address = address;
        if(wasListening)
            setListening(true);
        emit addressChanged();
    }
}

void CelluloBluetoothRelayServer::setPort(int port){
    if(port < 0){
        qWarning() << "CelluloBluetoothRelayServer::setPort(): port given was negative, setting to 0.";
        port = 0;
    }
    else if(port > 0xFFFF){
        qWarning() << "CelluloBluetoothRelayServer::setPort(): port given was larger than 65535, setting to 65535.";
        port = 0xFFFF;
    }

    if(port != this->port){
        bool wasListening = isListening();
        setListening(false);
        this->port = port;
        if(wasListening)
            setListening(true);
        emit portChanged();
    }
}

void CelluloBluetoothRelayServer::addRobot(CelluloBluetooth* robot){
    if(!robots.contains(robot)){
        robots.append(robot);
        robot->setRelayServer(this);
        robot->announceConnectionStatusToRelayServer();
    }
}

void CelluloBluetoothRelayServer::addClient(){
    if(clientSocket == NULL && server.hasPendingConnections()){
        clientSocket = server.nextPendingConnection();

        connect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        connect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));
        connect(clientSocket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
                [=](QTcpSocket::SocketError error){ qDebug() << "CelluloBluetoothRelayServer clientSocket error: " << error; });

        setListening(false);

        lastMacAddr = "";

        for(CelluloBluetooth* robot : robots)
            robot->announceConnectionStatusToRelayServer();

        emit clientConnected();
    }

    //TODO: ALLOW MULTIPLE CLIENTS

    //Discard rest of the connections
    while(server.hasPendingConnections()){
        QTcpSocket* trash = server.nextPendingConnection();
        connect(trash, SIGNAL(disconnected()), trash, SLOT(deleteLater()));
        trash->close();
    }
}

void CelluloBluetoothRelayServer::deleteClient(){
    if(clientSocket != NULL){
        disconnect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));

        lastMacAddr = "";

        clientSocket->deleteLater();
        clientSocket = NULL;
        emit clientDisconnected();
    }
}

void CelluloBluetoothRelayServer::disconnectClient(){
    if(clientSocket != NULL){
        disconnect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));

        lastMacAddr = "";

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
    CelluloBluetoothPacket::CmdPacketType packetType = clientPacket.getCmdPacketType();

    //Set target robot command
    if(packetType == CelluloBluetoothPacket::CmdPacketTypeSetAddress){
        quint8 fifthOctet = clientPacket.unloadUInt8();
        quint8 sixthOctet = clientPacket.unloadUInt8();
        QString suffix = (fifthOctet <= 0xF ? "0" : "") + QString::number(fifthOctet, 16) + ":" + (sixthOctet <= 0xF ? "0" : "") + QString::number(sixthOctet, 16);

        int newRobot = -1;
        for(int i=0; i<robots.size(); i++)
            if(robots[i]->getMacAddr().endsWith(suffix, Qt::CaseInsensitive)){
                newRobot = i;
                break;
            }

        if(newRobot < 0)








            //CREATE AND ADD NEW ROBOT







            qWarning() << "CelluloBluetoothRelayServer::processClientPacket(): Received CmdPacketTypeSetAddress with address suffix " << suffix << ", but no such robot is known to the server.";
        else
            currentRobot = newRobot;
    }

    //Some other command but no robot selected yet
    else if(currentRobot < 0)
        qWarning() << "CelluloBluetoothRelayServer::processClientPacket(): Received command packet but no robot is chosen yet, CmdPacketTypeSetAddress must be sent first. Dropping this packet.";

    //Connect/disconnect command
    else if(packetType == CelluloBluetoothPacket::CmdPacketTypeSetConnectionStatus){
        CelluloBluetoothEnums::ConnectionStatus status = (CelluloBluetoothEnums::ConnectionStatus)clientPacket.unloadUInt8();

        switch(status){
            case CelluloBluetoothEnums::ConnectionStatusConnected:
                robots[currentRobot]->connectToServer();
                break;

            case CelluloBluetoothEnums::ConnectionStatusDisconnected:
                robots[currentRobot]->disconnectFromServer();
                break;

            default:
                qWarning() << "CelluloBluetoothRelayServer::processClientPacket(): Invalid argument to CmdPacketTypeSetAddress packet.";
                break;
        }
    }

    //Some other command and there is already a target robot
    else
        robots[currentRobot]->sendCommand(clientPacket);

    clientPacket.clear();
}

void CelluloBluetoothRelayServer::sendToClient(QString macAddr, CelluloBluetoothPacket const& packet){
    if(clientSocket != NULL){

        //Send MAC address only if another robot is targeted
        if(lastMacAddr != macAddr){
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

            lastMacAddr = macAddr;
        }

        //Send actual packet
        clientSocket->write(packet.getEventSendData());
    }
    else
        qWarning() << "CelluloBluetoothRelayServer::sendToClient(): Trying to relay packet but no client connected yet.";
}
