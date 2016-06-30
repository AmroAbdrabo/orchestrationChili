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
 * @file CelluloZonePolygon.h
 * @brief Header for the polygon zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONEPOLYGON_H
#define CELLULOZONEPOLYGON_H

#include "CelluloZone.h"
#include <math.h>

/**
 * @brief CelluloZone Base Class for polygonal zones
 */
class CelluloZonePolygon : public CelluloZone {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(QList<QVector2D> vertices WRITE setVertices READ getVertices NOTIFY verticesChanged)

public:

    /**
     * @brief Creates a new Cellulo polygonal zone
     */
    CelluloZonePolygon();

    /**
     * @brief Gets the polygon's vertices
     *
     * @return List of polygon's vertices
     */
    const QList<QVector2D>& getVertices(){
        return vertices;
    }

    /**
     * @brief Sets the polygon's vertices
     *
     * @param newVertices List of new vertices
     */
    virtual void setVertices(const QList<QVector2D>& newVertices);

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
     * @brief Emitted when the vertices change
     */
    void verticesChanged();

protected:

    /**
     * @brief Updates the bounding rectangle from the new list of vertices
     */
    void updateBounds();

    /**
     * @brief isPointOnPolygonBorder calculate if point is on border of the polygon
     * @param xPoint x position of the point to be checked
     * @param yPoint y position of the point to be checked
     * @return 1 if the robot is on the border of this polygon 0 otherwise
     */
    //float isPointOnPolygonBorder(float xPoint, float yPoint);

    /**
     * @brief getPointToPolygonDistance calculate distance between point and polygon
     * @param xPoint x position of the point to be checked
     * @param yPoint y position of the point to be checked
     * @return distance between point and polygon
     */
    //float getPointToPolygonDistance(float xPoint, float yPoint);

    QList<QVector2D> vertices; ///< Vertices of the polygon
    float minX;                ///< Minimal x bound for the polygon
    float maxX;                ///< Maximum x bound for the polygon
    float minY;                ///< Minimum y bound for the polygon
    float maxY;                ///< Maximum y bound for the polygon

};


/**
 * @brief CelluloZone Base Class for irregular polygonal zones
 */
class CelluloZoneIrregularPolygon : public CelluloZonePolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

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

};

/**
 * @brief CelluloZone Specific Class for irregular polygonal zones inner determination
 */
class CelluloZoneIrregularPolygonInner : public CelluloZoneIrregularPolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneIrregularPolygonInner();

    /**
     * @brief Calculate whether the robot lies inside this irregular polygonal zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is inside this irregular polygonal zone 0 otherwise
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
 * @brief CelluloZone Specific Class for irregular polygonal zones border determination
 */
class CelluloZoneIrregularPolygonBorder : public CelluloZoneIrregularPolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneIrregularPolygonBorder();

    /**
     * @brief Calculate whether the robot lies on the border of this irregular polygonal zone (given the zone's margin)
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is on the border of this irregular polygonal zone (given the zone's margin) 0 otherwise
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
 * @brief CelluloZone Specific Class for irregular polygonal zones distance determination
 */
class CelluloZoneIrregularPolygonDistance : public CelluloZoneIrregularPolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneIrregularPolygonDistance();

    /**
     * @brief Calculate the distance between the robot pose and the border of this irregular polygonal zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return the distance between the robot pose and the border of this irregular polygonal zone
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

class CelluloZoneRegularPolygon : public CelluloZonePolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(int numEdges WRITE setNumEdges READ getNumEdges NOTIFY numEdgesChanged)
    Q_PROPERTY(float x WRITE setX READ getX NOTIFY xChanged)
    Q_PROPERTY(float y WRITE setY READ getY NOTIFY yChanged)
    Q_PROPERTY(float r WRITE setR READ getR NOTIFY rChanged)
    Q_PROPERTY(float rotAngle WRITE setRotAngle READ getRotAngle NOTIFY rotAngleChanged)

public:

    /**
     * @brief Creates a new Cellulo regular polygonal zone
     */
    CelluloZoneRegularPolygon();

    /**
     * @brief Gets the number of edges of the regular polygon
     * @return The number of edges of the regular polygon
     */
    int getNumEdges(){
        return numEdges;
    }
    void setNumEdges(int newNumEdge);

    /**
     * @brief Gets the x position of regular polygon definer circle's center
     * @return X position of regular polygon definer circle's center
     */
    float getX(){
        return x;
    }

    /**
     * @brief Sets the x position of the center of the regular polygon
     * @param newX Center x position in mm
     */
    void setX(float newX);

    /**
     * @brief Gets the y position of regular polygon definer circle's center
     * @return Y position of regular polygon definer circle's center
     */
    float getY(){
        return y;
    }

    /**
     * @brief Sets the y position of the center of the regular polygon
     * @param newY Center y position in mm
     */
    void setY(float newY);

    /**
     * @brief Gets the radius of the regular polygon definer circle
     * @return R the radius of the regular polygon definer circle
     */
    float getR(){
        return r;
    }

    /**
     * @brief Sets the radius of the outer circle of the regular polygon
     * @param newR Radius of the outer circle in mm
     */
    void setR(float newR);

    /**
     * @brief Gets the rotational angle of the regular polygon
     * @return The rotational angle of the regular polygon
     */
    float getRotAngle(){
        return rotAngle;
    }

    /**
     * @brief Sets the orientation of the regular polygon
     * @param newRotAngle The
     */
    void setRotAngle(float newRotAngle);

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

    float numEdges;                         ///< number of edges of the regular polygon
    float x;                                ///< x position of regular polygon defined circle's center
    float y;                                ///< y position of regular polygon defined circle's center
    float r;                                ///< radius of the regular polygon defined circle
    float rotAngle;                         ///< rotational angle of the regular polygon

private:

    /**
     * @brief Define regular polygon's point following the polygon defined circle, the number of edges and the rotational angle
     * @return points of the regular polygon
     */
    QList<QPointF> createPolygonPointsFromOuterCircle();

signals:

    /**
     * @brief Emitted when the number of edges of the regular polygonal zone changes
     */
    void numEdgesChanged();

    /**
     * @brief Emitted when the x position of regular polygon defined circle's center of the regular polygonal zone changes
     */
    void xChanged();

    /**
     * @brief Emitted when the y position of regular polygon defined circle's center of the regular polygonal zone changes
     */
    void yChanged();

    /**
     * @brief Emitted when the radius of the regular polygon defined circle of the regular polygonal zone changes
     */
    void rChanged();

    /**
     * @brief Emitted when the rotational angle of the regular polygonal zone changes
     */
    void rotAngleChanged();

};

/**
 * @brief CelluloZone Specific Class for regular polygonal zones inner determination
 */
class CelluloZoneRegularPolygonInner : public CelluloZoneRegularPolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneRegularPolygonInner();

    /**
     * @brief Calculate whether the robot lies inside this regular polygonal zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is inside this regular polygonal zone 0 otherwise
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
 * @brief CelluloZone Specific Class for regular polygonal zones border determination
 */
class CelluloZoneRegularPolygonBorder : public CelluloZoneRegularPolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneRegularPolygonBorder();

    /**
     * @brief Calculate whether the robot lies on the border of this regular polygonal zone (given the zone's margin)
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return 1 if the robot is on the border of this regular polygonal zone (given the zone's margin) 0 otherwise
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
 * @brief CelluloZone Specific Class for regular polygonal zones distance determination
 */
class CelluloZoneRegularPolygonDistance : public CelluloZoneRegularPolygon {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneRegularPolygonDistance();

    /**
     * @brief Calculate the distance between the robot pose and the border of this regular polygonal zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return the distance between the robot pose and the border of this regular polygonal zone
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

#endif // CELLULOZONEPOLYGON_H
