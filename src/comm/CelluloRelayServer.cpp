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
 * @file CelluloRelayServer.cpp
 * @brief Relays packets between a client and robots
 * @author Ayberk Özgür
 * @date 2016-11-18
 */

#include "CelluloRelayServer.h"

CelluloRelayServer::CelluloRelayServer(CelluloCommUtil::RelayProtocol protocol, QQuickItem* parent) :
    QQuickItem(parent)
{
    lastMacAddr = "";
    currentRobot = -1;

    clientSocket = NULL;

    this->protocol = protocol;
    localServer = NULL;
    tcpServer = NULL;
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            address = "cellulo_relay";
            port = -1;
            localServer = new QLocalServer(this);
            connect(localServer, SIGNAL(newConnection()), this, SLOT(addClient()));
            break;

        case CelluloCommUtil::RelayProtocol::Tcp:
            address = "localhost";
            port = CelluloCommUtil::DEFAULT_RELAY_PORT;
            tcpServer = new QTcpServer(this);
            connect(tcpServer, SIGNAL(newConnection()), this, SLOT(addClient()));
            break;
    }

    setListening(true);
}

CelluloRelayServer::~CelluloRelayServer(){
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            localServer->close();
            delete localServer;
            break;

        case CelluloCommUtil::RelayProtocol::Tcp:
            tcpServer->close();
            delete tcpServer;
            break;
    }
    disconnectClient();
}

bool CelluloRelayServer::isListening() const {
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            return localServer->isListening();

        case CelluloCommUtil::RelayProtocol::Tcp:
            return tcpServer->isListening();
    }

    return false;
}

void CelluloRelayServer::setListening(bool enable){
    if(enable){
        if(clientSocket != NULL)
            qWarning() << "CelluloRelayServer::setListening(): Can't start listening while client is connected, only one client is allowed.";
        else{
            switch(protocol){
                case CelluloCommUtil::RelayProtocol::Local:
                    QLocalServer::removeServer(address);
                    if(!localServer->listen(address))
                        qWarning() << "CelluloRelayServer::setListening(): Couldn't start listening: " << localServer->errorString();
                    else
                        qDebug() << "CelluloRelayServer::setListening(): Started listening on " << localServer->fullServerName();
                    break;

                case CelluloCommUtil::RelayProtocol::Tcp:
                    if(!tcpServer->listen(QHostAddress(address), port))
                        qWarning() << "CelluloRelayServer::setListening(): Couldn't start listening: " << tcpServer->errorString();
                    else
                        qDebug() << "CelluloRelayServer::setListening(): Started listening on " << tcpServer->serverAddress() << ":" << tcpServer->serverPort();
                    break;
            }
        }
    }
    else{
        switch(protocol){
            case CelluloCommUtil::RelayProtocol::Local:
                localServer->close();
                break;

            case CelluloCommUtil::RelayProtocol::Tcp:
                tcpServer->close();
                break;
        }
    }
}

void CelluloRelayServer::setAddress(QString address){
    if(address != this->address){
        bool wasListening = isListening();
        setListening(false);
        this->address = address;
        if(wasListening)
            setListening(true);
        emit addressChanged();
    }
}

void CelluloRelayServer::setPort(int port){
    if(protocol != CelluloCommUtil::RelayProtocol::Tcp){
        qWarning() << "CelluloRelayServer::setPort(): Port only meaningful for Tcp sockets.";
        return;
    }

    if(port < 0){
        qWarning() << "CelluloRelayServer::setPort(): port given was negative, setting to 0.";
        port = 0;
    }
    else if(port > 0xFFFF){
        qWarning() << "CelluloRelayServer::setPort(): port given was larger than 65535, setting to 65535.";
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

void CelluloRelayServer::addRobot(CelluloBluetooth* robot){
    if(robot != NULL && !robots.contains(robot)){
        robots.append(robot);
        robot->setRelayServer(this);
        robot->announceConnectionStatusToRelayServer();
        emit robotAdded(robot->macAddr);
    }
}

void CelluloRelayServer::removeRobot(CelluloBluetooth* robot){
    if(robot != NULL && robots.removeAll(robot) > 0){
        robot->announceConnectionStatusToRelayServer();
        robot->setRelayServer(NULL);
        emit robotRemoved(robot->macAddr);
    }
}

void CelluloRelayServer::addClient(){
    bool serverHasPendingConnections = false;
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            serverHasPendingConnections = localServer->hasPendingConnections();
            break;

        case CelluloCommUtil::RelayProtocol::Tcp:
            serverHasPendingConnections = tcpServer->hasPendingConnections();
            break;
    }

    //Get first connection
    if(clientSocket == NULL && serverHasPendingConnections){
        switch(protocol){
            case CelluloCommUtil::RelayProtocol::Local:
                clientSocket = localServer->nextPendingConnection();
                connect((QLocalSocket*)clientSocket, static_cast<void (QLocalSocket::*)(QLocalSocket::LocalSocketError)>(&QLocalSocket::error),
                        [=](QLocalSocket::LocalSocketError error){ qDebug() << "CelluloRelayServer clientSocket error: " << error; });
                break;

            case CelluloCommUtil::RelayProtocol::Tcp:
                clientSocket = tcpServer->nextPendingConnection();
                connect((QTcpSocket*)clientSocket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
                        [=](QTcpSocket::SocketError error){ qDebug() << "CelluloRelayServer clientSocket error: " << error; });
                break;
        }


        connect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        connect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));

        setListening(false);

        lastMacAddr = "";

        for(CelluloBluetooth* robot : robots)
            robot->announceConnectionStatusToRelayServer();

        emit clientConnected();
    }

    //TODO: ALLOW MULTIPLE CLIENTS

    //Discard rest of the connections
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            serverHasPendingConnections = localServer->hasPendingConnections();
            break;

        case CelluloCommUtil::RelayProtocol::Tcp:
            serverHasPendingConnections = tcpServer->hasPendingConnections();
            break;
    }
    while(serverHasPendingConnections){
        QIODevice* trash = NULL;
        switch(protocol){
            case CelluloCommUtil::RelayProtocol::Local:
                trash = localServer->nextPendingConnection();
                serverHasPendingConnections = localServer->hasPendingConnections();
                break;

            case CelluloCommUtil::RelayProtocol::Tcp:
                trash = tcpServer->nextPendingConnection();
                serverHasPendingConnections = tcpServer->hasPendingConnections();
                break;
        }
        if(trash != NULL){
            connect(trash, SIGNAL(disconnected()), trash, SLOT(deleteLater()));
            trash->close();
        }
    }
}

void CelluloRelayServer::deleteClient(){
    if(clientSocket != NULL){
        disconnect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));

        lastMacAddr = "";

        clientSocket->deleteLater();
        clientSocket = NULL;
        emit clientDisconnected();

        setListening(true);
    }
}

void CelluloRelayServer::disconnectClient(){
    if(clientSocket != NULL){
        disconnect(clientSocket, SIGNAL(readyRead()), this, SLOT(incomingClientData()));
        disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(deleteClient()));

        lastMacAddr = "";

        connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
        clientSocket->close();
        clientSocket = NULL;
        emit clientDisconnected();

        setListening(true);
    }
}

void CelluloRelayServer::incomingClientData(){
    QByteArray message = clientSocket->readAll();

    for(int i=0; i<message.length(); i++)

        //Load byte as part of a command message and check end of packet
        if(clientPacket.loadCmdByte(message[i]))
            processClientPacket();
}

void CelluloRelayServer::processClientPacket(){
    CelluloBluetoothPacket::CmdPacketType packetType = clientPacket.getCmdPacketType();

    //Set target robot command
    if(packetType == CelluloBluetoothPacket::CmdPacketTypeSetAddress){
        quint8 fifthOctet = clientPacket.unloadUInt8();
        quint8 sixthOctet = clientPacket.unloadUInt8();
        QString suffix = CelluloCommUtil::getMacAddrSuffix(fifthOctet, sixthOctet);

        int newRobot = -1;
        for(int i=0; i<robots.size(); i++)
            if(robots[i]->getMacAddr().endsWith(suffix, Qt::CaseInsensitive)){
                newRobot = i;
                break;
            }

        if(newRobot < 0){
            CelluloBluetooth* robot = new CelluloBluetooth(this);
            robot->setAutoConnect(false);
            robot->setMacAddr(CelluloCommUtil::DEFAULT_ROBOT_MAC_ADDR_PREFIX + suffix);
            robot->setAutoConnect(true);
            addRobot(robot);
            currentRobot = robots.size() - 1;
        }
        else
            currentRobot = newRobot;
    }

    //Some other command but no robot selected yet
    else if(currentRobot < 0)
        qWarning() << "CelluloRelayServer::processClientPacket(): Received command packet but no robot is chosen yet, CmdPacketTypeSetAddress must be sent first. Dropping this packet.";

    //Connect/disconnect command
    else if(packetType == CelluloBluetoothPacket::CmdPacketTypeSetConnectionStatus){
        CelluloBluetoothEnums::ConnectionStatus status = (CelluloBluetoothEnums::ConnectionStatus)clientPacket.unloadUInt8();
        switch(status){
            case CelluloBluetoothEnums::ConnectionStatusConnected:{

                //Get possible local adapter MAC address
                robots[currentRobot]->setAutoConnect(false);
                QList<quint8> octets;
                for(int i=0;i<6;i++)
                    octets.append(clientPacket.unloadUInt8());
                robots[currentRobot]->setLocalAdapterMacAddr(CelluloCommUtil::getMacAddr(octets));
                robots[currentRobot]->setAutoConnect(true);

                robots[currentRobot]->connectToServer();
                break;
            }

            case CelluloBluetoothEnums::ConnectionStatusDisconnected: {
                CelluloBluetooth* robot = robots[currentRobot];
                robot->disconnectFromServer();
                removeRobot(robot);
                robot->deleteLater();
                currentRobot = -1;
                break;
            }

            default:
                qWarning() << "CelluloRelayServer::processClientPacket(): Invalid argument to CmdPacketTypeSetAddress packet.";
                break;
        }
    }

    //Some other command and there is already a target robot
    else
        robots[currentRobot]->sendCommand(clientPacket);

    clientPacket.clear();
}

void CelluloRelayServer::sendToClient(QString macAddr, CelluloBluetoothPacket const& packet){
    if(clientSocket != NULL){

        //Send MAC address only if another robot is targeted
        if(lastMacAddr != macAddr){
            QList<quint8> octets = CelluloCommUtil::getOctets(macAddr);
            if(octets[0] == 0 && octets[1] == 0 && octets[2] == 0 && octets[3] == 0 && octets[4] == 0 && octets[5] == 0){
                qWarning() << "CelluloRelayServer::sendToClient(): Provided MAC address is in the wrong format.";
                return;
            }

            CelluloBluetoothPacket setAddressPacket;
            setAddressPacket.setEventPacketType(CelluloBluetoothPacket::EventPacketTypeSetAddress);
            setAddressPacket.load(octets[4]);
            setAddressPacket.load(octets[5]);
            clientSocket->write(setAddressPacket.getEventSendData());

            lastMacAddr = macAddr;
        }

        //Send actual packet
        clientSocket->write(packet.getEventSendData());
    }
    else
        qWarning() << "CelluloRelayServer::sendToClient(): Trying to relay packet but no client connected yet.";
}
