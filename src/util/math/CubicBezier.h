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
     * @brief Creates a new cubic Bézier curve with provided control points, calculates the lookup tables
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
     * @brief Sets all control points
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
     * @param closestPoint [out] Returns the closest point
     * @param closestDist [out] Returns the closest distance
     */
    void getClosestPoint(const QVector2D& m, QVector2D& closestPoint, qreal& closestDist);

    /**
     * @brief Calculates the point on the curve corresponding to the given parameter
     *
     * @param t Curve parameter in [0,1]
     * @return Point corresponding to t
     */
    QVector2D getPoint(qreal t);

    /**
     * @brief Splits the curve into two parts which make up this curve
     *
     * @param t Split point, must be in [0,1]
     * @param left [out] First part
     * @param right [out] Second part
     */
    void split(qreal t, CubicBezier& left, CubicBezier& right);

    /**
     * @brief Gets the coordinates of the bounding box
     *
     * @param minXOut [out] Left coordinate
     * @param maxXOut [out] Right coordinate
     * @param minYOut [out] Top coordinate
     * @param maxYOut [out] Bottom coordinate
     */
    void getBoundingBox(qreal& minXOut, qreal& maxXOut, qreal& minYOut, qreal& maxYOut);

private:

    /**
     * @brief Forces heavy calculations to be redone at a later time
     */
    void invalidateCalc();

    /**
     * @brief Calculates the equidistant t lookup table
     */
    void buildEquidistantTLUT();

    /**
     * @brief Calculates the x coordinate of the point on the curve corresponding to the given parameter
     *
     * @param t Curve parameter in [0,1]
     * @return Point x coordinate corresponding to t
     */
    qreal getPointX(qreal t);

    /**
     * @brief Calculates the y coordinate of the point on the curve corresponding to the given parameter
     *
     * @param t Curve parameter in [0,1]
     * @return Point y coordinate corresponding to t
     */
    qreal getPointY(qreal t);

    /**
     * @brief Sets the min/max X of the bounding box from the given value if value is less/greater than the min/max
     *
     * @param newX New value
     */
    void updateMinMaxX(qreal newX);

    /**
     * @brief Sets the min/max Y of the bounding box from the given value if value is less/greater than the min/max
     *
     * @param newY New value
     */
    void updateMinMaxY(qreal newY);

    /**
     * @brief Calculates the bounding box
     */
    void calculateBoundingBox();

    /**
     * @brief Calculates whether the bounding boxes of two cubic Bézier curves intersect
     *
     * @param curve1 First curve
     * @param curve2 Second curve
     * @return Whether the bounding box of the two curves intersect
     */
    static bool boundingBoxesIntersect(CubicBezier& curve1, CubicBezier& curve2);

    bool boundingBoxCalculated = false;                                       ///< Whether the bounding box is calculated for this curve
    bool equidistantTLutCalculated = false;                                   ///< Whether the equidistant t/point lookup table is calculated

    QVector2D p[4];                                                           ///< Control points
    static const int T_LUT_SIZE = 20;                                         ///< Approximate equidistant lookup table size
    static constexpr qreal T_INTERVAL_SIZE = (1/((qreal)(T_LUT_SIZE - 1)))/2; ///< Initial t interval size for closest point search
    static constexpr qreal T_INTERVAL_EPSILON = 0.01;                         ///< Closest point search interval limit, in mm
    qreal curveLength;                                                        ///< Approximate length of the curve
    qreal equidistantTLut[T_LUT_SIZE];                                        ///< List of t that are approximately equidistant to eachother on the curve
    QVector2D equidistantPointLut[T_LUT_SIZE];                                ///< List of points that correspond to equidistantTLut
    qreal minX = std::numeric_limits<qreal>::max();                           ///< Minimal x bound for the curve
    qreal maxX = std::numeric_limits<qreal>::min();                           ///< Maximum x bound for the curve
    qreal minY = std::numeric_limits<qreal>::max();                           ///< Minimum y bound for the curve
    qreal maxY = std::numeric_limits<qreal>::min();                           ///< Maximum y bound for the curve

};
