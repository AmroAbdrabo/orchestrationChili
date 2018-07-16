/*
 * Copyright (C) 2018 EPFL
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
 * @file PolyBezierTracker.h
 * @brief Makes CelluloRobots track PolyBezier curves
 * @author Ayberk Özgür
 * @date 2018-07-13
 */

#ifndef POLYBEZIERTRACKER_H
#define POLYBEZIERTRACKER_H

#include "../util/math/PolyBezier.h"
#include "CelluloRobot.h"

#include <QQuickItem>
#include <QVariantList>
#include <QList>
#include <QVector>
#include <QVector2D>

namespace Cellulo {

/**
 * @addtogroup robot
 * @{
 */

/**
 * @brief Makes a CelluloRobot track a PolyBezier curve
 */
class PolyBezierTracker : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /** @brief PolyBezier curve to track */
    Q_PROPERTY(Cellulo::PolyBezier* curve WRITE setCurve READ getCurve NOTIFY curveChanged)

    /** @brief Robot that will track the curve */
    Q_PROPERTY(Cellulo::CelluloRobot* robot WRITE setRobot READ getRobot NOTIFY robotChanged)

    /** @brief Whether to go the the start of the curve first (by default) or to start tracking from the closest point */
    Q_PROPERTY(bool goToStartFirst MEMBER goToStartFirst)

    /** @brief Whether to stop (i.e disable tracker) once the curve is completely tracked (i.e final point on the curve is reached), default false */
    Q_PROPERTY(bool stopWhenGoalReached MEMBER stopWhenGoalReached)

    /** @brief The currently tracked pose, in (mm,mm,deg), read-only */
    Q_PROPERTY(QVector3D trackedPose READ getTrackedPose NOTIFY trackedPoseChanged)

    /** @brief The currently tracked velocity, in (mm/s,mm/s,rad/s), read-only */
    Q_PROPERTY(QVector3D trackedVelocity READ getTrackedVelocity NOTIFY trackedVelocityChanged)

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new PolyBezier tracker
     *
     * @param parent The QML parent
     */
    PolyBezierTracker(QQuickItem* parent = nullptr);

    /**
     * @brief Destroys the tracker
     */
    ~PolyBezierTracker();

    /**
     * @brief Gets the curve to track
     *
     * @return The current curve to track
     */
    Cellulo::PolyBezier* getCurve() const { return curve; }

    /**
     * @brief Sets the curve to track
     *
     * @param newCurve The new curve to track
     */
    void setCurve(Cellulo::PolyBezier* newCurve);

    /**
     * @brief Gets the robot that will track
     *
     * @return The current robot that will track
     */
    Cellulo::CelluloRobot* getRobot() const { return robot; }

    /**
     * @brief Sets the robot that will track
     *
     * @param newCurve The new robot that will track
     */
    void setRobot(Cellulo::CelluloRobot* newRobot);

    /**
     * @brief Gets the currently tracked pose
     *
     * @return The currently tracked pose in (mm,mm,deg)
     */
    QVector3D getTrackedPose() const { return currentP; }

    /**
     * @brief Gets the currently tracked velocities
     *
     * @return The currently tracked velocities in (mm/s,mm/s,rad/s)
     */
    QVector3D getTrackedVelocity() const { return currentV; }

    /** @endcond */

signals:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Emitted when the curve changes
     */
    void curveChanged();

    /**
     * @brief Emitted when the robot that tracks changes
     */
    void robotChanged();

    /**
     * @brief Emitted when the tracked pose changes
     */
    void trackedPoseChanged();

    /**
     * @brief Emitted when the tracked velocity changes
     */
    void trackedVelocityChanged();

    /** @endcond */

    /**
     * @brief Emitted when the robot reaches the start of the curve, if goToStart was marked true when tracking command was given
     */
    void startReached();

    /**
     * @brief Emitted when the robot reaches the end of the curve
     */
    void endReached();

public slots:

    /**
     * @brief Tracks the curve with constant velocity
     *
     * @param vel Linear velocity magnitude
     */
    void trackConstLinearVel(qreal vel);

private slots:

    /**
     * @brief Refreshes the tracking when the curve control points change
     */
    void updateCurve();

    /**
     * @brief Sends control velocities to the robot depending on the current state of tracking
     *
     * @param deltaTime The milliseconds elapsed since last iteration of the loop
     */
    void robotControlLoop(qreal deltaTime);

private:

    /**
     * @brief Override; adds child as curve if PolyBezier, adds parent as robot if CelluloRobot
     *
     * @param change The change that occurred
     * @param value Points to the relevant item/data
     */
    void itemChange(ItemChange change, ItemChangeData const& value) override;

    bool goToStartFirst = true;                ///< Whether to go to the start of the curve first
    bool stopWhenGoalReached = false;          ///< Whether to stop when curve is completely tracked

    bool endReachedFlag = false;               ///< Internal flag to mark whether the end of the curve is reached

    bool goingToStart = false;                 ///< Whether going to the start of the curve
    constexpr static qreal GOAL_EPSILON = 5.0; ///< This close to goal is considered reached

    qreal trackingVel;                         ///< Linear tracking velocity

    qreal currentT = 0.0;                      ///< Last parameter t of the curve that is being tracked
    qreal currentR = 0.0;                      ///< Last arc length ratio r of the curve that is being tracked
    QVector3D currentP;                        ///< Last point on the curve that is being tracked
    QVector3D currentV;                        ///< Last velocity that is being tracked

    PolyBezier* curve;                         ///< Curve to be tracked
    CelluloRobot* robot;                       ///< Robot to track the curve

};

/** @} */

}

#endif // POLYBEZIERTRACKER_H
