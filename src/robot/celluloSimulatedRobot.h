#ifndef CELLULOSIMULATEDLOGIC_H
#define CELLULOSIMULATEDLOGIC_H

#define W_MAX 25.0f
#define VXY_MAX_INCREMENT 20.0f                    ///< Maximum increment for Vx,Vy in pose/position tracking
#define W_MAX_INCREMENT 0.5f                       ///< Maximum increment for w in pose tracking

class CelluloSimulatedRobot {
public:
    int goalPoseX;
    int goalPoseY;
    int goalPoseTheta;
    int goalPoseMaxV;
    int goalPoseMaxW;

    int poseX;
    int poseY;
    int poseTheta;
    int bcastPeriod;

    float marginXY;
    float marginTheta;

    bool xGoalReached;
    bool yGoalReached;
    bool thetaGoalReached;
    bool relevantGoalsReached;

    const float pPoseXY = 2.0f;             ///< Proportional component of goal pose controller for x and y
    const float pPoseTheta = 0.1f;          ///< Proportional component of goal pose controller for theta
    const float pPoseThetaGoalless = 0.08f; ///< Proportional component of goal pose controller for theta, when there is no fixed goal

    float vxGlobalGoalTracker; ///Global Vx dictacted by active tracker
    float vyGlobalGoalTracker; ///Global Vy dictacted by active tracker
    float wGlobalGoalTracker; ///Global w dictacted by active tracker

    CelluloSimulatedRobot();

    void setGoalPose(float x, float y, float theta, float v, float w);
    void setGoalPosition(float x, float y, float v);
    void setGoalYCoordinate(float y, float v);
    void setGoalXCoordinate(float x, float v);
    void setGoalOrientation(float theta, float w);
    void setGoalVelocity(float vx, float vy, float w);
    void clearTracking();
    void trackPosition();

};

#endif // CELLULOSIMULATEDLOGIC_H
