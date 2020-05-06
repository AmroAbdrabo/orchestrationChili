#ifndef CELLULOSIMULATEDLOGIC_H
#define CELLULOSIMULATEDLOGIC_H

#include <QColor>
#include "../comm/CelluloBluetoothEnums.h"

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


class CelluloSimulatedRobotLogic {
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
    const float pPoseTheta = 0.1f;        ///< Proportional component of goal pose controller for theta
    const float pPoseThetaGoalless = 0.08f; ///< Proportional component of goal pose controller for theta, when there is no fixed goal

    float vxGlobalGoalTracker; ///Global Vx dictacted by active tracker
    float vyGlobalGoalTracker; ///Global Vy dictacted by active tracker
    float wGlobalGoalTracker; ///Global w dictacted by active tracker

    CelluloSimulatedRobotLogic();

    /**
     * @brief Sets a goal pose to track
     *
     * @param x X position in grid coordinates times 100
     * @param y Y position in grid coordinates times 100
     * @param theta Orientation in degrees times 100
     * @param v Maximum linear velocity to track pose
     * @param w Maximum angular velocity to track pose in rad/s
     */
    void setGoalPose(float x, float y, float theta, float v, float w);

    /**
     * @brief Sets a goal position to track
     *
     * @param x X position in grid coordinates times 100
     * @param y Y position in grid coordinates times 100
     * @param v Maximum linear velocity to track position
     */
    void setGoalPosition(float x, float y, float v);

    /**
     * @brief Sets a goal Y coordinate to track
     *
     * @param y Y position in grid coordinates times 100
     * @param v Maximum linear velocity to track position
     */
    void setGoalYCoordinate(float y, float v);

    /**
     * @brief Sets a goal X coordinate to track
     *
     * @param x X position in grid coordinates times 100
     * @param v Maximum linear velocity to track position
     */
    void setGoalXCoordinate(float x, float v);

    /**
     * @brief Sets a goal orientation to track
     *
     * @param theta Orientation in degrees times 100
     * @param w Maximum angular velocity to track pose
     */
    void setGoalOrientation(float theta, float w);

    /**
     * @brief Sets a goal X and Theta coordinate to track
     *
     * @param x X position in grid coordinates times 100
     * @param theta Orientation in degrees times 100
     * @param v Maximum linear velocity to track pose
     * @param w Maximum angular velocity to track pose
     */
    void setGoalXThetaCoordinate(float x, float theta, float v, float w);

    /**
     * @brief Sets a goal Y and Theta coordinate to track
     *
     * @param y Y position in grid coordinates times 100
     * @param theta Orientation in degrees times 100
     * @param v Maximum linear velocity to track pose
     * @param w Maximum angular velocity to track pose
     */
    void setGoalYThetaCoordinate(float y, float theta, float v, float w);

    /**
     * @brief Sets a goal velocity
     *
     * @param vx X velocity in world frame in mm/s
     * @param vy Y velocity in world frame in mm/s
     * @param w Angular velocity in world frame in rad/s
     */
    void setGoalVelocity(float vx, float vy, float w);

    /**
     * @brief Clears pose/position/velocity goals
     */
    void clearTracking();

    /**
     * @brief Calculates necessary velocities to reach given position
     */
    void trackPosition();

    /**
    * @brief Calculates necessary velocities to reach given X coordindate
     */
    void trackXCoordinate();

    /**
     * @brief Calculates necessary velocities to reach given Y coordindate
     */
    void trackYCoordinate();

    /**
     * @brief Calculates necessary angular velocity to reach given orientation
     *
     * @param goalless Will not turn off tracking when within marginTheta, thetaGoalReached will always be false
     */
    void trackOrientation(bool goalless);

    /**
     * @brief Calculates the orientation of given vector
     *
     * @param x X component of vector
     * @param y Y component of vector
     * @return Orientation in degrees times 100
     */
    float getVectorOrientation(float x, float y);

    /**
     * @brief Runs regular motion control tasks
     */
    void updatePose(float curX, float curY, float theta);

};

#endif // CELLULOSIMULATEDLOGIC_H
