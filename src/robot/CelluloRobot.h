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
 * @file CelluloRobot.h
 * @brief Object that directly represents a Cellulo robot
 * @author Ayberk Özgür
 * @date 2015-05-20
 */

#ifndef CELLULOROBOT_H
#define CELLULOROBOT_H

#include <QVector3D>

#include "../comm/CelluloBluetooth.h"

class CelluloRobot : public CelluloBluetooth {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(QVector3D vxyw READ getVxyw NOTIFY vxywChanged)
    Q_PROPERTY(qreal vx READ getVx NOTIFY vxywChanged)
    Q_PROPERTY(qreal vy READ getVy NOTIFY vxywChanged)
    Q_PROPERTY(qreal w READ getW NOTIFY vxywChanged)

    Q_PROPERTY(bool poseVelControlEnabled READ getPoseVelControlEnabled WRITE setPoseVelControlEnabled NOTIFY poseVelControlEnabledChanged)
    Q_PROPERTY(int poseVelControlPeriod READ getPoseVelControlPeriod WRITE setPoseVelControlPeriod NOTIFY poseVelControlPeriodChanged)

    Q_PROPERTY(QVector3D poseVelControlKGoalVel MEMBER poseVelControlKGoalVel)
    Q_PROPERTY(QVector3D poseVelControlKGoalVelErr MEMBER poseVelControlKGoalVelErr)
    Q_PROPERTY(QVector3D poseVelControlKGoalPoseErr MEMBER poseVelControlKGoalPoseErr)

    Q_PROPERTY(QList<bool> keysTouched READ getKeysTouched NOTIFY keysTouchedChanged)
    Q_PROPERTY(QList<bool> keysLongTouched READ getKeysLongTouched NOTIFY keysLongTouchedChanged)

public:

    /**
     * @brief Creates a new Cellulo robot representation
     *
     * @param parent Parent of this QML item
     */
    explicit CelluloRobot(QQuickItem* parent = 0);

    /**
     * @brief Destroys this Cellulo robot representation
     */
    virtual ~CelluloRobot();

    /**
     * @brief Gets the current velocities
     *
     * @return Robot velocities: x,y in mm/s, z in rad/s (representing w)
     */
    QVector3D getVxyw() const { return vxyw; }

    /**
     * @brief Gets the current x velocity
     *
     * @return X velocity in mm/s
     */
    qreal getVx() const { return vxyw.x(); }

    /**
     * @brief Gets the current y velocity
     *
     * @return Y velocity in mm/s
     */
    qreal getVy() const { return vxyw.y(); }

    /**
     * @brief Gets the current angular velocity
     *
     * @return W velocity in rad/s
     */
    qreal getW() const { return vxyw.z(); }

    /**
     * @brief Gets whether the simultaneous pose and velocity controller is enabled
     *
     * @return Whether the simultaneous pose and velocity controller is enabled, false by default
     */
    bool getPoseVelControlEnabled() const { return poseVelControlEnabled; }

    /**
     * @brief Sets whether the simultaneous pose and velocity controller is enabled
     *
     * @param enabled Whether the simultaneous pose and velocity controller is enabled
     */
    void setPoseVelControlEnabled(bool enabled);

    /**
     * @brief Gets the simultaneous pose and velocity controller period
     *
     * @return The simultaneous pose and velocity controller period in milliseconds
     */
    int getPoseVelControlPeriod() const { return poseVelControlPeriod; }

    /**
     * @brief Sets the simultaneous pose and velocity controller period
     *
     * @param period The simultaneous pose and velocity controller period in milliseconds
     */
    void setPoseVelControlPeriod(int period);

    /**
     * @brief Gets the list of whether the 6 touch keys are touched
     *
     * @return List of whether the 6 touch keys are touched
     */
    QList<bool> getKeysTouched() const { return keysTouched; }

    /**
     * @brief Gets the list of whether the 6 touch keys are long touched
     *
     * @return List of whether the 6 touch keys are long touched
     */
    QList<bool> getKeysLongTouched() const { return keysLongTouched; }

signals:

    /**
     * @brief Emitted when the linear/angular velocity changes
     */
    void vxywChanged();

    /**
     * @brief Emitted when the simultaneous pose and velocity controller is enabled/disabled
     */
    void poseVelControlEnabledChanged();

    /**
     * @brief Emitted when the simultaneous pose and velocity controller period changes
     */
    void poseVelControlPeriodChanged();

    /**
     * @brief Emitted when the controller needs the next goal pose and velocity
     *
     * Upon receiving this signal, setGoalPoseAndVelocity() should be called by the user if a user control loop that
     * cycles on each received pose of the robot is present.
     */
    void nextGoalPoseVelRequested();

    /**
     * @brief Emitted when a key is touched/released
     */
    void keysTouchedChanged();

    /**
     * @brief Emitted when a key is long touched/released
     */
    void keysLongTouchedChanged();

private slots:

    /**
     * @brief Marks the velocity estimate to be reset on the next received pose
     */
    void resetVelEstimate();

    /**
     * @brief Initializes the robot to the settings necessary to run the controllers, initializes controllers
     */
    void initialize();

    /**
     * @brief Calculates new velocity estimates, new goals for velocity and pose
     */
    void spinControllers();

    /**
     * @brief Updates the key touched properties if necessary
     *
     * @param key Index of the key that is touched
     */
    void touchKey(int key);

    /**
     * @brief Updates the key touched properties if necessary
     *
     * @param key Index of the key that is released
     */
    void releaseKey(int key);

    /**
     * @brief Updates the key touched properties if necessary
     *
     * @param key Index of the key that is long touched
     */
    void longTouchKey(int key);

public slots:

    /**
     * @brief Sets the simultaneous pose and velocity goal of the robot, i.e the robot tries to be at the pose and move with the desired velocity while there
     *
     * @param x X coordinate (larger than 0mm)
     * @param y Y coordinate (larger than 0mm)
     * @param theta Orientation (between -180 degrees and 180 degrees)
     * @param Vx X velocity (between -185 mm/s and and 185 mm/s)
     * @param Vy Y velocity (between -185 mm/s and and 185 mm/s)
     * @param w Angular velocity (between -7.5 rad/s and 7.5 rad/s)
     */
    void setGoalPoseAndVelocity(qreal x, qreal y, qreal theta, qreal Vx, qreal Vy, qreal w);

private:

    QVector3D vxyw;                       ///< Robot velocities: x,y in mm/s, z in rad/s (representing w)

    bool poseVelControlEnabled;           ///< Whether the simultaneous pose and velocity controller is enabled, must be enabled by the user
    int poseVelControlPeriod;             ///< Desired pose/velocity control period in ms, set to 0 for highest possible frequency

    QVector3D poseVelControlKGoalVel;     ///< Goal velocity coefficients when tracking pose/velocity
    QVector3D poseVelControlKGoalVelErr;  ///< Goal velocity error coefficients when tracking pose/velocity
    QVector3D poseVelControlKGoalPoseErr; ///< Goal pose error coefficients when tracking pose/velocity

    QVector3D poseVelControlGoalPose;     ///< Latest x, y, theta goal
    QVector3D poseVelControlGoalVel;      ///< Latest Vx, Vy, w goal
    bool velEstimateNeedsReset;           ///< If true, velocity estimate variables will be reset in the next cycle
    QVector3D lastPose;                   ///< Previous robot pose
    qreal lastLastTimestamp;              ///< Previous timestamp

    static const qreal maxEstimatedXYVel; ///< Clamp limit for the estimated linear robot velocity, in mm/s
    static const qreal maxEstimatedW;     ///< Clamp limit for the estimated angular robot velocity, in rad/s
    static const qreal vMu;               ///< Smoothing coefficient for velocity estimate

    QList<bool> keysTouched;              ///< Whether keys are touched
    QList<bool> keysLongTouched;          ///< Whether keys are touched

    /**
     * @brief Pose broadcast with less than this period will be discarded when calculating the velocity
     *
     * @return Pose broadcast with less than this period will be discarded when calculating the velocity
     */
    qreal getBcastPeriodMin() const { return poseVelControlPeriod - 50; }

    /**
     * @brief Pose broadcast with more than this period will be discarded when calculating the velocity
     *
     * @return Pose broadcast with more than this period will be discarded when calculating the velocity
     */
    qreal getBcastPeriodMax() const { return poseVelControlPeriod + 100; }

    /**
     * @brief Estimates the robot velocities
     */
    void estimateVelocities();

    /**
     * @brief Calculates goal velocities to simultaneously reach pose and velocity goals, sends them as command
     */
    void poseVelControlCommandVelocities();

};

#endif // CELLULOROBOT_H
