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
 * @file CelluloZoneAngle.h
 * @brief Header for single angle zones
 * @author Ayberk Özgür
 * @date 2018-07-18
 */

#ifndef CELLULOZONEANGLE_H
#define CELLULOZONEANGLE_H

#include "CelluloZone.h"

/**
 * @brief Describes a single angle
 */
class CelluloZoneAngle : public CelluloZone {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(float angle WRITE setAngle READ getAngle NOTIFY angleChanged)

public:

    /**
     * @brief Creates a new Cellulo angular zone
     */
    CelluloZoneAngle();

    /**
     * @brief Gets the angle
     * @return The angle
     */
    float getAngle(){ return angle; }

    /**
     * @brief Sets the angle
     * @param newAngle New angle
     */
    void setAngle(float newAngle);

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

    qreal angle;    ///< The angle

signals:

    /**
     * @brief Emitted when the angle changes
     */
    void angleChanged();

};

/**
 * @brief Describes an angular zone sensitive to the client angle crossing the zone angle
 *
 * This zone is stateful and produces undefined behavior when used with more than one client
 */
class CelluloZoneAngleThreshold : public CelluloZoneAngle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneAngleThreshold();

    /**
     * @brief Calculate on which side the client currently is with respect to the zone
     *
     * @param xRobot UNUSED
     * @param yRobot UNUSED
     * @param thetaRobot Orientation of the client
     *
     * @return 1 or -1, value changes when the client crosses the threshold angle; value does not necessarily indicate the specific side
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

private:

    qreal prevDiff;     ///< Previous calculated difference
    qreal currentValue; ///< Current calculated value, changes every time the client crosses the angle

};

#endif // CELLULOZONEANGLE_H
