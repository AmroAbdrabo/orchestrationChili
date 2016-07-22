/*
 * Copyright (C) 2016 EPFL
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
 * @file CubicBezier.h
 * @brief Header for a cubic Bézier curve
 * @author Ayberk Özgür
 * @date 2016-07-21
 */

#include <QVector2D>

/**
 * @brief Describes a cubic Bézier curve B(t) = (1 - t)^3*p0 + 3*(1 - t)^2*t*p1 + 3*(1 - t)*t^2*p2 + t^3*p3
 */
class CubicBezier {

public:

    /**
     * @brief Creates a new cubic Bézier curve with provided control points
     *
     * @param p0 First control point
     * @param p1 Second control point
     * @param p2 Third control point
     * @param p3 Fourth control point
     */
    CubicBezier(const QVector2D &p0, const QVector2D &p1, const QVector2D &p2, const QVector2D &p3);

    /**
     * @brief Creates a new cubic Bézier curve with undefined control points
     */
    CubicBezier();

    /**
     * @brief Sets all control points, calculates the approximate equidistant t lookup table
     *
     * @param p0 First control point
     * @param p1 Second control point
     * @param p2 Third control point
     * @param p3 Fourth control point
     */
    void setControlPoints(const QVector2D& p0, const QVector2D& p1, const QVector2D& p2, const QVector2D& p3);

    /**
     * @brief Gets a control point
     *
     * @param i Index: 0, 1, 2 or 3
     */
    QVector2D getControlPoint(unsigned char i);

    /**
     * @brief Gets the closest point on the curve to the given point
     *
     * @param m Given point
     * @param closestPoint Returns the closest point
     * @param closestDist Returns the closest distance
     */
    void getClosestPoint(const QVector2D& m, QVector2D& closestPoint, qreal& closestDist);

    /**
     * @brief Calculates the point on the curve corresponding to the given parameter
     *
     * @param t Curve parameter in [0,1]
     * @return Point corresponding to t
     */
    QVector2D getPoint(qreal t);

private:

    /**
     * @brief Calculates the equidistant t lookup table
     */
    void buildEquidistantTLUT();

    QVector2D p[4];                                                           ///< Control points
    static const int T_LUT_SIZE = 20;                                         ///< Approximate equidistant lookup table size
    static constexpr qreal T_INTERVAL_SIZE = (1/((qreal)(T_LUT_SIZE - 1)))/2; ///< Initial t interval size for closest point search
    static constexpr qreal T_INTERVAL_EPSILON = 0.01;                         ///< Closest point search interval limit, in mm
    qreal curveLength;                                                        ///< Approximate length of the curve
    qreal equidistantTLut[T_LUT_SIZE];                                        ///< List of t that are approximately equidistant to eachother on the curve
    QVector2D equidistantPointLut[T_LUT_SIZE];                                ///< List of points that correspond to equidistantTLut






    float minX;                 ///< Minimal x bound for the polygon
    float maxX;                 ///< Maximum x bound for the polygon
    float minY;                 ///< Minimum y bound for the polygon
    float maxY;                 ///< Maximum y bound for the polygon

};
