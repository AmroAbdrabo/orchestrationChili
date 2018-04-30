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
 * @file HexTileRemapper.h
 * @brief Header for a hexagonal multi-tile remapper
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#ifndef HEXTILEREMAPPER_H
#define HEXTILEREMAPPER_H

#include "PoseRemapper.h"

#include <QVector3D>

namespace Cellulo {

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief Offsets the pose of the robot such that the source
 */
class HexTileRemapper : public PoseRemapper {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new hex tile remaper
     */
    explicit HexTileRemapper(QQuickItem* parent = 0);

    /**
     * @brief Deletes this hex tile remapper
     */
    virtual ~HexTileRemapper();

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



};

/** @} */

}

#endif // HEXTILEREMAPPER_H
