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
 * @file CelluloZonePoint.h
 * @brief Header for the point zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONEPOINT_H
#define CELLULOZONEPOINT_H

#include "CelluloZone.h"

/**
 * @brief CelluloZone Base Class for point zones
 */
class CelluloZonePoint : public CelluloZone {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(float x WRITE setX READ getX NOTIFY xChanged)
    Q_PROPERTY(float y WRITE setY READ getY NOTIFY yChanged)

public:

    /**
     * @brief Creates a new Cellulo point zone
     */
    CelluloZonePoint();

    /**
     * @brief Gets the x position of the point
     * @return X position of the point
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
     * @brief Gets the y position of the point
     * @return Y position of the point
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
     * @brief get the properties of this zone in rationalized form
     * @param realPlaygroundWidth real playground width
     * @param realPlaygroundHeight real playground height
     * @return map of rationalized properties
     */
    QVariantMap getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight);

    /**
     * @brief Calculate the zone quantity of this line zone according to the robot's pose
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
     * @param json json object to be written
     */
    void write(QJsonObject &json);

    /**
     * @brief Read the zone infos from the given json Object
     * @param json json object to be read
     */
    void read(const QJsonObject &json);

protected:

    float x;                               ///< X position of the point
    float y;                               ///< Y position of the point

signals:

    /**
     * @brief Emitted when the X position of the point changes
     */
    void xChanged();

    /**
     * @brief Emitted when the Y position of the point changes
     */
    void yChanged();

};

/**
 * @brief CelluloZone Specific Class for point zones distance determination
 */
class CelluloZonePointDistance : public CelluloZonePoint {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZonePointDistance();

    /**
     * @brief Calculate the distance between the robot pose and this point zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return the distance between the robot pose and this point zone
     */
    Q_INVOKABLE float calculate(float xRobot, float yRobot, float thetaRobot);

};

#endif // CELLULOZONEPOINT_H
