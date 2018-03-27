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
 * @file CelluloLocalRelayServer.cpp
 * @brief Relays packets between a client and virtual robot objects over a Unix domain socket
 * @author Ayberk Özgür
 * @date 2017-03-16
 */

#include "CelluloLocalRelayServer.h"
#include "../CelluloCommUtil.h"

namespace Cellulo{

CelluloLocalRelayServer::CelluloLocalRelayServer(QQuickItem* parent) :
    #if defined(Q_OS_ANDROID)
        CelluloRelayServer(CelluloCommUtil::RelayProtocol::Tcp, parent){ //QLocalServer doesn't work on Android for some reason
            address = "127.0.0.1";
        }
    #else
        CelluloRelayServer(CelluloCommUtil::RelayProtocol::Local, parent){}
    #endif

CelluloLocalRelayServer::~CelluloLocalRelayServer(){}

bool CelluloLocalRelayServer::cleanSocket(){
    return QLocalServer::removeServer(address);
}

}
