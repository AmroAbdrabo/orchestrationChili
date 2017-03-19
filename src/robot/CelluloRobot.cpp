/*
 * Copyright (C) 2017 EPFL
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

#include "CelluloRobot.h"

CelluloRobot::CelluloRobot(QQuickItem* parent) : CelluloBluetooth(parent){
    poseVelControlEnabled = false;
    poseVelControlPeriod = 20;
    vxyw = QVector3D(0,0,0);
}

CelluloRobot::~CelluloRobot(){}

void CelluloRobot::setPoseVelControlEnabled(bool enabled){

}

void CelluloRobot::setPoseVelControlPeriod(int period){

}

void CelluloRobot::initialize(){
    if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected){
        setPoseBcastPeriod(poseVelControlPeriod);
        setTimestampingEnabled(true);

        velEstimateNeedsReset = true;
        lastPose = Qt.vector3d(0,0,0);
        lastTime = 0;

        nextGoalPoseVelRequested();
    }
}

void CelluloRobot::estimateVelocities(){
    var newTime = lastTimestamp;
    var deltaTime = newTime - lastTime;
    var newPose = Qt.vector3d(x,y,theta);

    var newVxyw = newPose.minus(lastPose);
    while(newVxyw.z <= -180)
        newVxyw.z += 360;
    while(newVxyw.z > 180)
        newVxyw.z -= 360;
    newVxyw.z = newVxyw.z*Math.PI/180;

    newVxyw = newVxyw.times(1000/deltaTime);
    if(bcastPeriodMin < deltaTime && deltaTime < bcastPeriodMax){
        if(velEstimateNeedsReset){
            velEstimateNeedsReset = false;
            vxyw = newVxyw;
        }
        else
            vxyw = vxyw.times(vMu).plus(newVxyw.times(1 - vMu));
    }
    else if(bcastPeriodMax <= deltaTime){
        velEstimateNeedsReset = true;
        vxyw = newVxyw;
    }
    else
        velEstimateNeedsReset = true;

    if(vxyw.x > maxEstimatedXYVel)
        vxyw.x = maxEstimatedXYVel;
    else if(vxyw.x < -maxEstimatedXYVel)
        vxyw.x = -maxEstimatedXYVel;
    if(vxyw.y > maxEstimatedXYVel)
        vxyw.y = maxEstimatedXYVel;
    else if(vxyw.y < -maxEstimatedXYVel)
        vxyw.y = -maxEstimatedXYVel;
    if(vxyw.z > maxEstimatedW)
        vxyw.z = maxEstimatedW;
    else if(vxyw.z < -maxEstimatedW)
        vxyw.z = -maxEstimatedW;

    lastPose = newPose;
    lastTime = newTime;
}

void CelluloRobot::commandVelocities(){
    nextGoalPoseVelRequested();

    //Goal velocity component
    var commandVel = goalVel.times(kGoalVel);

    //Goal velocity error component
    var velErr = goalVel.minus(vxyw);
    commandVel = commandVel.plus(velErr.times(kGoalVelErr));

    //Goal pose error component
    var poseErr = goalPose.minus(Qt.vector3d(x,y,theta));
    while(poseErr.z > 180)
        poseErr.z -= 360;
    while(poseErr.z <= -180)
        poseErr.z += 360;
    poseErr.z = poseErr.z/180*Math.PI;
    commandVel = commandVel.plus(poseErr.times(kGoalPoseErr));

    //Clamp goal velocity
    if(commandVel.x > 200)
        commandVel.x = 200;
    else if(commandVel.x < -200)
        commandVel.x = -200;
    if(commandVel.y > 200)
        commandVel.y = 200;
    else if(commandVel.y < -200)
        commandVel.y = -200;
    if(commandVel.z > 10)
        commandVel.z = 10;
    else if(commandVel.z < -10)
        commandVel.z = -10;

    setGoalVelocity(commandVel.x, commandVel.y, commandVel.z);
}
