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

    /** @endcond */

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





    QVariantList tiles;

};

/** @} */

}

#endif // HEXTILEMAP_H
