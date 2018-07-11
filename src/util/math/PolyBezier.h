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
 * @file PolyBezier.h
 * @brief A composite cubic Bézier curve
 * @author Ayberk Özgür
 * @date 2018-07-10
 */

#ifndef POLYBEZIER_H
#define POLYBEZIER_H

#include "CubicBezier.h"

#include <QList>
#include <QVector2D>

namespace Cellulo{

/** @cond DO_NOT_DOCUMENT */

/**
 * @brief A composite cubic Bézier curve, i.e sequential list cubic Bézier curves whose endpoints coincide
 *
 * The curve is composed of continuous cubic Bézier curve segments, as seen in https://en.wikipedia.org/wiki/Composite_B%C3%A9zier_curve
 * The curve is compliant with the SVG standard of continuous cubic Bézier segments.
 *
 * It is composed of 3n+1 control points where the points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve.
 */
class PolyBezier {

public:

    /**
     * @brief Creates a new composite cubic Bézier curve
     */
    PolyBezier();

    /**
     * @brief Gets the curve's control points
     *
     * @return List of curve's control points, contains 3*numSegments + 1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve
     */
    QList<QVector2D> getControlPoints() const;

    /**
     * @brief Sets the curve's control points
     *
     * @param newControlPoints List of curve's control points, must contain 3*numSegments + 1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve
     */
    void setControlPoints(QList<QVector2D> const& newControlPoints);

    /**
     * @brief Gets the number of cubic Bézier curves making up this composite curve
     *
     * @return Number of cubic Bézier curves making up this composite curve
     */
    int getNumSegments();

    /**
     * @brief Gets the point on the curve corresponding to the given parameter
     *
     * @param t Given parameter t in [0,numSegments]
     * @return Point on curve corresponding to t
     */
    QVector2D getPoint(qreal t);

    /**
     * @brief Gets the tangent direction of point on the curve corresponding to the given parameter
     *
     * @param t Given parameter t in [0,numSegments]
     * @return Tangent direction of the point on curve corresponding to t
     */
    QVector2D getTangent(qreal t);

    /**
     * @brief Gets the normal direction of point on the curve corresponding to the given parameter
     *
     * @param t Given parameter t in [0,numSegments]
     * @return Normal direction of the point on curve corresponding to t
     */
    QVector2D getNormal(qreal t);

    /**
     * @brief Gets the segment index from the given parameter t, pulls t to [0,1]
     *
     * @param t [in/out] Parameter t in [0,numSegments], changes to segment parameter that is in [0,1]
     * @return Segment index
     */
    int getSegmentIndex(qreal& t);

    /**
     * @brief Gets the closest point on the curve to the given point
     *
     * @param m Given point
     * @param closestPoint [out] Returns the closest point
     * @param closestDist [out] Returns the closest distance
     * @return Returns the parameter t corresponding to the closest point
     */
    qreal getClosest(const QVector2D& m, QVector2D& closestPoint, qreal& closestDist);

    /**
     * @brief Calculates whether the given point is in the area defined by the curve
     *
     * If the curve is not closed, a straight line going from its start point to its endpoint is assumed to close it.
     *
     * @param point The point to check
     * @return Whether this point is in the curve area
     */
    bool isInside(QVector2D const& point);

    /**
     * @brief Calculates whether the given point is in the bounding box of this curve
     *
     * @param point The point to check
     * @return Whether this point is in the bounding box
     */
    bool isInBoundingBox(QVector2D const& point);

private:

    /**
     * @brief Updates the bounding rectangle from the new list of vertices
     */
    void calculateBoundingBox();

    /**
     * @brief Forces heavy calculations to be redone at a later time
     */
    void invalidateCalc();

    QList<CubicBezier> segments;                    ///< Consecutive Bézier curve segments
    bool boundingBoxCalculated = false;             ///< Whether the bounding box is calculated and ready
    qreal minX = std::numeric_limits<qreal>::max(); ///< Minimal x bound for the curve
    qreal maxX = std::numeric_limits<qreal>::min(); ///< Maximum x bound for the curve
    qreal minY = std::numeric_limits<qreal>::max(); ///< Minimum y bound for the curve
    qreal maxY = std::numeric_limits<qreal>::min(); ///< Maximum y bound for the curve

};

/** @endcond */

}

#endif // POLYBEZIER_H
