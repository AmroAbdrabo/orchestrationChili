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
 * @file CelluloZonePolyBezier.h
 * @brief Header for composite cubic Bézier curves
 * @author Ayberk Özgür
 * @date 2016-07-21
 */

#ifndef CELLULOZONEPOLYBEZIER_H
#define CELLULOZONEPOLYBEZIER_H

#include "CelluloZone.h"
#include "../util/math/CubicBezier.h"

/**
 * @brief CelluloZone Base class for composite cubic Bézier curve
 *
 * The curve is composed of continuous cubic Bézier curve segments, as seen in https://en.wikipedia.org/wiki/Composite_B%C3%A9zier_curve
 * The curve is compliant with the SVG standard of continuous cubic Bézier segments.
 *
 * It is composed of 3n+1 control points where the points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve.
 */
class CelluloZonePolyBezier : public CelluloZone {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(QList<QVector2D> controlPoints WRITE setControlPoints READ getControlPoints NOTIFY controlPointsChanged)

public:

    /**
     * @brief Creates a new Cellulo composite Bézier curve
     */
    CelluloZonePolyBezier();

    /**
     * @brief Gets the curve's control points
     *
     * @return List of curve's control points, contains 3n+1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve
     */
    QList<QVector2D> getControlPoints();

    /**
     * @brief Sets the curve's control points
     *
     * @param newVertices List of curve's control points, must contain 3n+1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve
     */
    void setControlPoints(const QList<QVector2D>& newControlPoints);

    /**
     * @brief Draws this zone onto the painter
     *
     * @param painter Object to draw onto
     * @param color Color of the paint
     * @param canvasWidth Screen width of the canvas in pixels
     * @param canvasHeight Screen height of the canvas in pixels
     * @param physicalWidth Physical width of the canvas in mm
     * @param physicalHeight Physical height of the canvas in mm
     */
    virtual void paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight) override;

signals:

    /**
     * @brief Emitted when the control points change
     */
    void controlPointsChanged();

protected:

    QList<CubicBezier> segments; ///< Consecutive Bézier curve segments








    /**
     * @brief Updates the bounding rectangle from the new list of vertices
     */
    void updateBounds();

    float minX;                ///< Minimal x bound for the polygon
    float maxX;                ///< Maximum x bound for the polygon
    float minY;                ///< Minimum y bound for the polygon
    float maxY;                ///< Maximum y bound for the polygon

};



#endif // CELLULOZONEPOLYBEZIER_H
