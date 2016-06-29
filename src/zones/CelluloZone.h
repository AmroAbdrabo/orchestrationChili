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
 * @file CelluloZone.h
 * @brief Header for base class zone architecture
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONE_H
#define CELLULOZONE_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>

#include "CelluloZoneTypes.h"
#include "CelluloZoneClient.h"
#include "CelluloZonePaintedItem.h"

class CelluloZonePaintedItem;

/**
 * @brief CelluloZone Base Class for zones
 */
class CelluloZone : public QQuickItem{
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(bool active WRITE setActive READ isActive NOTIFY activeChanged)
    Q_PROPERTY(QString name WRITE setName READ getName NOTIFY nameChanged)
    Q_PROPERTY(float marginThickeness WRITE setMarginThickeness READ getMarginTickeness NOTIFY marginThickenessChanged)
    Q_PROPERTY(int stackingOrder WRITE setStackingOrder READ getStackingOrder NOTIFY stackingOrderChanged)
    Q_PROPERTY(CelluloZoneTypes::ZoneType type READ getType NOTIFY typeChanged)

public:

    /**
     * @brief Creates a new Cellulo zone
     */
    explicit CelluloZone(QQuickItem* parent = 0);

    /**
     * @brief Get the type of the zone
     * @return Type of the zone
     */
    CelluloZoneTypes::ZoneType getType() { return type; }

    /**
     * @brief Get the name of the zone
     * @return Name of the zone
     */
    QString getName() { return name; }

    /**
     * @brief Set the name of the zone
     * @param newName new name for the zone
     */
    void setName(QString newName){
        if(newName!=name){
            name = newName;
            emit(nameChanged());
        }
    }

    /**
     * @brief Get the margin thickeness which is the margin accepted to tell if a robot is on border
     * @return Marginthickeness
     */
    float getMarginTickeness() { return marginThickeness; }

    /**
     * @brief Sets a margin thickeness
     * @param newMarginthickeness new margin thickeness to be set >0
     */
    void setMarginThickeness(float newMarginThickeness){
        if(newMarginThickeness!=marginThickeness && newMarginThickeness>0){
            marginThickeness = newMarginThickeness;
            emit(marginThickenessChanged());
        }
    }

    /**
     * @brief Get the stacking order
     * @return StackingOrder
     */
    float getStackingOrder() { return stackingOrder; }

    /**
     * @brief Sets the stacking order
     * @param newStackingOrder new stacking order to be set >=0
     */
    void setStackingOrder(float newStackingOrder){
        if(newStackingOrder!=stackingOrder && newStackingOrder>=0){
            stackingOrder = newStackingOrder;
            emit(stackingOrderChanged());
        }
    }

    /**
     * @brief Return if the zone is active or not
     * @return Active state
     */
    float isActive() { return active; }

    /**
     * @brief Sets active state
     * @param newActive new active state
     */
    void setActive(float newActive){
        if(newActive!=active){
            active = newActive;
            emit(activeChanged());
        }
    }

    /**
     * @brief Calculate the zone quantity of this zone according to the robot's pose
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
     *
     * @param QJsonObject Json object to be written
     */
    virtual void write(QJsonObject& json);

    /**
     * @brief Read the zone infos from the given json Object
     *
     * @param json Json object to be read
     */
    virtual void read(const QJsonObject& json);

    /**
     * @brief Draws this zone onto the painter
     *
     * @param painter Object to draw onto
     * @param canvasWidth Screen width of the canvas in pixels
     * @param canvasHeight Screen height of the canvas in pixels
     * @param physicalWidth Physical width of the canvas in mm
     * @param physicalHeight Physical height of the canvas in mm
     */
    virtual void paint(QPainter* painter, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight) = 0;

    /**
     * @brief Creates a PaintedItem that is the visual representation of this zone
     *
     * @param parent Visual QML parent that this item will fill
     * @param physicalPlaygroundWidth Playground width in mm
     * @param physicalPlaygroundHeight Playground height in mm
     *
     * @return A PaintedItem that is the visual representation of this zone
     */
    Q_INVOKABLE CelluloZonePaintedItem* createPaintedItem(QQuickItem* parent, qreal physicalPlaygroundWidth, qreal physicalPlaygroundHeight);

public slots:

    /**
     * @brief Slot associated to the CelluloZoneClient signal poseChanged
     *
     * Calculates zone quantity for the sender client (must inherit CelluloZoneClient) if zone is active
     *
     * @param x New x coordinate of the client
     * @param y New y coordinate of the client
     * @param theta New orientaton of the client
     */
    void onClientPoseChanged(qreal x, qreal y, qreal theta);

protected:

    QString name;                               ///< name of the zone
    CelluloZoneTypes::ZoneType type;            ///< type of the zone
    int stackingOrder;                          ///< stacking order of the zone
    float marginThickeness;                     ///< margin accepted to tell if a robot is on zone's border (middle of the margin is the border)
    bool active;                                ///< true if zone is active false otherwise
    QHash<QString, float> cellulosCalculate;    ///< map of cellulorobot (represented by their MacAdress) and their zone quantity for this zone

    /////////////////////////////////////////////////////////////////////// Mathematical functions for children

    /**
     * @brief pointToSegmentDistance Compute distance between point and segement
     * @param x X position of the point
     * @param y Y position of the point
     * @param x1 X position of the first line's point
     * @param y1 Y position of the first line's point
     * @param x2 X position of the second line's point
     * @param y2 Y position of the second line's point
     * @return distance between point and segment
     */
    float pointToSegmentDistance(float x,float y, float x1, float y1, float x2, float y2);

    /**
     * @brief pointInPoly Detect if a points is inside this polygonal zone
     * @param xRobot x position of the point to be checked
     * @param yRobot y position of the point to be checked
     * @param minX min x value for heavy computation to be launched
     * @param maxX max x value for heavy computation to be launched
     * @param minY min y value for heavy computation to be launched
     * @param maxY max y value for heavy computation to be launched
     * @param pointsQt qt points of the polygon
     * @return 1 if point is in poly, 0 otherwise
     */
    float pointInPoly(float xRobot, float yRobot,float minX,float maxX,float minY,float maxY, QList<QPointF> pointsQt);

    /**
     * @brief getRectangleFromLine Get rectangle around line with given margin
     * @param x1 X position of the first line's point
     * @param y1 Y position of the first line's point
     * @param x2 X position of the second line's point
     * @param y2 Y position of the second line's point
     * @param rectangleWidth width wanted for the surrounding rectangle
     * @return points of the rectangle surrounding the line
     */
    QList<QPointF> getRectangleFromLine(float x1,float y1,float x2, float y2, float rectangleWidth);

signals:

    /**
     * @brief Emitted when the margin thickeness of the zone changes
     */
    void marginThickenessChanged();

    /**
     * @brief Emitted when the stacking order of the zone changes
     */
    void stackingOrderChanged();

    /**
     * @brief Emitted when the active state of the zone changes
     */
    void activeChanged();

    /**
     * @brief Emitted when the name of the zone changes
     */
    void nameChanged();

    /**
     * @brief Emitted when the type of the zone changes
     */
    void typeChanged();

private:

    QHash<CelluloZoneClient*, qreal> clientsLastValues;  ///< Stores the most recent values calculated for clients

};

Q_DECLARE_METATYPE(CelluloZone*)

#endif // CELLULOZONE_H
