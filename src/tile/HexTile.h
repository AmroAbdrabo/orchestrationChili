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
 * @file HexTile.h
 * @brief Header for a hexagonal tile definition
 * @author Ayberk Özgür
 * @date 2018-04-27
 */

#ifndef HEXTILE_H
#define HEXTILE_H

#include <QQuickItem>

namespace Cellulo {

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief Hexagonal tile definition
 */
class HexTile : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new hex tile
     */
    explicit HexTile(QQuickItem* parent = 0);

    /**
     * @brief Deletes this hex tile
     */
    virtual ~HexTile();

    /** @endcond */

private:



};

/** @} */

}

#endif // HEXTILE_H
