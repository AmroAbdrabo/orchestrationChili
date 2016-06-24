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
 * @file CelluloZoneRectangle.h
 * @brief Header for the rectangular zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONERECTANGLE_H
#define CELLULOZONERECTANGLE_H

#include "CelluloZone.h"

/**
 * @brief CelluloZone Base Class for rectangular zones
 */
class CelluloZoneRectangle : public CelluloZone {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(float x WRITE setX READ getX NOTIFY xChanged)
    Q_PROPERTY(float y WRITE setY READ getY NOTIFY yChanged)
    Q_PROPERTY(float height WRITE setHeight READ getHeight NOTIFY heightChanged)
    Q_PROPERTY(float width WRITE setWidth READ getWidth NOTIFY widthChanged)

public:

    /**
     * @brief Creates a new Cellulo rectangular zone
     */
    CelluloZoneRectangle();

    /**
     * @brief get the properties of this zone in rationalized form
     * @param realPlaygroundWidth real playground width
     * @param realPlaygroundHeight real playground height
     * @return map of rationalized properties
     */
    QVariantMap getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight);

    /**
     * @brief Gets the x position of upper left corner of the rectangle
     * @return X position of upper left corner of the rectangle
     */
    float getX() {
        return x;
    }
    void setX(float newX) {
        if(newX!=x){
            x = newX;
            emit(xChanged());
        }
    }

    /**
     * @brief Gets the y position of upper left corner of the rectangle
     * @return Y position of upper left corner of the rectangle
     */
    float getY() {
        return y;
    }
    void setY(float newY) {
        if(newY!=y){
            y = newY;
            emit(yChanged());
        }
    }

    /**
     * @brief Gets the height of the rectangle
     * @return Height of the rectangle
     */
    float getHeight() {
        return height;
    }
    void setHeight(float newHeight) {
        if(newHeight!=height){
            height = newHeight;
            emit(heightChanged());
        }
    }

    /**
     * @brief Gets the width of the rectangle
     * @return Width of the rectangle
     */
    float getWidth() {
        return width;
    }
    void setWidth(float newWidth) {
        if(newWidth!=width){
            width = newWidth;
            emit(widthChanged());
        }
    }

    /**
     * @brief Calculate the zone quantity of this rectangular zone according to the robot's pose
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return Zone quantity for this zone and this robot's pose
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) = 0;

    /**
     * @brief Write the zone infos to the given json Object
     * @param QJsonObject json object to be written
     */
    void write(QJsonObject &json);


    /**
     * @brief Read the zone infos from the given json Object
     * @param json json object to be read
     */
    void read(const QJsonObject &json);

protected:

    float x;                                ///< x position of the upper left corner of the rectangle
    float y;                                ///< y position of the upper left corner of the rectangle
    float height;                           ///< height of the rectangle
    float width;                            ///< width of the rectangle

signals:

    /**
     * @brief Emitted when the x position of the upper left corner of the rectangular zone's center changes
     */
    void xChanged();

    /**
     * @brief Emitted when the y postion of the upper left corner of the rectangular zone's center changes
     */
    void yChanged();

    /**
     * @brief Emitted when the height of the rectangular zone changes
     */
    void heightChanged();

    /**
     * @brief Emitted when the height of the rectangular zone changes
     */
    void widthChanged();

};

/**
 * @brief CelluloZone Specific Class for rectangular zones inner determination
 */
class CelluloZoneRectangleInner : public CelluloZoneRectangle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneRectangleInner();

    /**
     * @brief Calculate whether the robot lies inside this rectangular zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is inside this rectangular zone 0 otherwise
     */
    Q_INVOKABLE float calculate(float xRobot, float yRobot, float thetaRobot);

};

/**
 * @brief CelluloZone Specific Class for rectangular zones border determination
 */
class CelluloZoneRectangleBorder : public CelluloZoneRectangle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneRectangleBorder();

    /**
     * @brief Calculate whether the robot lies on the border of this rectangular zone (given the zone's margin)
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is on the border of this rectangular zone (given the zone's margin) 0 otherwise
     */
    Q_INVOKABLE float calculate(float xRobot, float yRobot, float thetaRobot);

};

/**
 * @brief CelluloZone Specific Class for rectangular zones distance determination
 */
class CelluloZoneRectangleDistance : public CelluloZoneRectangle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneRectangleDistance();

    /**
     * @brief Calculate the distance between the robot pose and the border of this rectangular zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return the distance between the robot pose and the border of this rectangular zone
     */
    Q_INVOKABLE float calculate(float xRobot, float yRobot, float thetaRobot);

};

#endif // CELLULOZONERECTANGLE_H
