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
 * @file HexTileMapAutoBuilder.h
 * @brief Header for a hexagonal tile autobuilder
 * @author Ayberk Özgür
 * @date 2018-05-18
 */

#ifndef HEXTILEMAPAUTOBUILDER_H
#define HEXTILEMAPAUTOBUILDER_H

#include <QQuickItem>
#include <QVector2D>
#include <QVector3D>

#include "AxialHexCoords.h"
#include "HexTileStandardCoords.h"
#include "HexTileMap.h"

namespace Cellulo {

class HexTileMap;

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief HexTileMap autobuilder, keeps history of poses for one physical/virtual object (e.g robot) and adds unknown tiles to their correct places
 */
class HexTileMapAutoBuilder : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new HexTileMap autobuilder
     */
    explicit HexTileMapAutoBuilder(QObject* parent = 0);

    /**
     * @brief Deletes this HexTileMap autobuilder
     */
    virtual ~HexTileMapAutoBuilder();

    /** @endcond */

signals:

    /** @cond DO_NOT_DOCUMENT */


    /** @endcond */

public slots:

    void senderKidnappedChanged();

    void resetAutoBuild();

    void processKnownTile(QVector2D const& position, AxialHexCoords* tileCoords);

    QVector3D processUnknownTile(QVector3D const& sourcePose, bool addNewTile, bool mapEmpty, Cellulo::HexTileMap* tileMap = nullptr);

private:

    bool autoBuildKnownCoordsExist;         ///< Whether there is a reading from any known tile
    AxialHexCoords autoBuildKnownCoords;    ///< The hex coordinates of the known tile, if any
    QList<QVector2D> autoBuildKnownHistory; ///< The remapped coordinate history on the known tile

    HexTileStandardCoords* autoBuildUnknownStdCoords;   ///< The autodetected standard coordinates of the unknown tile
    QList<QVector2D> autoBuildUnknownHistory;           ///< The raw source coordinate history on the unknown tile

    constexpr static int autoBuildKnownHistorySize = 5;     ///< Maximum number of directions on the known tile to consider
    constexpr static int autoBuildKnownHistoryMinSize = 3;  ///< Minimum number of directions on the known tile to consider
    constexpr static int autoBuildUnknownHistorySize = 3;   ///< Number of directions on the unknown tile to consider
    constexpr static float autoBuildMinVecSize = 2.0f;  ///< Min direction length in mm for consideration in unknown tile generation

};

/** @} */

}

Q_DECLARE_METATYPE(Cellulo::HexTileMapAutoBuilder*)

#endif // HEXTILEMAPAUTOBUILDER_H
