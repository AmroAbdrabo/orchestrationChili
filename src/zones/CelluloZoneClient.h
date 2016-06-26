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
 * @file CelluloZoneClient.h
 * @brief Header for the Cellulo zone client
 * @author Ayberk Özgür
 * @date 2016-06-26
 */

#include <QQuickItem>

#include "CelluloZone.h"

/**
 * @brief Describes an object with a physical pose (e.g a robot) that may interact with Cellulo zones
 */
class CelluloZoneClient : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /**
     * @brief Creates a new zone client
     * @param parent Qt parent
     */
    explicit CelluloZoneClient(QQuickItem* parent = 0);

signals:

    /**
     * @brief Emitted when a zone's value with respect to this object changes
     *
     * @param zone The zone whose value has changed
     * @param value The new value
     */
    void zoneValueChanged(const CelluloZone& zone, qreal value);

    /**
     * @brief Emitted when the physical pose of the object changes
     *
     * @param x New x coordinate in mm
     * @param y New y coordinate in mm
     * @param theta New orientation in degrees
     */
    void poseChanged(qreal x, qreal y, qreal theta);

};
