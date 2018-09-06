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

#include "../CelluloCommUtil.h"

namespace Cellulo{

CelluloRelayClient::CelluloRelayClient(CelluloCommUtil::RelayProtocol protocol, QQuickItem* parent) :
    QQuickItem(parent)
{
    lastMacAddr = "";
    currentRobot = -1;

    this->protocol = protocol;
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            serverAddress = "cellulo_relay";
            port = -1;
            serverSocket = new QLocalSocket(this);
            connect((QLocalSocket*)serverSocket, static_cast<void (QLocalSocket::*)(QLocalSocket::LocalSocketError)>(&QLocalSocket::error),
                    [=](QLocalSocket::LocalSocketError error){ qDebug() << "CelluloRelayClient serverSocket error: " << error; });
            break;

        case CelluloCommUtil::RelayProtocol::Tcp:
            serverAddress = "localhost";
            port = CelluloCommUtil::DEFAULT_RELAY_PORT;
            serverSocket = new QTcpSocket(this);
            ((QTcpSocket*)serverSocket)->setSocketOption(QAbstractSocket::LowDelayOption, 1);
            connect((QTcpSocket*)serverSocket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
                    [=](QTcpSocket::SocketError error){ qDebug() << "CelluloRelayClient serverSocket error: " << error; });
            break;
    }

    connect(serverSocket, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(serverSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(incomingServerData()));
    connect(this, SIGNAL(connected()), this, SIGNAL(connectedChanged()));
    connect(this, SIGNAL(disconnected()), this, SIGNAL(connectedChanged()));

    autoConnect = true;
    connect(&reconnectTimer, SIGNAL(timeout()), this, SLOT(decideReconnect()));
    reconnectTimer.start(SERVER_RECONNECT_TIME_MILLIS);

    connect(&heartbeatTimer, SIGNAL(timeout()), this, SLOT(sendHeartbeat()));
    heartbeatTimer.setSingleShot(false);
    heartbeatTimer.setInterval(CelluloCommUtil::RELAY_HEARTBEAT_INTERVAL);
    connect(this, SIGNAL(connected()),    &heartbeatTimer, SLOT(start()));
    connect(this, SIGNAL(disconnected()), &heartbeatTimer, SLOT(stop()));
}

CelluloRelayClient::~CelluloRelayClient(){
    serverSocket->close();
    delete serverSocket;
}

void CelluloRelayClient::setAutoConnect(bool autoConnect){
    if(this->autoConnect != autoConnect){
        this->autoConnect = autoConnect;

        if(autoConnect)
            reconnectTimer.start(SERVER_RECONNECT_TIME_MILLIS);
        else
            reconnectTimer.stop();

        emit autoConnectChanged();
    }
}

void CelluloRelayClient::decideReconnect(){
    if(autoConnect){
        switch(protocol){
            case CelluloCommUtil::RelayProtocol::Local:
                if(((QLocalSocket*)serverSocket)->state() == QLocalSocket::UnconnectedState){
                    reconnectTimer.stop();
                    connectToServer();
                }
                break;

            case CelluloCommUtil::RelayProtocol::Tcp:
                if(((QTcpSocket*)serverSocket)->state() == QTcpSocket::UnconnectedState){
                    reconnectTimer.stop();
                    connectToServer();
                }
                break;
        }
    }
}

void CelluloRelayClient::sendHeartbeat(){
    if(isConnected()){
        CelluloBluetoothPacket heartbeatPacket;
        heartbeatPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeHeartbeat);
        serverSocket->write(heartbeatPacket.getCmdSendData());
    }
}

void CelluloRelayClient::setServerAddress(QString serverAddress){
    if(serverAddress != this->serverAddress){
        bool notUnconnected = false;
        switch(protocol){
            case CelluloCommUtil::RelayProtocol::Local:
                notUnconnected = ((QLocalSocket*)serverSocket)->state() != QLocalSocket::UnconnectedState;
                break;

            case CelluloCommUtil::RelayProtocol::Tcp:
                notUnconnected = ((QTcpSocket*)serverSocket)->state() != QTcpSocket::UnconnectedState;
                break;
        }

        if(notUnconnected){
            disconnectFromServer();
            this->serverAddress = serverAddress;
            emit serverAddressChanged();
            if(autoConnect)
                reconnectTimer.start(SERVER_RECONNECT_TIME_MILLIS);
            else{
                reconnectTimer.stop();
                connectToServer();
            }
        }
        else{
            this->serverAddress = serverAddress;
            emit serverAddressChanged();
        }
    }
}

void CelluloRelayClient::setPort(int port){
    if(protocol != CelluloCommUtil::RelayProtocol::Tcp){
        qWarning() << "CelluloRelayClient::setPort(): Port only meaningful for Tcp sockets.";
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
        if(((QTcpSocket*)serverSocket)->state() != QTcpSocket::UnconnectedState){
            disconnectFromServer();
            this->port = port;
            emit portChanged();
            if(autoConnect)
                reconnectTimer.start(SERVER_RECONNECT_TIME_MILLIS);
            else{
                reconnectTimer.stop();
                connectToServer();
            }
        }
        else{
            this->port = port;
            emit portChanged();
        }
    }
}

bool CelluloRelayClient::isConnected(){
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            return ((QLocalSocket*)serverSocket)->state() == QLocalSocket::ConnectedState;

        case CelluloCommUtil::RelayProtocol::Tcp:
            return ((QTcpSocket*)serverSocket)->state() == QTcpSocket::ConnectedState;
    }
    return false;
}

void CelluloRelayClient::connectToServer(){
    lastMacAddr = "";
    localAdapters.clear();
    emit localAdaptersChanged();

    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            ((QLocalSocket*)serverSocket)->connectToServer(serverAddress);
            break;

        case CelluloCommUtil::RelayProtocol::Tcp:
            ((QTcpSocket*)serverSocket)->connectToHost(serverAddress, port);
            break;
    }
}

void CelluloRelayClient::disconnectFromServer(){
    switch(protocol){
        case CelluloCommUtil::RelayProtocol::Local:
            ((QLocalSocket*)serverSocket)->disconnectFromServer();
            break;

        case CelluloCommUtil::RelayProtocol::Tcp:
            ((QTcpSocket*)serverSocket)->disconnectFromHost();
            break;
    }

    lastMacAddr = "";
    localAdapters.clear();
    emit localAdaptersChanged();
}

void CelluloRelayClient::addRobot(CelluloBluetooth* robot, bool select){
    if(!robots.contains(robot)){
        robots.append(robot);
        robot->setRelayClient(this);

        if(select)
            currentRobot = robots.size() - 1;

        emit robotsChanged();
    }
}

void CelluloRelayClient::removeRobot(CelluloBluetooth* robot){
    if(robot != NULL){
        CelluloBluetooth* prevRobot = NULL;
        if(currentRobot >= 0)
            prevRobot = robots[currentRobot];

        if(robots.removeAll(robot) > 0){
            robot->setRelayClient(NULL);
            if(prevRobot == robot)
                prevRobot = NULL;

            emit robotsChanged();
        }

        currentRobot = robots.indexOf(prevRobot);
    }
}

QVariantList CelluloRelayClient::getRobots() const {
    QVariantList robotsVar;
    for(CelluloBluetooth* robot : robots)
        robotsVar << QVariant::fromValue(robot);
    return robotsVar;
}

QVariantList CelluloRelayClient::getLocalAdapters() const {
    QVariantList adaptersVar;
    for(QString const& adapter : localAdapters)
        adaptersVar << QVariant::fromValue(adapter);
    return adaptersVar;
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

    //Local adapter announcement
    if(packetType == CelluloBluetoothPacket::EventPacketTypeAnnounceLocalAdapter){
        bool added = (bool)serverPacket.unloadUInt8();
        quint8 firstOctet = serverPacket.unloadUInt8();
        quint8 secondOctet = serverPacket.unloadUInt8();
        quint8 thirdOctet = serverPacket.unloadUInt8();
        quint8 fourthOctet = serverPacket.unloadUInt8();
        quint8 fifthOctet = serverPacket.unloadUInt8();
        quint8 sixthOctet = serverPacket.unloadUInt8();
        QString localAdapter = CelluloCommUtil::getMacAddr(QList<quint8>({firstOctet, secondOctet, thirdOctet, fourthOctet, fifthOctet, sixthOctet})).toUpper();

        if(added && !localAdapters.contains(localAdapter)){
            localAdapters.append(localAdapter);
            emit localAdaptersChanged();
        }
        else if(!added && localAdapters.contains(localAdapter)){
            localAdapters.removeAll(localAdapter);
            emit localAdaptersChanged();
        }
    }

    //Set target robot event
    else if(packetType == CelluloBluetoothPacket::EventPacketTypeSetAddress){
        quint8 firstOctet = serverPacket.unloadUInt8();
        quint8 secondOctet = serverPacket.unloadUInt8();
        quint8 thirdOctet = serverPacket.unloadUInt8();
        quint8 fourthOctet = serverPacket.unloadUInt8();
        quint8 fifthOctet = serverPacket.unloadUInt8();
        quint8 sixthOctet = serverPacket.unloadUInt8();
        QString incomingAddr = CelluloCommUtil::getMacAddr(QList<quint8>({firstOctet, secondOctet, thirdOctet, fourthOctet, fifthOctet, sixthOctet}));

        int newRobot = -1;
        for(int i=0; i<robots.size(); i++)
            if(robots[i]->getMacAddr().compare(incomingAddr, Qt::CaseInsensitive) == 0){
                newRobot = i;
                break;
            }

        if(newRobot < 0){
            currentRobot = -1;
            emit unknownRobotAtServer(incomingAddr);
        }
        else
            currentRobot = newRobot;
    }

    //Some other event but no robot selected yet
    else if(currentRobot < 0)
        qWarning() << "CelluloRelayClient::processServerPacket(): Received event packet but no robot is chosen yet, EventPacketTypeSetAddress must be sent first. Dropping this packet.";

    //Connection status announcement
    else if(packetType == CelluloBluetoothPacket::EventPacketTypeAnnounceConnectionStatus){

        //Connection status
        CelluloBluetoothEnums::ConnectionStatus newStatus = (CelluloBluetoothEnums::ConnectionStatus)serverPacket.unloadUInt8();
        if(robots[currentRobot]->connectionStatus != newStatus){
            robots[currentRobot]->connectionStatus = newStatus;
            emit robots[currentRobot]->connectionStatusChanged();
        }

        //Local adapter MAC address
        QList<quint8> octets;
        for(int i=0;i<6;i++)
            octets.append(serverPacket.unloadUInt8());
        robots[currentRobot]->setLocalAdapterMacAddr(CelluloCommUtil::getMacAddr(octets));
    }

    //Some other command and there is already a target robot
    else
        robots[currentRobot]->processResponse(serverPacket);

    serverPacket.clear();
}

void CelluloRelayClient::sendToServer(QString macAddr, CelluloBluetoothPacket const& packet){

    //Send MAC address only if another robot is targeted
    if(lastMacAddr != macAddr){
        QList<quint8> octets = CelluloCommUtil::getOctets(macAddr);
        if(octets[0] == 0 && octets[1] == 0 && octets[2] == 0 && octets[3] == 0 && octets[4] == 0 && octets[5] == 0){
            qWarning() << "CelluloRelayClient::sendToServer(): Provided MAC address is in the wrong format.";
            return;
        }

        CelluloBluetoothPacket setAddressPacket;
        setAddressPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetAddress);
        setAddressPacket.load(octets[0]);
        setAddressPacket.load(octets[1]);
        setAddressPacket.load(octets[2]);
        setAddressPacket.load(octets[3]);
        setAddressPacket.load(octets[4]);
        setAddressPacket.load(octets[5]);
        serverSocket->write(setAddressPacket.getCmdSendData());

        lastMacAddr = macAddr;
    }

    //If connect/disconnect requested, need to resend MAC addr in the future
    if(packet.getCmdPacketType() == CelluloBluetoothPacket::CmdPacketTypeSetConnectionStatus)
        lastMacAddr = "";

    //Send actual packet
    serverSocket->write(packet.getCmdSendData());
}

}
