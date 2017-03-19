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

    Q_PROPERTY(bool poseVelControlEnabled READ getPoseVelControlEnabled WRITE setPoseVelControlEnabled NOTIFY poseVelControlEnabledChanged)
    Q_PROPERTY(int poseVelControlPeriod READ getPoseVelControlPeriod WRITE setPoseVelControlPeriod NOTIFY poseVelControlPeriodChanged)
    Q_PROPERTY(QVector3D vxyw READ getVxyw NOTIFY vxywChanged)
    Q_PROPERTY(qreal vx READ getVx NOTIFY vxywChanged)
    Q_PROPERTY(qreal vy READ getVy NOTIFY vxywChanged)
    Q_PROPERTY(qreal w READ getW NOTIFY vxywChanged)






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

signals:

    /**
     * @brief Emitted when the simultaneous pose and velocity controller is enabled/disabled
     */
    void poseVelControlEnabledChanged();

    /**
     * @brief Emitted when the simultaneous pose and velocity controller period changes
     */
    void poseVelControlPeriodChanged();

    /**
     * @brief Emitted when the linear/angular velocity changes
     */
    void vxywChanged();

private slots:



public slots:



private:

    bool poseVelControlEnabled; ///< Whether the simultaneous pose and velocity controller is enabled, must be enabled by the user
    int poseVelControlPeriod;   ///< Desired pose/velocity control period in ms, set to 0 for highest possible frequency
    QVector3D vxyw;             ///< Robot velocities: x,y in mm/s, z in rad/s (representing w)

    /**
     * @brief Initializes the robot to the settings necessary to run the controllers, initializes controllers
     */
    void initialize();

    /**
     * @brief Estimates the robot velocities
     */
    void estimateVelocities();

    /**
     * @brief Calculates goal velocities to simultaneously reach pose and velocity goals, sends them as command
     */
    void commandVelocities();

};

#endif // CELLULOROBOT_H
