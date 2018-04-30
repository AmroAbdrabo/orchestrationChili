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
 * @file OffsetRemapper.h
 * @brief Header for offset remapper base
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#ifndef OFFSETREMAPPER_H
#define OFFSETREMAPPER_H

#include "PoseRemapper.h"

#include <QVector3D>

namespace Cellulo {

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief Offsets the pose of the robot by a given amount
 */
class OffsetRemapper : public PoseRemapper {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    /** @brief X offset in mm */
    Q_PROPERTY(qreal deltaX MEMBER deltaX)

    /** @brief Y offset in mm */
    Q_PROPERTY(qreal deltaY MEMBER deltaY)

    /** @brief Theta offset in degrees */
    Q_PROPERTY(qreal deltaTheta MEMBER deltaTheta)

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new offset remapper
     */
    explicit OffsetRemapper(QQuickItem* parent = 0);

    /**
     * @brief Deletes this remapper
     */
    virtual ~OffsetRemapper();

    /** @endcond */

public slots:

    /**
     * @brief Remaps the given pose to another pose based on some rule to be determined by the extending classes
     *
     * @param  pose Given pose (x,y is in mm, z is orientation in degrees)
     * @return Remapped pose (x,y is in mm, z is orientation in degrees)
     */
    virtual QVector3D remapPose(QVector3D const& pose) override;

private:

    qreal deltaX;     ///< X offset in mm
    qreal deltaY;     ///< Y offset in mm
    qreal deltaTheta; ///< Theta offset in deg

};

/** @} */

}

#endif // OFFSETREMAPPER_H
