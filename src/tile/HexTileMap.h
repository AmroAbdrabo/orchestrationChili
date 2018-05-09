/*
 * Copyright (C) 2018 EPFL
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
 * @file HexTileMap.h
 * @brief Header for a hexagonal multi-tile map
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#ifndef HEXTILEMAP_H
#define HEXTILEMAP_H

#include "PoseRemapper.h"

#include <QVector3D>
#include <QVariantList>
#include <QRectF>

namespace Cellulo {

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief Map built from hex tiles
 */
class HexTileMap : public PoseRemapper {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    /** @brief The physical coordinates of the top left of this map, in mm */
    Q_PROPERTY(QVector2D physicalTopLeft READ getPhysicalTopLeft WRITE setPhysicalTopLeft NOTIFY physicalTopLeftChanged)

    /** @brief The physical size of this map, in mm */
    Q_PROPERTY(QVector2D physicalSize READ getPhysicalSize WRITE setPhysicalSize NOTIFY physicalSizeChanged)



    //TODO: BETTER STORAGE
    Q_PROPERTY(QVariantList tiles MEMBER tiles)

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new hex tile map
     */
    explicit HexTileMap(QQuickItem* parent = 0);

    /**
     * @brief Deletes this hex tile map
     */
    virtual ~HexTileMap();

    /**
     * @brief Gets the physical size, used for drawing
     *
     * @return The physical size described by this map
     */
    QVector2D getPhysicalSize() const { return physicalSize; }

    /**
     * @brief Sets the new physical area, must have positive width/height
     *
     * @param physicalArea New physical area described by this map, used for drawing
     */
    void setPhysicalSize(QVector2D const& physicalArea);

    /**
     * @brief Gets the physical top left coordinate, used for drawing
     *
     * @return The physical top left coordinate described by this map
     */
    QVector2D getPhysicalTopLeft() const { return physicalTopLeft; }

    /**
     * @brief Sets the new physical top left coordinate
     *
     * @param physicalTopLeft New physical top left coordinate of this map, used for drawing
     */
    void setPhysicalTopLeft(QVector2D const& physicalTopLeft);

    /**
     * @brief Converts the given physical size to screen size according to the physical and screen sizes of this map
     *
     * @param  physicalSize Physical size of the object in mm
     * @return              Screen size of the object in pixels
     */
    QVector2D toScreenSize(QVector2D const& physicalSize) const;

    /**
     * @brief Converts the given physical point to screen point according to the physical and screen sizes of this map
     *
     * @param  physicalCoords Physical coordinates in mm
     * @return                Screen coordinates in pixels
     */
    QVector2D toScreenCoords(QVector2D const& physicalCoords) const;

    /** @endcond */

signals:

    /**
     * @brief Emitted when the physical size changes
     */
    void physicalSizeChanged();

    /**
     * @brief Emitted when the physical top left coordinate changes
     */
    void physicalTopLeftChanged();

    /**
     * @brief Emitted when screen children should redraw
     */
    void markedDirty();

public slots:

    /**
     * @brief Remaps the given pose to another pose based on the hex tile configuration
     *
     * @param  pose Given pose (x,y is in mm, z is orientation in degrees)
     * @return Remapped pose (x,y is in mm, z is orientation in degrees)
     */
    virtual QVector3D remapPose(QVector3D const& pose) override;

private:

    /**
     * @brief Override; adds the added child to tiles if it is a HexTile
     *
     * @param change The change that occurred, must be ItemChildAddedChange
     * @param value Points to the added child when change is ItemChildAddedChange
     */
    void itemChange(ItemChange change, const ItemChangeData& value) override;

    QVector2D physicalTopLeft;  ///< Physical top left coordinate of this map in mm, used when drawing
    QVector2D physicalSize;     ///< Physical size described by this map in mm, used when drawing





    //TODO: BETTER STORAGE
    QVariantList tiles;

};

/** @} */

}

#endif // HEXTILEMAP_H
