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
     * @brief Approximately calculates the shortest distance of the given point to this curve
     *
     * @param m Given point
     * @return Approximate shortest distance of given point to curve
     */
    qreal getDistance(const QVector2D& m);

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

    QVector2D p[4];                     ///< Control points
    static const int T_LUT_SIZE = 20;   ///< Approximate equidistant lookup table size
    qreal equidistantTLUT[T_LUT_SIZE];  ///< List of t that are approximately equidistant to eachother on the curve







    float minX;                 ///< Minimal x bound for the polygon
    float maxX;                 ///< Maximum x bound for the polygon
    float minY;                 ///< Minimum y bound for the polygon
    float maxY;                 ///< Maximum y bound for the polygon

};
