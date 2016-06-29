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
#include <QMetaObject>
#include <QEvent>

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
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ getFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(QColor lineColor WRITE setLineColor READ getLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(qreal lineThickness WRITE setLineThickness READ getLineThickness NOTIFY lineThicknessChanged)
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
     * @brief Gets the color to fill insides of shapes
     *
     * @return The fill color
     */
    QColor getFillColor(){
        return fillColor;
    }

    /**
     * @brief Updates the color to fill insides of shapes
     *
     * @param newColor The new fill color
     */
    void setFillColor(QColor newColor);

    /**
     * @brief Gets the color to draw borders of shapes
     *
     * @return The line color
     */
    QColor getLineColor(){
        return lineColor;
    }

    /**
     * @brief Updates the color to draw borders of shapes
     *
     * @param newColor The new line color
     */
    void setLineColor(QColor newColor);

    /**
     * @brief Gets the border thickness
     *
     * @return Border thickness in mm
     */
    qreal getLineThickness(){
        return lineThickness;
    }

    /**
     * @brief Updates the border thickness
     *
     * @param newThickness Border thickness in mm
     */
    void setLineThickness(qreal newThickness);

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
    void paint(QPainter* painter) override;

signals:

    /**
     * @brief Emitted when the fill color changes
     */
    void fillColorChanged();

    /**
     * @brief Emitted when the line color changes
     */
    void lineColorChanged();

    /**
     * @brief Emitted when the line thickness changes
     */
    void lineThicknessChanged();

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
    void setWidthToParent();

    /**
     * @brief Sets this item's height equal to the parent's height
     */
    void setHeightToParent();

private:

    /**
     * @brief Disconnects old binding, connects new binding and updates width/height
     *
     * @param newParent The new parent
     */
    void updateParentWidthHeightBinding(QQuickItem* newParent);

    /**
     * @brief Override; binds the new parent's height/width to this object
     *
     * @param change The change that occurred, must be ItemParentHasChanged
     * @param value Points to the new parent when change is ItemParentHasChanged
     */
    void itemChange(ItemChange change, const ItemChangeData& value) override;

    QColor fillColor;                               ///< Color to be used on inner areas
    QColor lineColor;                               ///< Color to be used on borders
    qreal lineThickness;                            ///< Thickness of all lines and points in pixels
    CelluloZone* associatedZone;                    ///< The zone that will draw on the painter
    qreal physicalPlaygroundWidth;                  ///< Physical playground width in mm
    qreal physicalPlaygroundHeight;                 ///< Physical playground height in mm

    QMetaObject::Connection parentWidthConnection;  ///< Connection to bind this object's width to the parent
    QMetaObject::Connection parentHeightConnection; ///< Connection to bind this object's height to the parent
};

#endif // CELLULOZONEPAINTEDITEM_H
