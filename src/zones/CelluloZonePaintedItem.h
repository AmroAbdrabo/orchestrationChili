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
 * @file CelluloZonePaintedItem.h
 * @brief Header for a QML compatible QQuickPaintedItem for Cellulo zones
 * @author Ayberk Özgür
 * @date 2016-06-28
 */

#ifndef CELLULOZONEPAINTEDITEM_H
#define CELLULOZONEPAINTEDITEM_H

#include <QQuickPaintedItem>

#include "CelluloZone.h"

class CelluloZone;

/**
 * @brief A QML compatible QQuickPaintedItem for CelluloZones
 *
 * Visually covers the parent (from (0,0) to (parent.width,parent.height)) and draws the zone at the appropriate place
 */
class CelluloZonePaintedItem : public QQuickPaintedItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_PROPERTY(CelluloZone* associatedZone WRITE setAssociatedZone READ getAssociatedZone NOTIFY associatedZoneChanged)
    Q_PROPERTY(qreal physicalPlaygroundWidth WRITE setPhysicalPlaygroundWidth READ getPhysicalPlaygroundWidth NOTIFY physicalPlaygroundWidthChanged)
    Q_PROPERTY(qreal physicalPlaygroundHeight WRITE setPhysicalPlaygroundHeight READ getPhysicalPlaygroundHeight NOTIFY physicalPlaygroundHeightChanged)

public:

    /**
     * @brief Creates a new CelluloZonePaintedItem
     *
     * @param parent QML parent
     */
    explicit CelluloZonePaintedItem(QQuickItem* parent = 0);

    /**
     * @brief Sets the associated zone
     *
     * @param associatedZone The CelluloZone that will take care of painting
     */
    void setAssociatedZone(CelluloZone* zone);

    /**
     * @brief Gets the associated zone
     *
     * @return The CelluloZone that takes care of painting
     */
    CelluloZone* getAssociatedZone(){
        return associatedZone;
    }

    /**
     * @brief Changes the physical playground width
     *
     * @param newWidth New width in millimeters
     */
    void setPhysicalPlaygroundWidth(qreal newWidth);

    /**
     * @brief Gets the physical playground width
     *
     * @return The physical playground width in mm
     */
    qreal getPhysicalPlaygroundWidth(){
        return physicalPlaygroundWidth;
    }

    /**
     * @brief Changes the physical playground height
     *
     * @param newWidth New height in millimeters
     */
    void setPhysicalPlaygroundHeight(qreal newHeight);

    /**
     * @brief Gets the physical playground height
     *
     * @return The physical playground height in mm
     */
    qreal getPhysicalPlaygroundHeight(){
        return physicalPlaygroundHeight;
    }

    /**
     * @brief Implementation of pure virtual function in QQuickPaintedItem
     *
     * @param painter Object to paint on
     */
    void paint(QPainter* painter);

signals:

    /**
     * @brief Emitted when the associated zone changes
     */
    void associatedZoneChanged();

    /**
     * @brief Emitted when the physical playground width changes
     */
    void physicalPlaygroundWidthChanged();

    /**
     * @brief Emitted when the physical playground height changes
     */
    void physicalPlaygroundHeightChanged();

private slots:

    /**
     * @brief Sets this item's width equal to the parent's width
     */
    void parentWidthChanged();

    /**
     * @brief Sets this item's height equal to the parent's height
     */
    void parentHeightChanged();

private:

    CelluloZone* associatedZone;    ///< The zone that will draw on the painter
    qreal physicalPlaygroundWidth;  ///< Physical playground width in mm
    qreal physicalPlaygroundHeight; ///< Physical playground height in mm
};

#endif // CELLULOZONEPAINTEDITEM_H
