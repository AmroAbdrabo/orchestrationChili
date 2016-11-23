/*
 * Copyright (C) 2015 EPFL
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
 * @file CelluloBluetooth.cpp
 * @brief Source for Bluetooth communication with Cellulo robots
 * @author Ayberk Özgür
 * @date 2015-05-20
 */

#include "CelluloBluetooth.h"

#include <QBluetoothDeviceInfo>
#include <time.h>

QByteArray CelluloBluetooth::frameBuffer;

CelluloBluetooth::CelluloBluetooth(QQuickItem* parent) : CelluloZoneClient(parent){
    connect(this, SIGNAL(poseChanged(qreal,qreal,qreal)), this, SIGNAL(poseChanged_inherited()));

    autoConnect = true;
    socket = NULL;

    btConnectTimeoutTimer.setSingleShot(true);
    btConnectTimeoutTimer.setInterval(BT_CONNECT_TIMEOUT_MILLIS);
    connect(&btConnectTimeoutTimer, SIGNAL(timeout()), this, SLOT(refreshConnection()));

    //TODO: CALL RESET PROPERTIES INSTEAD OF THE BELOW

    frameBuffer.reserve(IMG_WIDTH_SHARED*IMG_HEIGHT_SHARED);

    connectionStatus = CelluloBluetoothEnums::ConnectionStatusDisconnected;

    timestampingEnabled = false;
    batteryState = CelluloBluetoothEnums::BatteryStateShutdown; //Beginning with shutdown is a good idea
    x = 0;
    y = 0;
    theta = 0;
    lastTimestamp = 0;
    framerate = 0.0;
    kidnapped = true;
    gesture = CelluloBluetoothEnums::GestureNone;
}

CelluloBluetooth::~CelluloBluetooth(){
    disconnectFromServer();
}

void CelluloBluetooth::resetProperties(){

    sendPacket.clear();
    recvPacket.clear();

    timestampingEnabled = false;
    batteryState = CelluloBluetoothEnums::BatteryStateShutdown; //Beginning with shutdown is a good idea
    emit batteryStateChanged();
    x = 0;
    y = 0;
    theta = 0;
    emit poseChanged(x, y, theta);
    lastTimestamp = 0;
    framerate = 0.0;
    emit timestampChanged();
    kidnapped = true;
    emit kidnappedChanged();
    for(int i=0; i<6; i++)
        emit touchReleased(i);
    gesture = CelluloBluetoothEnums::GestureNone;
    emit gestureChanged();
}

QVariantList CelluloBluetooth::getFrame() const {
    QVariantList frame;
    for(int i=0; i<frameBuffer.length(); i++)
        frame.append((int)frameBuffer[i]);
    while(frame.length() < IMG_WIDTH_SHARED*IMG_HEIGHT_SHARED)
        frame.append((int)0);
    return frame;
}

void CelluloBluetooth::setMacAddr(QString macAddr){
    disconnectFromServer();
    if(this->macAddr != macAddr){
        this->macAddr = macAddr;
        emit macAddrChanged();
    }
    if(!macAddr.isEmpty() && autoConnect)
        connectToServer();
}

void CelluloBluetooth::setAutoConnect(bool autoConnect){
    if(this->autoConnect != autoConnect){
        this->autoConnect = autoConnect;
        emit autoConnectChanged();
    }
}

void CelluloBluetooth::refreshConnection(){
    if(connectionStatus != CelluloBluetoothEnums::ConnectionStatusConnected){
        qDebug() << "CelluloBluetooth::refreshConnection(): Connection attempt timed out, will retry";
        disconnectFromServer();
        connectToServer();
    }
}

void CelluloBluetooth::openSocket(){
    if(socket != NULL){
        qDebug() << "CelluloBluetooth::openSocket(): " << macAddr << "...";

        socket->connectToService(
            QBluetoothAddress(macAddr),
                #ifdef ANDROID
            QBluetoothUuid(QBluetoothUuid::SerialPort)
                #else
            1     //TODO: Temporary fix until https://bugreports.qt.io/browse/QTBUG-53041 is fixed
                #endif
            );
        btConnectTimeoutTimer.start();
        if(connectionStatus != CelluloBluetoothEnums::ConnectionStatusConnecting){
            connectionStatus = CelluloBluetoothEnums::ConnectionStatusConnecting;
            emit connectionStatusChanged();
        }
    }
}

void CelluloBluetooth::connectToServer(){
    if(socket == NULL){
        socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

        connect(socket, SIGNAL(readyRead()), this, SLOT(socketDataArrived()));
        connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        connect(socket, static_cast<void (QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error),
                [=](QBluetoothSocket::SocketError error){ qDebug() << "CelluloBluetooth socket error: " << error; });

        openSocket();
    }
}

void CelluloBluetooth::disconnectFromServer(){
    if(socket != NULL){
        qDebug() << "CelluloBluetooth::disconnectFromServer(): " << macAddr << "...";
        disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketDataArrived()));
        disconnect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
        disconnect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        socket->abort();
        socket->close();
        if(connectionStatus != CelluloBluetoothEnums::ConnectionStatusDisconnected){
            connectionStatus = CelluloBluetoothEnums::ConnectionStatusDisconnected;
            emit connectionStatusChanged();
        }
        socket->deleteLater();
        socket = NULL;
        btConnectTimeoutTimer.stop();
        resetProperties();
    }
}

void CelluloBluetooth::socketConnected(){
    qDebug() << "CelluloBluetooth::socketConnected(): " << macAddr;
    if(connectionStatus != CelluloBluetoothEnums::ConnectionStatusConnected){
        connectionStatus = CelluloBluetoothEnums::ConnectionStatusConnected;
        emit connectionStatusChanged();
    }

    //Update residual states that normally update by events
    queryBatteryState();
}

void CelluloBluetooth::socketDisconnected(){
    qDebug() << "CelluloBluetooth::socketDisconnected(): " << macAddr;
    if(connectionStatus != CelluloBluetoothEnums::ConnectionStatusDisconnected){
        connectionStatus = CelluloBluetoothEnums::ConnectionStatusDisconnected;
        emit connectionStatusChanged();
    }
    if(autoConnect)
        openSocket();
}

void CelluloBluetooth::socketDataArrived(){
    QByteArray message = socket->readAll();

    for(int i=0; i<message.length(); i++)

        //Load byte and check end of packet
        if(recvPacket.loadEventByte(message[i]))
            processResponse();
}

void CelluloBluetooth::processResponse(){
    processResponse(recvPacket);
}

void CelluloBluetooth::processResponse(CelluloBluetoothPacket& externalPacket){
    switch(externalPacket.getEventPacketType()){
        case CelluloBluetoothPacket::EventPacketTypeBootComplete:
            emit bootCompleted();
            break;

        case CelluloBluetoothPacket::EventPacketTypeShuttingDown:
            emit shuttingDown();
            break;

        case CelluloBluetoothPacket::EventPacketTypeLowBattery:
            emit lowBattery();
            break;

        case CelluloBluetoothPacket::EventPacketTypeBatteryStateChanged: {
            CelluloBluetoothEnums::BatteryState newState = (CelluloBluetoothEnums::BatteryState)externalPacket.unloadUInt8();
            if(batteryState != newState){
                batteryState = newState;
                emit batteryStateChanged();
            }
            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeTouchBegan: {
            int key = externalPacket.unloadUInt8();
            if(key >= 0 && key <= 5)
                emit touchBegan(key);
            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeTouchLongPressed: {
            int key = externalPacket.unloadUInt8();
            if(key >= 0 && key <= 5)
                emit longTouch(key);
            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeTouchReleased: {
            int key = externalPacket.unloadUInt8();
            if(key >= 0 && key <= 5)
                emit touchReleased(key);
            break;
        }

        case CelluloBluetoothPacket::EventPacketTypePoseChanged: {
            x = externalPacket.unloadUInt32()*DOTS_GRID_SPACING/(float)GOAL_POSE_FACTOR_SHARED;
            y = externalPacket.unloadUInt32()*DOTS_GRID_SPACING/(float)GOAL_POSE_FACTOR_SHARED;
            theta = externalPacket.unloadUInt16()/(float)GOAL_POSE_FACTOR_SHARED;
            emit poseChanged(x,y,theta);

            if(kidnapped){
                kidnapped = false;
                emit kidnappedChanged();
            }

            break;
        }

        case CelluloBluetoothPacket::EventPacketTypePoseChangedTimestamped: {
            x = externalPacket.unloadUInt32()*DOTS_GRID_SPACING/(float)GOAL_POSE_FACTOR_SHARED;
            y = externalPacket.unloadUInt32()*DOTS_GRID_SPACING/(float)GOAL_POSE_FACTOR_SHARED;
            theta = externalPacket.unloadUInt16()/(float)GOAL_POSE_FACTOR_SHARED;
            emit poseChanged(x,y,theta);

            unsigned int newTimestamp = externalPacket.unloadUInt32();
            framerate =
                FRAMERATE_SMOOTH_FACTOR*framerate +
                (1.0 - FRAMERATE_SMOOTH_FACTOR)*1000/(newTimestamp - lastTimestamp);
            lastTimestamp = newTimestamp;
            emit timestampChanged();

            if(kidnapped){
                kidnapped = false;
                emit kidnappedChanged();
            }

            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeKidnapChanged: {
            int newKidnapped = externalPacket.unloadUInt8();
            if(newKidnapped == 0 || newKidnapped == 1)
                if((bool)newKidnapped != kidnapped){
                    kidnapped = (bool)newKidnapped;
                    emit kidnappedChanged();
                }
            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeGestureChanged: {
            CelluloBluetoothEnums::Gesture newGesture = (CelluloBluetoothEnums::Gesture)externalPacket.unloadUInt8();
            if(gesture != newGesture){
                gesture = newGesture;
                emit gestureChanged();
            }
            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeTrackingGoalReached:
            emit trackingGoalReached();
            break;

        case CelluloBluetoothPacket::EventPacketTypeAcknowledged:
            qDebug() << "CelluloBluetooth::processResponse(): Robot acknowledged";
            break;

        case CelluloBluetoothPacket::EventPacketTypeFrameLine: {
            quint16 line = externalPacket.unloadUInt16();

            //Drop previous incomplete frame
            if(frameBuffer.length() > line*IMG_WIDTH_SHARED){
                qDebug() << "CelluloBluetooth::processResponse(): Dropping previously incomplete frame";
                frameBuffer.clear();
            }

            //Append possibly empty lines
            while(frameBuffer.length() < line*IMG_WIDTH_SHARED){
                qDebug() << "CelluloBluetooth::processResponse(): Camera image line dropped";
                for(int i=0; i<IMG_WIDTH_SHARED; i++)
                    frameBuffer.append('\0');
            }

            //Append line just received
            for(int i=0; i<IMG_WIDTH_SHARED; i++)
                frameBuffer.append(externalPacket.unloadUInt8());

            //Update progress
            cameraImageProgress = (float)(line + 1)/IMG_HEIGHT_SHARED;
            emit cameraImageProgressChanged();

            if(line >= IMG_HEIGHT_SHARED - 1)
                emit frameReady();

            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeDebug: {
            qDebug("%6u %6u\n",externalPacket.unloadUInt32(),externalPacket.unloadUInt32());
            //qDebug() << "CelluloBluetoothPacket::processResponse(): Debug event received";
            break;
        }

        case CelluloBluetoothPacket::EventPacketTypeSetAddress:

            //Ignore, should never come from a robot
            externalPacket.unloadUInt8();
            externalPacket.unloadUInt8();
            qDebug() << "CelluloBluetoothPacket::processResponse(): EventPacketTypeSetAddress received, should not happen!";
            break;

        default:
            break;
    }

    externalPacket.clear();
}

void CelluloBluetooth::sendCommand(){
    if(socket != NULL)
        socket->write(sendPacket.getCmdSendData());
}

void CelluloBluetooth::sendCommand(CelluloBluetoothPacket const& externalPacket){
    if(socket != NULL)
        socket->write(externalPacket.getCmdSendData());
}

/*
 * Robot commands
 */

void CelluloBluetooth::ping(){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypePing);
    sendCommand();
}

void CelluloBluetooth::setPoseBcastPeriod(unsigned int period){
    if(period > 0xFFFF)
        period = 0xFFFF;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetBcastPeriod);
    sendPacket.load((quint16)period);
    sendCommand();
}

void CelluloBluetooth::setTimestampingEnabled(bool enabled){
    if(enabled != timestampingEnabled){
        timestampingEnabled = enabled;

        sendPacket.clear();
        sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeTimestampEnable);
        sendPacket.load((quint8)enabled);

        sendCommand();
    }
}

void CelluloBluetooth::requestFrame(){
    frameBuffer.clear();
    if(cameraImageProgress != 0.0f){
        cameraImageProgress = 0.0f;
        emit cameraImageProgressChanged();
    }

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeFrameRequest);
    sendCommand();
}

void CelluloBluetooth::setExposureTime(int pixels){
    if(pixels != 0 && pixels < 260)
        pixels = 260;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetExposureTime);
    sendPacket.load((quint32)pixels);
    sendCommand();
}

void CelluloBluetooth::queryBatteryState(){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeBatteryStateRequest);
    sendCommand();
}

void CelluloBluetooth::setMotor1Output(int output){
    setMotorOutput(1, output);
}

void CelluloBluetooth::setMotor2Output(int output){
    setMotorOutput(2, output);
}

void CelluloBluetooth::setMotor3Output(int output){
    setMotorOutput(3, output);
}

void CelluloBluetooth::setMotorOutput(int motor, int output){
    if(motor != 1 && motor != 2 && motor != 3)
        return;

    if(output < -0xFFF)
        output = -0xFFF;
    else if(output > 0xFFF)
        output = 0xFFF;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetMotorOutput);
    sendPacket.load((quint8)motor);
    sendPacket.load((qint16)output);
    sendCommand();
}

void CelluloBluetooth::setAllMotorOutputs(int m1output, int m2output, int m3output){
    if(m1output < -0xFFF)
        m1output = -0xFFF;
    else if(m1output > 0xFFF)
        m1output = 0xFFF;

    if(m2output < -0xFFF)
        m2output = -0xFFF;
    else if(m2output > 0xFFF)
        m2output = 0xFFF;

    if(m3output < -0xFFF)
        m3output = -0xFFF;
    else if(m3output > 0xFFF)
        m3output = 0xFFF;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetAllMotorOutputs);
    sendPacket.load((qint16)m1output);
    sendPacket.load((qint16)m2output);
    sendPacket.load((qint16)m3output);
    sendCommand();
}

void CelluloBluetooth::setGoalVelocity(float vx, float vy, float w){
    int vx_ = (int)(vx*GOAL_VEL_FACTOR_SHARED);
    int vy_ = (int)(vy*GOAL_VEL_FACTOR_SHARED);
    int w_ = (int)(w*GOAL_VEL_FACTOR_SHARED);

    if(vx_ < -0x7FFF)
        vx_ = -0x7FFF;
    else if(vx_ > 0x7FFF)
        vx_ = 0x7FFF;

    if(vy_ < -0x7FFF)
        vy_ = -0x7FFF;
    else if(vy_ > 0x7FFF)
        vy_ = 0x7FFF;

    if(w_ < -0x7FFF)
        w_ = -0x7FFF;
    else if(w_ > 0x7FFF)
        w_ = 0x7FFF;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalVelocity);
    sendPacket.load((qint16)vx_);
    sendPacket.load((qint16)vy_);
    sendPacket.load((qint16)w_);
    sendCommand();
}

void CelluloBluetooth::setGoalPose(float x, float y, float theta, float v, float w){
    x *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    y *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    theta *= GOAL_POSE_FACTOR_SHARED;
    v *= GOAL_VEL_FACTOR_SHARED;
    w *= GOAL_VEL_FACTOR_SHARED;

    quint32 xi, yi;
    quint16 thetai, vi, wi;

    if(x > (float)0xFFFFFFFF)
        xi = 0xFFFFFFFF;
    else
        xi = (quint32)x;

    if(y > (float)0xFFFFFFFF)
        yi = 0xFFFFFFFF;
    else
        yi = (quint32)y;

    if(theta > (float)0xFFFF)
        thetai = 0xFFFF;
    else
        thetai = (quint16)theta;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    if(w > (float)0xFFFF)
        wi = 0xFFFF;
    else
        wi = (quint16)w;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalPose);
    sendPacket.load((quint32)xi);
    sendPacket.load((quint32)yi);
    sendPacket.load((quint16)thetai);
    sendPacket.load((quint16)vi);
    sendPacket.load((quint16)wi);
    sendCommand();
}

void CelluloBluetooth::setGoalPosition(float x, float y, float v){
    x *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    y *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    v *= GOAL_VEL_FACTOR_SHARED;

    quint32 xi, yi;
    quint16 vi;

    if(x > (float)0xFFFFFFFF)
        xi = 0xFFFFFFFF;
    else
        xi = (quint32)x;

    if(y > (float)0xFFFFFFFF)
        yi = 0xFFFFFFFF;
    else
        yi = (quint32)y;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalPosition);
    sendPacket.load((quint32)xi);
    sendPacket.load((quint32)yi);
    sendPacket.load((quint16)vi);
    sendCommand();
}

void CelluloBluetooth::setGoalXCoordinate(float x, float v){
    x *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    v *= GOAL_VEL_FACTOR_SHARED;

    quint32 xi;
    quint16 vi;

    if(x > (float)0xFFFFFFFF)
        xi = 0xFFFFFFFF;
    else
        xi = (quint32)x;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalXCoordinate);
    sendPacket.load((quint32)xi);
    sendPacket.load((quint16)vi);
    sendCommand();
}

void CelluloBluetooth::setGoalYCoordinate(float y, float v){
    y *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    v *= GOAL_VEL_FACTOR_SHARED;

    quint32 yi;
    quint16 vi;

    if(y > (float)0xFFFFFFFF)
        yi = 0xFFFFFFFF;
    else
        yi = (quint32)y;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalYCoordinate);
    sendPacket.load((quint32)yi);
    sendPacket.load((quint16)vi);
    sendCommand();
}

void CelluloBluetooth::setGoalOrientation(float theta, float w){
    theta *= GOAL_POSE_FACTOR_SHARED;
    w *= GOAL_VEL_FACTOR_SHARED;
    quint16 thetai, wi;

    if(theta > (float)0xFFFF)
        thetai = 0xFFFF;
    else
        thetai = (quint16)theta;

    if(w > (float)0xFFFF)
        wi = 0xFFFF;
    else
        wi = (quint16)w;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalOrientation);
    sendPacket.load((quint16)thetai);
    sendPacket.load((quint16)wi);
    sendCommand();
}

void CelluloBluetooth::setGoalXThetaCoordinate(float x, float theta, float v, float w){
    x *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    theta *= GOAL_POSE_FACTOR_SHARED;
    v *= GOAL_VEL_FACTOR_SHARED;
    w *= GOAL_VEL_FACTOR_SHARED;

    quint32 xi;
    quint16 thetai, vi, wi;

    if(x > (float)0xFFFFFFFF)
        xi = 0xFFFFFFFF;
    else
        xi = (quint32)x;

    if(theta > (float)0xFFFF)
        thetai = 0xFFFF;
    else
        thetai = (quint16)theta;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    if(w > (float)0xFFFF)
        wi = 0xFFFF;
    else
        wi = (quint16)w;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalXThetaCoordinate);
    sendPacket.load((quint32)xi);
    sendPacket.load((quint16)thetai);
    sendPacket.load((quint16)vi);
    sendPacket.load((quint16)wi);
    sendCommand();
}

void CelluloBluetooth::setGoalYThetaCoordinate(float y, float theta, float v, float w){
    y *= GOAL_POSE_FACTOR_SHARED/DOTS_GRID_SPACING;
    theta *= GOAL_POSE_FACTOR_SHARED;
    v *= GOAL_VEL_FACTOR_SHARED;
    w *= GOAL_VEL_FACTOR_SHARED;

    quint32 yi;
    quint16 thetai, vi, wi;

    if(y > (float)0xFFFFFFFF)
        yi = 0xFFFFFFFF;
    else
        yi = (quint32)y;

    if(theta > (float)0xFFFF)
        thetai = 0xFFFF;
    else
        thetai = (quint16)theta;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    if(w > (float)0xFFFF)
        wi = 0xFFFF;
    else
        wi = (quint16)w;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalYThetaCoordinate);
    sendPacket.load((quint32)yi);
    sendPacket.load((quint16)thetai);
    sendPacket.load((quint16)vi);
    sendPacket.load((quint16)wi);
    sendCommand();
}

void CelluloBluetooth::clearTracking(){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeClearTracking);
    sendCommand();
}

void CelluloBluetooth::simpleVibrate(float iX, float iY, float iTheta, unsigned int period, unsigned int duration){
    iX *= GOAL_VEL_FACTOR_SHARED;
    iY *= GOAL_VEL_FACTOR_SHARED;
    iTheta *= GOAL_VEL_FACTOR_SHARED;

    quint16 iX_int, iY_int, iTheta_int;

    if(iX > (float)0xFFFF)
        iX_int = 0xFFFF;
    else
        iX_int = (quint16)iX;

    if(iY > (float)0xFFFF)
        iY_int = 0xFFFF;
    else
        iY_int = (quint16)iY;

    if(iTheta > (float)0xFFFF)
        iTheta_int = 0xFFFF;
    else
        iTheta_int = (quint16)iTheta;

    if(duration > 0xFFFF)
        duration = 0xFFFF;

    if(period > 0xFFFF)
        period = 0xFFFF;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSimpleVibrate);
    sendPacket.load(iX_int);
    sendPacket.load(iY_int);
    sendPacket.load(iTheta_int);
    sendPacket.load((qint16)period);
    sendPacket.load((qint16)duration);
    sendCommand();
}

void CelluloBluetooth::vibrateOnMotion(float iCoeff, unsigned int period){
    iCoeff *= 100;

    quint16 iCoeff_int;

    if(iCoeff > (float)0xFFFF)
        iCoeff_int = 0xFFFF;
    else
        iCoeff_int = (quint16)iCoeff;

    if(period > 0xFFFF)
        period = 0xFFFF;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeVibrateOnMotion);
    sendPacket.load(iCoeff_int);
    sendPacket.load((qint16)period);
    sendCommand();
}

void CelluloBluetooth::clearHapticFeedback(){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeClearHapticFeedback);
    sendCommand();
}

void CelluloBluetooth::setLEDResponseMode(CelluloBluetoothEnums::LEDResponseMode mode){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetLEDResponseMode);
    sendPacket.load((quint8)mode);
    sendCommand();
}

void CelluloBluetooth::setLocomotionInteractivityMode(CelluloBluetoothEnums::LocomotionInteractivityMode mode){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetLocomotionInteractivityMode);
    sendPacket.load((quint8)mode);
    sendCommand();
}

void CelluloBluetooth::setGestureEnabled(bool enabled){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeGestureEnable);
    sendPacket.load((quint8)enabled);
    sendCommand();
}

void CelluloBluetooth::setCasualBackdriveAssistEnabled(bool enabled){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeCasualBackdriveAssistEnable);
    sendPacket.load((quint8)enabled);
    sendCommand();
}

void CelluloBluetooth::setHapticBackdriveAssist(float xAssist, float yAssist, float thetaAssist){
    xAssist *= 100;
    yAssist *= 100;
    thetaAssist *= 100;

    qint16 xAssist_int, yAssist_int, thetaAssist_int;

    if(xAssist > (float)0x7FFF)
        xAssist_int = 0x7FFF;
    else if(xAssist < (float)(-0x7FFF))
        xAssist_int = -0x7FFF;
    else
        xAssist_int = (qint16)xAssist;

    if(yAssist > (float)0x7FFF)
        yAssist_int = 0x7FFF;
    else if(yAssist < (float)(-0x7FFF))
        yAssist_int = -0x7FFF;
    else
        yAssist_int = (qint16)yAssist;

    if(thetaAssist > (float)0x7FFF)
        thetaAssist_int = 0x7FFF;
    else if(thetaAssist < (float)(-0x7FFF))
        thetaAssist_int = -0x7FFF;
    else
        thetaAssist_int = (qint16)thetaAssist;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeHapticBackdriveAssist);
    sendPacket.load(xAssist_int);
    sendPacket.load(yAssist_int);
    sendPacket.load(thetaAssist_int);
    sendCommand();
}

void CelluloBluetooth::setVisualEffect(CelluloBluetoothEnums::VisualEffect effect, QColor color, int value){
    if(value > 0xFF)
        value = 0xFF;
    else if(value < 0)
        value = 0;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetVisualEffect);
    sendPacket.load((quint8)effect);
    sendPacket.load((quint8)color.red());
    sendPacket.load((quint8)color.green());
    sendPacket.load((quint8)color.blue());
    sendPacket.load((quint8)value);
    sendCommand();
}

void CelluloBluetooth::polyBezierInit(const QVector2D& point0){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypePolyBezierInit);
    sendPacket.load((float)point0.x());
    sendPacket.load((float)point0.y());
    sendCommand();
}

void CelluloBluetooth::polyBezierAppend(const QVector2D& point1, const QVector2D& point2, const QVector2D& point3){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypePolyBezierAppend);
    sendPacket.load((float)point1.x());
    sendPacket.load((float)point1.y());
    sendPacket.load((float)point2.x());
    sendPacket.load((float)point2.y());
    sendPacket.load((float)point3.x());
    sendPacket.load((float)point3.y());
    sendCommand();
}

void CelluloBluetooth::polyBezierSetFromZone(CelluloZone* zone){
    CelluloZonePolyBezier* bzone = qobject_cast<CelluloZonePolyBezier*>(zone);
    if(bzone)
        bzone->sendPathToRobot(this);
    else
        qWarning() << "CelluloBluetooth::polyBezierSetFromZone(): zone must be castable to CelluloZonePolyBezier.";
}

void CelluloBluetooth::setGoalPolyBezier(float v, float w){
    v *= GOAL_VEL_FACTOR_SHARED;
    int w_ = (int)(w*GOAL_VEL_FACTOR_SHARED);

    quint16 vi;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    if(w_ < -0x7FFF)
        w_ = -0x7FFF;
    else if(w_ > 0x7FFF)
        w_ = 0x7FFF;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalPolyBezier);
    sendPacket.load(vi);
    sendPacket.load((qint16)w_);
    sendCommand();
}

void CelluloBluetooth::setGoalPolyBezierAligned(float v, float theta, float w){
    v *= GOAL_VEL_FACTOR_SHARED;
    theta *= GOAL_POSE_FACTOR_SHARED;
    w *= GOAL_VEL_FACTOR_SHARED;

    quint16 vi, thetai, wi;

    if(v > (float)0xFFFF)
        vi = 0xFFFF;
    else
        vi = (quint16)v;

    if(theta > (float)0xFFFF)
        thetai = 0xFFFF;
    else
        thetai = (quint16)theta;

    if(w > (float)0xFFFF)
        wi = 0xFFFF;
    else
        wi = (quint16)w;

    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeSetGoalPolyBezierAligned);
    sendPacket.load(vi);
    sendPacket.load(thetai);
    sendPacket.load(wi);
    sendCommand();
}

void CelluloBluetooth::reset(){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeReset);
    sendCommand();
}

void CelluloBluetooth::shutdown(){
    sendPacket.clear();
    sendPacket.setCmdPacketType(CelluloBluetoothPacket::CmdPacketTypeShutdown);
    sendCommand();
}
