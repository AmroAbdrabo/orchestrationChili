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
 * @file CelluloZoneCircle.h
 * @brief Header for circle zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONECIRCLE_H
#define CELLULOZONECIRCLE_H

#include "CelluloZone.h"

/**
 * @brief CelluloZone Base Class for circular zones
 */
class CelluloZoneCircle : public CelluloZone {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(float x WRITE setX READ getX NOTIFY xChanged)
    Q_PROPERTY(float y WRITE setY READ getY NOTIFY yChanged)
    Q_PROPERTY(float r WRITE setR READ getR NOTIFY rChanged)

public:

    /**
     * @brief Creates a new Cellulo circular zone
     */
    CelluloZoneCircle();

    /**
     * @brief Gets the x position of circle's center
     * @return X position of circle's center
     */
    float getX(){
        return x;
    }

    /**
     * @brief Updates the x position of circle's center
     * @param newX New x position in mm
     */
    void setX(float newX);

    /**
     * @brief Gets the y position of circle's center
     * @return Y position of circle's center
     */
    float getY(){
        return y;
    }

    /**
     * @brief Updates the y position of circle's center
     * @param newY New y position in mm
     */
    void setY(float newY);

    /**
     * @brief Gets the radius of the circle
     * @return R the radius of the circle
     */
    float getR(){
        return r;
    }

    /**
     * @brief Updates the radius of circle
     * @param newR New radius in mm
     */
    void setR(float newR);

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

    /**
     * @brief Draws this zone onto the painter
     *
     * @param painter Object to draw onto
     * @param canvasWidth Screen width of the canvas in pixels
     * @param canvasHeight Screen height of the canvas in pixels
     * @param physicalWidth Physical width of the canvas in mm
     * @param physicalHeight Physical height of the canvas in mm
     */
    virtual void paint(QPainter* painter, QColor fillColor, QColor lineColor, qreal lineThickness, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight) override;

protected:

    float x;    ///< x position of circle's center
    float y;    ///< y position of circle's center
    float r;    ///< r the radius of the circle

signals:

    /**
     * @brief Emitted when the x position of circular zone's center changes
     */
    void xChanged();

    /**
     * @brief Emitted when the y position of circular zone's center changes
     */
    void yChanged();

    /**
     * @brief Emitted when r the radius of the circular zone changes
     */
    void rChanged();

};

/**
 * @brief CelluloZone Specific Class for circular zones inner determination
 */
class CelluloZoneCircleInner : public CelluloZoneCircle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneCircleInner();

    /**
     * @brief Calculate whether the robot lies inside this circular zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is inside this circular zone 0 otherwise
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) override;

};

/**
 * @brief CelluloZone Specific Class for circular zones border determination
 */
class CelluloZoneCircleBorder : public CelluloZoneCircle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneCircleBorder();

    /**
     * @brief Calculate whether the robot lies on the border of this circular zone (given the zone's margin)
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is on the border of this circular zone (given the zone's margin) 0 otherwise
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) override;

};

/**
 * @brief CelluloZone Specific Class for circular zones distance determination
 */
class CelluloZoneCircleDistance : public CelluloZoneCircle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneCircleDistance();

    /**
     * @brief Calculate the distance between the robot pose and the border of this circular zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return the distance between the robot pose and the border of this circular zone
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) override;

};

#endif // CELLULOZONECIRCLE_H
