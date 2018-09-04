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
 * @file CelluloBluezUtil.cpp
 * @brief All things Cellulo done with the bluez c API
 * @author Ayberk Özgür
 * @date 2018-09-04
 */

#include "CelluloBluezUtil.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

namespace Cellulo{

bool CelluloBluezUtil::bindToLocalAdapter(QBluetoothSocket* socket, QString const& localAdapterMacAddr){
    struct sockaddr_rc localAddrStruct;
    localAddrStruct.rc_family = AF_BLUETOOTH;
    //qDebug() << "rc_channel: " << localAddrStruct.rc_channel;
    //localAddrStruct.rc_channel = (uint8_t) 1;

    //Open new low level BTPROTO_RFCOMM socket
    int socketDescriptor = ::socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if(socketDescriptor < 0){
        qCritical() << "CelluloBluezUtil::bindToLocalAdapter(): socket() returned error: " << strerror(errno);
        return false;
    }

    str2ba(localAdapterMacAddr.toStdString().c_str(), &(localAddrStruct.rc_bdaddr)); //Always returns 0, does not return error

    //Bind the BTPROTO_RFCOMM socket to the local adapter
    if(bind(socketDescriptor, (struct sockaddr*)(&localAddrStruct), sizeof(localAddrStruct)) < 0){
        qCritical() << "CelluloBluezUtil::bindToLocalAdapter(): bind() returned error: " << strerror(errno);
        ::close(socketDescriptor);
        return false;
    }

    //Set the BTPROTO_RFCOMM socket as QBluetoothSocket's low level socket
    if(!socket->setSocketDescriptor(socketDescriptor, QBluetoothServiceInfo::RfcommProtocol, QBluetoothSocket::UnconnectedState)){
        qCritical() << "CelluloBluezUtil::bindToLocalAdapter(): QBluetoothSocket::setSocketDescriptor() failed.";
        ::close(socketDescriptor);
        return false;
    }

    return true;
}

}
