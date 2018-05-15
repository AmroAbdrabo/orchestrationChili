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

#include "CoordSpaceConverter.h"

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

    /** @brief Converter from physical sizes (mm) to screen sizes (pixels) */
    Q_PROPERTY(Cellulo::CoordSpaceConverter* toScreenSize READ getToScreenSize NOTIFY toScreenSizeChanged)

    /** @brief Converter from physical coords (mm) to screen coords (pixels) */
    Q_PROPERTY(Cellulo::CoordSpaceConverter* toScreenCoords READ getToScreenCoords NOTIFY toScreenCoordsChanged)

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
     * @brief Gets the converter from physical sizes to screen sizes
     *
     * @return Converter from physical sizes to screen sizes
     */
    Cellulo::CoordSpaceConverter* getToScreenSize(){ return &toScreenSize; }

    /**
     * @brief Gets the converter from physical coords to screen coords
     *
     * @return Converter from physical coords to screen coords
     */
    Cellulo::CoordSpaceConverter* getToScreenCoords(){ return &toScreenCoords; }

    /** @endcond */

signals:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Emitted when the physical size changes
     */
    void physicalSizeChanged();

    /**
     * @brief Emitted when the physical top left coordinate changes
     */
    void physicalTopLeftChanged();

    /**
     * @brief Emitted when toScreenSize changes
     */
    void toScreenSizeChanged();

    /**
     * @brief Emitted when toScreenCoords changes
     */
    void toScreenCoordsChanged();

    /** @endcond */

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

private slots:

    /**
     * @brief Updates the internal coordinates of toScreenSize according to this map
     */
    void updateToScreenSize();

    /**
     * @brief Updates the internal coordinates of toScreenCoords according to this map
     */
    void updateToScreenCoords();

private:

    /**
     * @brief Override; adds the added child to tiles if it is a HexTile
     *
     * @param change The change that occurred, must be ItemChildAddedChange
     * @param value Points to the added child when change is ItemChildAddedChange
     */
    void itemChange(ItemChange change, const ItemChangeData& value) override;

    QVector2D physicalTopLeft;           ///< Physical top left coordinate of this map in mm, used when drawing
    QVector2D physicalSize;              ///< Physical size described by this map in mm, used when drawing
    CoordSpaceConverter toScreenSize;    ///< Converter from physical sizes to screen sizes
    CoordSpaceConverter toScreenCoords;  ///< Converter from physical coords to screen coords




    //TODO: BETTER STORAGE
    QVariantList tiles;

};

/** @} */

}

#endif // HEXTILEMAP_H
