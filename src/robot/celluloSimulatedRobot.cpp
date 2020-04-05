#include "celluloSimulatedRobot.h"
#include <math.h>

#define abs(X) ((X) >= 0 ? (X) : -(X))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
#define PI 3.14159265359f

CelluloSimulatedRobot::CelluloSimulatedRobot(){
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

void CelluloSimulatedRobot::setGoalPose(int x, int y, int theta, float v, float w)
{
    goalPoseX = x;
    goalPoseY = y;
    goalPoseTheta = theta;
    goalPoseMaxV = v;
    goalPoseMaxW = w;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobot::setGoalPosition(int x, int y, float v){
    goalPoseX = x;
    goalPoseY = y;
    goalPoseMaxV = v;
    goalPoseMaxW = 0;
    relevantGoalsReached = false;
}

void CelluloSimulatedRobot::setGoalXCoordinate(int x, float v){
    goalPoseX = x;
    goalPoseMaxV = v;
    goalPoseMaxW = 0;
    relevantGoalsReached = false;
    //***************************** CLEAR D AND I
}

void CelluloSimulatedRobot::setGoalYCoordinate(int y, float v){
    goalPoseY = y;
    goalPoseMaxV = v;
    goalPoseMaxW = 0;
    relevantGoalsReached = false;
    //***************************** CLEAR D AND I
}

void CelluloSimulatedRobot::setGoalOrientation(int theta, float w){
    goalPoseTheta = theta;
    goalPoseMaxV = 0;
    goalPoseMaxW = w;
    relevantGoalsReached = false;
    //***************************** CLEAR D AND I
}

void CelluloSimulatedRobot::setGoalVelocity(float vx, float vy, float w){
    vxGlobalGoalTracker = vx;
    vyGlobalGoalTracker = vy;
    wGlobalGoalTracker = w;
}

void CelluloSimulatedRobot::clearTracking(){
    goalPoseX = 0;
    goalPoseY = 0;
    goalPoseTheta = 0;
    goalPoseMaxV = 0;
    goalPoseMaxW = 0;

    //added
    vxGlobalGoalTracker = 0;
    vyGlobalGoalTracker = 0;
    wGlobalGoalTracker = 0;
}

void CelluloSimulatedRobot::trackPosition(){

    //Get difference of goal and actual x, y in grid coordinates
    float xDiff = (goalPoseX - poseX)/100.0f;
    float yDiff = (goalPoseY - poseY)/100.0f;

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

