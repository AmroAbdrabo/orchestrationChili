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
 * @file CelluloMathUtil.h
 * @brief Header for mathematical and geometrical utilities
 * @author Joanna Salathé
 * @author Ayberk Özgür
 * @date 2016-06-30
 */

#ifndef CELLULOMATHUTIL_H
#define CELLULOMATHUTIL_H

#include <QObject>
#include <QVector2D>

class CelluloMathUtil : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloMathUtil(QObject* parent = 0);
    ~CelluloMathUtil();

    /**
     * @brief Calculates the distance of a point to a line segment in 2D
     *
     * @param p The point
     * @param seg1 The first endpoint of the line segment
     * @param seg2 The second endpoint of the line segment
     * @return Distance between the point and the line segment
     */
    Q_INVOKABLE static qreal pointToSegmentDist(const QVector2D& p, const QVector2D& seg1, const QVector2D& seg2);

    /**
     * @brief Calculates the signed distance of a point to a line in 2D
     *
     * @param p The point
     * @param lp1 First point the line passes through
     * @param lp2 Second point the line passes through
     * @return Distance between the point and line segment, negative if point is below the line
     */
    Q_INVOKABLE static qreal pointToLineDistSigned(const QVector2D& p, const QVector2D& lp1, const QVector2D& lp2);

    /**
     * @brief Calculates whether the given point is in the given polygon
     *
     * @param p The point
     * @param v The vertices of the polygon
     * @return Whether the point lies in the given polygon
     */
    Q_INVOKABLE static bool pointInPoly(const QVector2D& p, const QList<QVector2D>& v);

    /**
     * @brief Calculates the distance of the point to the polygon border
     *
     * @param p The point (may be in the polygon)
     * @param v The vertices of the polygon
     * @return The distance of the point to the polygon border
     */
    Q_INVOKABLE static qreal pointToPolyBorderDist(const QVector2D& p, const QList<QVector2D>& v);

    /**
     * @brief Calculates the roots of ax^2 + bx + c = 0
     *
     * @param a 2nd order coefficient
     * @param b 1st order coefficient
     * @param c Constant
     * @param x1 [out] First root if real roots exist
     * @param x2 [out] Second root if real roots exist
     * @return Number of unique real roots, i.e 0, 1 or 2
     */
    static int solveQuadEq(qreal a, qreal b, qreal c, qreal& x1, qreal& x2);

    /**
     * @brief Calculates the roots of ax^3 + bx^2 + cx + d = 0
     *
     * @param a 3rd order coefficient, must be nonzero
     * @param b 2nd order coefficient
     * @param c 1st order coefficient
     * @param d Constant
     * @param x1 [out] First unique root if real roots exist
     * @param x2 [out] Second unique root if real roots exist (will be equal to x3 if there are two roots, equal to x1 if there is only one root)
     * @param x3 [out] Third unique root if real roots exist (will be equal to x2 if there are two roots, equal to x1 if there is only one root)
     * @return Number of unique real roots, i.e 1, 2 or 3
     */
    static int solveCubicEq(qreal a, qreal b, qreal c, qreal d, qreal& x1, qreal& x2, qreal& x3);

    /**
     * @brief Checks whether the value is within -epsilon,+epsilon
     *
     * @param val The value
     * @param epsilon The tolerance
     * @return Whether the number is within -epsilon,+epsilon
     */
    static bool isZero(qreal val, qreal epsilon);

private:

    static constexpr qreal SOLVE_CUBIC_EPSILON = 1e-9; ///< Epsilon to use during isZero by the cubic equation solver

};

#endif // CELLULOMATHUTIL_H
