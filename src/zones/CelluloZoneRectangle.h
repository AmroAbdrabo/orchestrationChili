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
     * @brief Gets the x position of upper left corner of the rectangle
     * @return X position of upper left corner of the rectangle
     */
    float getX() {
        return x;
    }

    /**
     * @brief Updates the rectangle's left edge x position
     * @param newX New x position in mm
     */
    void setX(float newX);

    /**
     * @brief Gets the y position of upper left corner of the rectangle
     * @return Y position of upper left corner of the rectangle
     */
    float getY() {
        return y;
    }

    /**
     * @brief Updates the rectangle's top edge y position
     * @param newY New y position in mm
     */
    void setY(float newY);

    /**
     * @brief Gets the height of the rectangle
     * @return Height of the rectangle
     */
    float getHeight() {
        return height;
    }

    /**
     * @brief Updates the rectangle's height
     * @param newHeight New height in mm
     */
    void setHeight(float newHeight);

    /**
     * @brief Gets the width of the rectangle
     * @return Width of the rectangle
     */
    float getWidth() {
        return width;
    }

    /**
     * @brief Updates the rectangle's width
     * @param newHeight New width in mm
     */
    void setWidth(float newWidth);

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
 * @brief CelluloZone Specific Class for rectangular zones border determination
 */
class CelluloZoneRectangleBorder : public CelluloZoneRectangle {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(qreal borderThickness WRITE setBorderThickness READ getBorderThickness NOTIFY borderThicknessChanged)

public:

    CelluloZoneRectangleBorder();

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
     * @brief Calculate whether the robot lies on the border of this rectangular zone (given the zone's margin)
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is on the border of this rectangular zone (given the zone's margin) 0 otherwise
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

    qreal borderThickness;

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

#endif // CELLULOZONERECTANGLE_H
