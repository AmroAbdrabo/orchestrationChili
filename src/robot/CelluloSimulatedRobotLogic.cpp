#include "CelluloSimulatedRobotLogic.h"
#include <math.h>
#include <QDebug>

#define abs(X) ((X) >= 0 ? (X) : -(X))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
#define PI 3.14159265359f


CelluloSimulatedRobotLogic::CelluloSimulatedRobotLogic(){
    goalPoseX = 0;
    goalPoseY = 0;
    goalPoseTheta = 0;
    goalPoseMaxV = 0;
    goalPoseMaxW = 0;

    poseX = 0;
    poseY = 0;
    poseTheta = 0;
    bcastPeriod = 0;

    marginXY = 0;
    marginTheta = 0;

    xGoalReached = false;
    yGoalReached = false;
    thetaGoalReached = false;
    relevantGoalsReached = false;

    vxGlobalGoalTracker = 0; ///Global Vx dictacted by active tracker
    vyGlobalGoalTracker = 0; ///Global Vy dictacted by active tracker
    wGlobalGoalTracker = 0; ///Global w dictacted by active tracker
}


void CelluloSimulatedRobotLogic::setGoalPose(float x, float y, float theta, float v, float w)
{
    goalPoseX = x;
    goalPoseY = y;
    goalPoseTheta = theta;
    goalPoseMaxV = v;
    goalPoseMaxW = w;
    currentMotionTracker = MOTION_TRACKER_POSE;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobotLogic::setGoalPosition(float x, float y, float v){
    goalPoseX = x;
    goalPoseY = y;
    goalPoseMaxV = v;
    goalPoseMaxW = 0;
    currentMotionTracker = MOTION_TRACKER_POSITION;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobotLogic::setGoalXCoordinate(float x, float v){
    goalPoseX = x;
    goalPoseMaxV = v;
    goalPoseMaxW = 0;
    currentMotionTracker = MOTION_TRACKER_X_COORDINATE;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobotLogic::setGoalYCoordinate(float y, float v){
    goalPoseY = y;
    goalPoseMaxV = v;
    goalPoseMaxW = 0;
    currentMotionTracker = MOTION_TRACKER_Y_COORDINATE;
    relevantGoalsReached = false;
    //***************************** CLEAR D AND I
}

void CelluloSimulatedRobotLogic::setGoalOrientation(float theta, float w){
    goalPoseTheta = theta;
    goalPoseMaxV = 0;
    goalPoseMaxW = w;
    currentMotionTracker = MOTION_TRACKER_ORIENTATION;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobotLogic::setGoalXThetaCoordinate(float x, float theta, float v, float w)
{
    goalPoseX = x;
    goalPoseTheta = theta;
    goalPoseMaxV = v;
    goalPoseMaxW = w;
    currentMotionTracker = MOTION_TRACKER_X_THETA_COORDINATE;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobotLogic::setGoalYThetaCoordinate(float y, float theta, float v, float w)
{
    goalPoseY = y;
    goalPoseTheta = theta;
    goalPoseMaxV = v;
    goalPoseMaxW = w;
    currentMotionTracker = MOTION_TRACKER_Y_THETA_COORDINATE;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobotLogic::setGoalVelocity(float vx, float vy, float w){
    vxGlobalGoalTracker = vx;
    vyGlobalGoalTracker = vy;
    wGlobalGoalTracker = w;
    currentMotionTracker = MOTION_TRACKER_VELOCITY;
}

void CelluloSimulatedRobotLogic::clearTracking(){
    goalPoseX = 0;
    goalPoseY = 0;
    goalPoseTheta = 0;
    goalPoseMaxV = 0;
    goalPoseMaxW = 0;

    currentMotionTracker = MOTION_TRACKER_NONE;
    //added to support simply setting the velocity to desired velocity
    vxGlobalGoalTracker = 0;
    vyGlobalGoalTracker = 0;
    wGlobalGoalTracker = 0;
}

void CelluloSimulatedRobotLogic::trackXCoordinate() {

    //Get difference of goal and actual x in grid coordinates
    float xDiff = (goalPoseX - poseX)/*/100.0f*/;

    xGoalReached = abs(xDiff) < marginXY;

    float vxGlobalGoalNew;

    //Maximum linear velocity is zero or goal is reached, do not track linear position
    if(goalPoseMaxV == 0 || xGoalReached)
        vxGlobalGoalNew = 0;

    //X goal remains
    else{
        vxGlobalGoalNew = pPoseXY*xDiff;
        if(vxGlobalGoalNew > goalPoseMaxV)
            vxGlobalGoalNew = goalPoseMaxV;
        else if(vxGlobalGoalNew < -goalPoseMaxV)
            vxGlobalGoalNew = -goalPoseMaxV;
    }

    //Update goal velocities slowly over time
    if(vxGlobalGoalNew > vxGlobalGoalTracker + VXY_MAX_INCREMENT)
        vxGlobalGoalTracker = vxGlobalGoalTracker + VXY_MAX_INCREMENT;
    else if(vxGlobalGoalNew < vxGlobalGoalTracker - VXY_MAX_INCREMENT)
        vxGlobalGoalTracker = vxGlobalGoalTracker - VXY_MAX_INCREMENT;
    else
        vxGlobalGoalTracker = vxGlobalGoalNew;

}

void CelluloSimulatedRobotLogic::trackYCoordinate()
{
    //Get difference of goal and actual y in grid coordinates
        float yDiff = (goalPoseY - poseY)/*/100.0f*/;

        yGoalReached = abs(yDiff) < marginXY;

        float vyGlobalGoalNew;

        //Maximum linear velocity is zero or goal is reached, do not track linear position
        if(goalPoseMaxV == 0 || yGoalReached)
            vyGlobalGoalNew = 0;

        //Y goal remains
        else{
            vyGlobalGoalNew = pPoseXY*yDiff;
            if(vyGlobalGoalNew > goalPoseMaxV)
                vyGlobalGoalNew = goalPoseMaxV;
            else if(vyGlobalGoalNew < -goalPoseMaxV)
                vyGlobalGoalNew = -goalPoseMaxV;
        }

        //Update goal velocities slowly over time
        if(vyGlobalGoalNew > vyGlobalGoalTracker + VXY_MAX_INCREMENT)
            vyGlobalGoalTracker = vyGlobalGoalTracker + VXY_MAX_INCREMENT;
        else if(vyGlobalGoalNew < vyGlobalGoalTracker - VXY_MAX_INCREMENT)
            vyGlobalGoalTracker = vyGlobalGoalTracker - VXY_MAX_INCREMENT;
        else
            vyGlobalGoalTracker = vyGlobalGoalNew;
}

void CelluloSimulatedRobotLogic::trackOrientation(bool goalless) {
    //Get difference of goal and actual orientation between -PI and PI in radians
    float thetaDiff = (goalPoseTheta - poseTheta);
    while(thetaDiff < -180)
        thetaDiff += 360;
    while(thetaDiff > 180)
        thetaDiff -= 360;

    thetaGoalReached = goalless ? false : abs(thetaDiff) < marginTheta;

    float wGlobalGoalNew;

    //If maximum angular velocity is zero, do not track orientation
    if(goalPoseMaxW == 0 || thetaGoalReached)
        wGlobalGoalNew = 0;
    else{
        wGlobalGoalNew = (goalless ? pPoseThetaGoalless : pPoseTheta)*thetaDiff;
        if(wGlobalGoalNew > goalPoseMaxW)
            wGlobalGoalNew = goalPoseMaxW;
        else if(wGlobalGoalNew < -goalPoseMaxW)
            wGlobalGoalNew = -goalPoseMaxW;
    }

    //Update goal velocity slowly over time
    if(wGlobalGoalNew > wGlobalGoalTracker + W_MAX_INCREMENT)
        wGlobalGoalTracker = wGlobalGoalTracker + W_MAX_INCREMENT;
    else if(wGlobalGoalNew < wGlobalGoalTracker - W_MAX_INCREMENT)
        wGlobalGoalTracker = wGlobalGoalTracker - W_MAX_INCREMENT;
    else
        wGlobalGoalTracker = wGlobalGoalNew;
}



void CelluloSimulatedRobotLogic::trackPosition(){
    //TODO find a way to link x, y and poseX, poseY to avoid redundancy
    //added because x, y and in bluetooth class..

    //Get difference of goal and actual x, y in grid coordinates
    float xDiff = (goalPoseX - poseX)/*100.0f*/;
    float yDiff = (goalPoseY - poseY)/*100.0f*/;

    xGoalReached = abs(xDiff) < marginXY;
    yGoalReached = abs(yDiff) < marginXY;

    float vxGlobalGoalNew;
    float vyGlobalGoalNew;

    //Maximum linear velocity is zero, do not track linear position
    if(goalPoseMaxV == 0){
        vxGlobalGoalNew = 0;
        vyGlobalGoalNew = 0;
    }

    //Only x goal remains
    else if(!xGoalReached && yGoalReached){
        vyGlobalGoalNew = 0;
        vxGlobalGoalNew = pPoseXY*xDiff;
        if(vxGlobalGoalNew > goalPoseMaxV)
            vxGlobalGoalNew = goalPoseMaxV;
        else if(vxGlobalGoalNew < -goalPoseMaxV)
            vxGlobalGoalNew = -goalPoseMaxV;
    }

    //Only y goal remains
    else if(xGoalReached && !yGoalReached){
        vxGlobalGoalNew = 0;
        vyGlobalGoalNew = pPoseXY*yDiff;
        if(vyGlobalGoalNew > goalPoseMaxV)
            vyGlobalGoalNew = goalPoseMaxV;
        else if(vyGlobalGoalNew < -goalPoseMaxV)
            vyGlobalGoalNew = -goalPoseMaxV;
    }

    //Both goals reached
    else if(xGoalReached && yGoalReached){
        vxGlobalGoalNew = 0;
        vyGlobalGoalNew = 0;
    }

    //Both goals remain
    else{
        vxGlobalGoalNew = pPoseXY*xDiff;
        vyGlobalGoalNew = pPoseXY*yDiff;

        //Scale down both x and y to have given max. linear velocity
        float vxyGlobalGoalNew = sqrt(vxGlobalGoalNew*vxGlobalGoalNew + vyGlobalGoalNew*vyGlobalGoalNew);
        if(vxyGlobalGoalNew > goalPoseMaxV){
            vxGlobalGoalNew = vxGlobalGoalNew*goalPoseMaxV/vxyGlobalGoalNew;
            vyGlobalGoalNew = vyGlobalGoalNew*goalPoseMaxV/vxyGlobalGoalNew;
        }
    }

    //Update goal velocities slowly over time
    if(vxGlobalGoalNew > vxGlobalGoalTracker + VXY_MAX_INCREMENT)
        vxGlobalGoalTracker = vxGlobalGoalTracker + VXY_MAX_INCREMENT;
    else if(vxGlobalGoalNew < vxGlobalGoalTracker - VXY_MAX_INCREMENT)
        vxGlobalGoalTracker = vxGlobalGoalTracker - VXY_MAX_INCREMENT;
    else
        vxGlobalGoalTracker = vxGlobalGoalNew;

    if(vyGlobalGoalNew > vyGlobalGoalTracker + VXY_MAX_INCREMENT)
        vyGlobalGoalTracker = vyGlobalGoalTracker + VXY_MAX_INCREMENT;
    else if(vyGlobalGoalNew < vyGlobalGoalTracker - VXY_MAX_INCREMENT)
        vyGlobalGoalTracker = vyGlobalGoalTracker - VXY_MAX_INCREMENT;
    else
        vyGlobalGoalTracker = vyGlobalGoalNew;
}

void CelluloSimulatedRobotLogic::updatePose(float curX, float curY, float curTheta) {
    poseX = curX;
    poseY = curY;
    poseTheta = curTheta;

    //TODO UNDERSTAND HOW KIDNAPPING IS CURRENTLY DONE!
    //Turn off everything if kidnapped
   /* if(kidnapped){
        zeroMeasuredVelocities();
        zeroMotorOutputs();
        return;
    }*/

    //Calculate desired goal velocities depending on the current motion tracker; and calculate whether goals are reached
    bool relevantGoalsReachedNow = false;
    switch(currentMotionTracker){
        case MOTION_TRACKER_POSITION:
            trackPosition();
            wGlobalGoalTracker = 0;
            relevantGoalsReachedNow = xGoalReached && yGoalReached;
            break;

        case MOTION_TRACKER_X_COORDINATE:
            trackXCoordinate();
            vyGlobalGoalTracker = 0;
            wGlobalGoalTracker = 0;
            relevantGoalsReachedNow = xGoalReached;
            break;

        case MOTION_TRACKER_Y_COORDINATE:
            trackYCoordinate();
            vxGlobalGoalTracker = 0;
            wGlobalGoalTracker = 0;
            relevantGoalsReachedNow = yGoalReached;
            break;

        case MOTION_TRACKER_POSE:
            trackPosition();
            trackOrientation(false);
            relevantGoalsReachedNow = xGoalReached && yGoalReached && thetaGoalReached;
            break;

        case MOTION_TRACKER_ORIENTATION:
            vxGlobalGoalTracker = 0;
            vyGlobalGoalTracker = 0;
            trackOrientation(false);
            relevantGoalsReachedNow = thetaGoalReached;
            break;

        case MOTION_TRACKER_X_THETA_COORDINATE:
            trackXCoordinate();
            vyGlobalGoalTracker = 0;
            trackOrientation(false);
            relevantGoalsReachedNow = xGoalReached && thetaGoalReached;
            break;

        case MOTION_TRACKER_Y_THETA_COORDINATE:
            trackYCoordinate();
            vxGlobalGoalTracker = 0;
            trackOrientation(false);
            relevantGoalsReachedNow = yGoalReached && thetaGoalReached;
            break;

        //these cases are not needed yet
        /*case MOTION_TRACKER_POLYBEZIER:
            trackPolyBezier(false);
            relevantGoalsReachedNow = polyBezierGoalReached;
            break;

        case MOTION_TRACKER_POLYBEZIER_ALIGNED:
            trackPolyBezier(true);
            relevantGoalsReachedNow = polyBezierGoalReached;
            break;*/

        case MOTION_TRACKER_NONE:
            vxGlobalGoalTracker = 0;
            vyGlobalGoalTracker = 0;
            wGlobalGoalTracker = 0;
            break;

        default:
            break;
    }

    if(relevantGoalsReachedNow && !relevantGoalsReached) {
        //TODO should i do something here?
        qDebug() << "Goal reached!";
    }
    relevantGoalsReached = relevantGoalsReachedNow;
}

void CelluloSimulatedRobotLogic::setVisualEffect(Cellulo::CelluloBluetoothEnums::VisualEffect effect, QColor color, int value)
{
    if(effect == Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectConstAll){
        this->color = color;
    }


}
