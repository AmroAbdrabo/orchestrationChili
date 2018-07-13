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

#include <QQuickItem>
#include <QVariantList>
#include <QList>
#include <QVector>
#include <QVector2D>

namespace Cellulo{

/**
 * @addtogroup robot
 * @{
 */

/**
 * @brief Makes a CelluloRobot track a PolyBezier curve, parent must be a CelluloRobot
 */
class PolyBezierTracker : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /** @brief PolyBezier curve to track */
    Q_PROPERTY(Cellulo::PolyBezier* curve WRITE setCurve READ getCurve NOTIFY curveChanged)

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
     * @brief Gets the curve's control points
     *
     * @return List of curve's control points, contains 3*numSegments + 1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve
     */
    Cellulo::PolyBezier* getCurve() const { return curve; }

    /**
     * @brief Sets the curve's control points
     *
     * @param newControlPoints List of curve's control points, must contain 3*numSegments + 1 QVector2Ds where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve
     */
    void setCurve(Cellulo::PolyBezier* newCurve);

    /** @endcond */

signals:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Emitted when the control points change
     */
    void curveChanged();

    /** @endcond */

public slots:



private:



    PolyBezier* curve; ///< Curve to be tracked

};

/** @} */

}

#endif // POLYBEZIERTRACKER_H
