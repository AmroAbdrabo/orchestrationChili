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
 * @file PositionRemapper.h
 * @brief Header for position remapper base
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#ifndef POSITIONREMAPPER_H
#define POSITIONREMAPPER_H

#include<QObject>
#include<QVector2D>

namespace Cellulo{

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief Abstract object that should remap given positions to another positions based on some rule to be determined by the extending classes
 *
 * @abstract
 */
class PositionRemapper : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new Cellulo zone
     */
    explicit PositionRemapper(QObject* parent = 0);

    /**
     * @brief Deletes this zone and its PaintedItem if it exists
     */
    ~PositionRemapper();

    /** @endcond */

public slots:

    /**
     * @brief Remaps the given position to another position based on some rule to be determined by the extending classes
     *
     * @param  position Given position
     * @return Remapped position
     */
    virtual QVector2D remapPosition(QVector2D const& position) = 0;

};

/** @} */

}

Q_DECLARE_METATYPE(Cellulo::PositionRemapper*)

#endif // POSITIONREMAPPER_H
