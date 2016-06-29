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
 * @file CelluloZoneLine.h
 * @brief Header for the line zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONELINE_H
#define CELLULOZONELINE_H

#include "CelluloZone.h"

/**
 * @brief CelluloZone Base Class for line zones
 */
class CelluloZoneLine : public CelluloZone {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(float x1 WRITE setX1 READ getX1 NOTIFY x1Changed)
    Q_PROPERTY(float y1 WRITE setY1 READ getY1 NOTIFY y1Changed)
    Q_PROPERTY(float x2 WRITE setX2 READ getX2 NOTIFY x2Changed)
    Q_PROPERTY(float y2 WRITE setY2 READ getY2 NOTIFY y2Changed)

public:
    /**
     * @brief Creates a new Cellulo line zone
     */
    CelluloZoneLine();

    /**
     * @brief Gets the x position of the first line's point
     * @return X position of the first line's point
     */
    float getX1() {
        return x1;
    }

    /**
     * @brief Updates the x position of the line segment first endpoint
     * @param newx1 New x position in mm
     */
    void setX1(float newX1);

    /**
     * @brief Gets the y position of the first line's point
     * @return Y position of the first line's point
     */
    float getY1() {
        return y1;
    }

    /**
     * @brief Updates the y position of the line segment first endpoint
     * @param newx1 New y position in mm
     */
    void setY1(float newY1);

    /**
     * @brief Gets the x position of the second line's point
     * @return X position of the second line's point
     */
    float getX2() {
        return x2;
    }

    /**
     * @brief Updates the x position of the line segment second endpoint
     * @param newX2 New x position in mm
     */
    void setX2(float newX2);

    /**
     * @brief Gets the y position of the second line's point
     * @return Y position of the second line's point
     */
    float getY2() {
        return y2;
    }

    /**
     * @brief Updates the y position of the line segment second endpoint
     * @param newY1 New y position in mm
     */
    void setY2(float newY2);

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

protected:

    float x1;                               ///< X position of the first line's point
    float y1;                               ///< Y position of the first line's point
    float x2;                               ///< X position of the second line's point
    float y2;                               ///< Y position of the second line's point

signals:

    /**
     * @brief Emitted when the X position of the first line's point changes
     */
    void x1Changed();

    /**
     * @brief Emitted when the Y position of the first line's point changes
     */
    void y1Changed();

    /**
     * @brief Emitted when the X position of the second line's point changes
     */
    void x2Changed();

    /**
     * @brief Emitted when the Y position of the second line's point changes
     */
    void y2Changed();

};

/**
 * @brief CelluloZone Specific Class for line zones distance determination
 */
class CelluloZoneLineDistance : public CelluloZoneLine {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneLineDistance();

    /**
     * @brief Calculate the distance between the robot position and this line zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return the distance between the robot position and this line zone
     */
    Q_INVOKABLE float calculate(float xRobot, float yRobot, float thetaRobot) override;

};

#endif // CELLULOZONELINE_H
