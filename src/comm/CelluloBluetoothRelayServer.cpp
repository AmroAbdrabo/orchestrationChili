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
 * @brief Relays packets to/from clients/robots
 * @author Ayberk Özgür
 * @date 2016-11-18
 */

#include "CelluloBluetoothRelayServer.h"

#include <QBluetoothUuid>

CelluloBluetoothRelayServer::CelluloBluetoothRelayServer(QQuickItem* parent):
    QQuickItem(parent),
    server(QBluetoothServiceInfo::RfcommProtocol, this)
{
    uuid = "{00001101-0000-1000-8000-00805F9B34FB}";
    name = "Cellulo Bluetooth Relay Server";
    connect(&server, SIGNAL(newConnection()), this, SLOT(publishConnections()));
}

CelluloBluetoothRelayServer::~CelluloBluetoothRelayServer(){
    service.unregisterService();
    server.close();
}

bool CelluloBluetoothRelayServer::isListening() const{
    return server.isListening();
}

void CelluloBluetoothRelayServer::setListening(bool enable){
    bool wasListening = server.isListening();

    if(enable){
        service = server.listen(QBluetoothUuid(uuid), name);
        if(!service.isValid())
            qWarning() << "BluetoothServer::setListening(): Couldn't start listening: " << server.error();
    }
    else{
        service.unregisterService();
        server.close();
    }

    if(wasListening != server.isListening())
        emit listeningChanged();
}

void CelluloBluetoothRelayServer::addClients(){
    while(server.hasPendingConnections()){
        //emit newConnection(new BluetoothSocketExtended(server.nextPendingConnection(), this));

    }
}
