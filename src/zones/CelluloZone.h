/*
 * Copyright (C) 2015 EPFL
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
 * @version 1.0
 * @date 2015-03-04
 */

#ifndef CELLULOZONE_H
#define CELLULOZONE_H

#include <QQuickItem>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>
#include "CelluloZoneTypes.h"

/**
 * @brief CelluloZone Base Class for zones
 */
class CelluloZone : public QQuickItem{
    Q_OBJECT
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
     * @brief Get the properties of the zones in their rationalized form
     * @param realPlaygroundWidth playground width in mm
     * @param realPlaygroundHeight playground height in mm
     * @return map of rationalized properties
     */
    virtual QVariantMap getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight) = 0;


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
     * @param QJsonObject json object to be written
     */
    virtual void write(QJsonObject &json) = 0;


    /**
     * @brief Read the zone infos from the given json Object
     * @param json json object to be read
     */
    virtual void read(const QJsonObject &json) = 0;


public slots:
    /**
     * @brief slot associated to the CelluloBluetooth signal onPoseChanged, change zone quantity for this robot if robot exists and zone is active
     */
    void calculateOnPoseChanged();



protected:
    QString name;                               ///< name of the zone
    CelluloZoneTypes::ZoneType type;            ///< type of the zone
    int stackingOrder;                          ///< stacking order of the zone
    float marginThickeness;                     ///< margin accepted to tell if a robot is on zone's border (middle of the margin is the border)
    bool active;                                ///< true if zone is active false otherwise
    QHash<QString, float> cellulosCalculate;    ///< map of cellulorobot (represented by their MacAdress) and their zone quantity for this zone

    /**
     * @brief update the zone quantity of the robot for this zone
     * @param key robot MacAdress
     * @param value Zone quantity
     */
    void changeInCellulosCalculate(const QString& key, float value);

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

    /**
     * @brief Emitted when the zone quantity of any robot has changed
     * @param key robot concerned by this change of zone quantity
     * @param newValue new zone quantity for the robot with the MacAdress key
     */
    void calculateCelluloChanged(const QString& key, float newValue);

};

#endif // CELLULOZONE_H
