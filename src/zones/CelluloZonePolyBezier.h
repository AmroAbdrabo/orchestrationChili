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
#include "../comm/CelluloBluetooth.h"

class CelluloBluetooth;

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
    Q_PROPERTY(QVariantList controlPoints WRITE setControlPoints READ getControlPoints NOTIFY controlPointsChanged)

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
    QVariantList getControlPoints();

    /**
     * @brief Sets the curve's control points
     *
     * @param newVertices List of curve's control points, must contain 3n+1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve
     */
    void setControlPoints(const QVariantList& newControlPoints);

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

    /**
     * @brief Write the zone infos to the given json Object
     * @param QJsonObject json object to be written
     */
    virtual void write(QJsonObject& json) override;

    /**
     * @brief Read the zone infos from the given json Object
     * @param json json object to be read
     */
    virtual void read(const QJsonObject& json) override;

public slots:

    /**
     * @brief Sends this path to the given robot in order to be followed
     *
     * @param robot The robot to send the path to
     */
    void sendPathToRobot(CelluloBluetooth* robot) const;

signals:

    /**
     * @brief Emitted when the control points change
     */
    void controlPointsChanged();

protected:

    /**
     * @brief Gets the distance to the closest point on the curves to the given point
     *
     * @param m Given point
     * @return Closest distance
     */
    qreal getClosestDistance(const QVector2D& m);

    /**
     * @brief Gets the distance to the closest point on the curves to the given point
     *
     * @param m Given point
     * @param closestPoint [out] Returns the closest point
     * @return Closest distance
     */
    qreal getClosestDistance(const QVector2D& m, QVector2D& closestPoint);

    /**
     * @brief Updates the bounding rectangle from the new list of vertices
     */
    void calculateBoundingBox();

    /**
     * @brief Calculates whether the given point is in the bounding box of this curve
     *
     * @param m The point to check
     * @return Whether this point is in the bounding box
     */
    bool inBoundingBox(const QVector2D& m);

    QList<CubicBezier> segments;                    ///< Consecutive Bézier curve segments
    qreal minX = std::numeric_limits<qreal>::max(); ///< Minimal x bound for the curve
    qreal maxX = std::numeric_limits<qreal>::min(); ///< Maximum x bound for the curve
    qreal minY = std::numeric_limits<qreal>::max(); ///< Minimum y bound for the curve
    qreal maxY = std::numeric_limits<qreal>::min(); ///< Maximum y bound for the curve

private:

    /**
     * @brief Forces heavy calculations to be redone at a later time
     */
    void invalidateCalc();

    bool boundingBoxCalculated = false; ///< Whether the bounding box is calculated and ready

};

/**
 * @brief Calculates the distance to a composite Bézier curve
 */
class CelluloZonePolyBezierDistance : public CelluloZonePolyBezier {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZonePolyBezierDistance();

    /**
     * @brief Gets the closest point on the curves to the given point
     *
     * @param m Given point
     * @return Closest point
     */
    Q_INVOKABLE QVector2D getClosestPoint(const QVector2D& m);

    /**
     * @brief Calculate the closest distance of the composite curve to the robot
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return Closest distance to any curve among the segments
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) override;

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

};

/**
 * @brief Calculates whether the client is on the border of a composite Bézier curve
 */
class CelluloZonePolyBezierBorder : public CelluloZonePolyBezier {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(qreal borderThickness WRITE setBorderThickness READ getBorderThickness NOTIFY borderThicknessChanged)

public:

    CelluloZonePolyBezierBorder();

    /**
     * @brief Gets the border thickness
     *
     * @return Border thickness in mm
     */
    qreal getBorderThickness(){ return borderThickness; }

    /**
     * @brief Sets the new border thickness
     *
     * @param newThickness New thickness in mm
     */
    void setBorderThickness(qreal newThickness);

    /**
     * @brief Write the zone infos to the given json Object
     * @param QJsonObject json object to be written
     */
    virtual void write(QJsonObject &json) override;

    /**
     * @brief Read the zone infos from the given json Object
     * @param json json object to be read
     */
    virtual void read(const QJsonObject &json) override;

    /**
     * @brief Calculate whether the robot is within the border
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return Whether the robot is within the border
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) override;

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
     * @brief Emitted when border thickness changes
     */
    void borderThicknessChanged();

private:

    qreal borderThickness;      ///< The border thickness in mm

};


/**
 * @brief Calculates whether the client is within the composite Bézier curve
 *
 * The first and last points of the curve are assumed to be connected with a line segment in order to ensure the curve is closed.
 */
class CelluloZonePolyBezierInner : public CelluloZonePolyBezier {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZonePolyBezierInner();

    /**
     * @brief Calculate whether the robot lies inside this composite Bézier curve
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is inside this zone 0 otherwise
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) override;

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

};

#endif // CELLULOZONEPOLYBEZIER_H
