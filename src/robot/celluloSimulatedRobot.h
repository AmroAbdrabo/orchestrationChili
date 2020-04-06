#ifndef CELLULOSIMULATEDLOGIC_H
#define CELLULOSIMULATEDLOGIC_H

#define W_MAX 25.0f
#define VXY_MAX_INCREMENT 20.0f                    ///< Maximum increment for Vx,Vy in pose/position tracking
#define W_MAX_INCREMENT 0.5f                       ///< Maximum increment for w in pose tracking

/**
 * @brief List of motion controllers
 */
typedef enum {
    MOTION_TRACKER_NONE = 0,           ///< No motion controller is active
    MOTION_TRACKER_VELOCITY,           ///< Tracking global velocity
    MOTION_TRACKER_POSE,               ///< Tracking pose
    MOTION_TRACKER_POSITION,           ///< Tracking position
    MOTION_TRACKER_X_COORDINATE,       ///< Tracking just the X coordinate
    MOTION_TRACKER_Y_COORDINATE,       ///< Tracking just the Y coordinate
    MOTION_TRACKER_ORIENTATION,        ///< Tracking orientation
    MOTION_TRACKER_X_THETA_COORDINATE, ///< Tracking X and Theta coordinates
    MOTION_TRACKER_Y_THETA_COORDINATE, ///< Tracking Y and Theta coordinates
    MOTION_TRACKER_POLYBEZIER,         ///< Tracking a composite Bézier curve
    MOTION_TRACKER_POLYBEZIER_ALIGNED, ///< Tracking a composite Bézier curve with tangent orientation
    MOTION_TRACKER_NUM_TRACKERS,
    MOTION_TRACKER_INVALID = -1
} MOTION_TRACKER;


class CelluloSimulatedRobot {
public:
    MOTION_TRACKER currentMotionTracker = MOTION_TRACKER_NONE; ///< Currently active tracker

    float poseX;
    float poseY;
    float poseTheta;

    float goalPoseX;
    float goalPoseY;
    float goalPoseTheta;
    float goalPoseMaxV;
    float goalPoseMaxW;

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
    void setGoalXThetaCoordinate(float x, float theta, float v, float w);
    void setGoalYThetaCoordinate(float y, float theta, float v, float w);
    void setGoalVelocity(float vx, float vy, float w);
    void clearTracking();
    void trackPosition();
    void trackXCoordinate();
    void trackYCoordinate();
    void trackOrientation(bool goalless);
    float getVectorOrientation(float x, float y);
    void updatePose(float curX, float curY, float theta);
};

#endif // CELLULOSIMULATEDLOGIC_H
