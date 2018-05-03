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

#include "HexTileStandardCoords.h"

namespace Cellulo {

class HexTileStandardCoords;

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief Hexagonal tile definition, built in axial coordinates
 *
 * See https://www.redblobgames.com/grids/hexagons/#coordinates-axial.
 */
class HexTile : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
        /* *INDENT-ON* */

    /** @brief Target Q index (horizontal) in axial discrete hex tile coordinates */
    Q_PROPERTY(int q MEMBER q NOTIFY qChanged)

    /** @brief Target R index (vertical, 120 degrees to the Q axis) in axial discrete hex tile coordinates */
    Q_PROPERTY(int r MEMBER r NOTIFY rChanged)

    /** @brief Starting X coordinate of the rectangular source space (mm) */
    Q_PROPERTY(float sourceLeft MEMBER sourceLeft NOTIFY sourceLeftChanged)

    /** @brief Starting Y coordinate of the rectangular source space (mm) */
    Q_PROPERTY(float sourceTop MEMBER sourceTop NOTIFY sourceTopChanged)

    /** @brief Ending X coordinate of the rectangular source space (mm) */
    Q_PROPERTY(float sourceRight MEMBER sourceRight NOTIFY sourceRightChanged)

    /** @brief Ending Y coordinate of the rectangular source space (mm) */
    Q_PROPERTY(float sourceBottom MEMBER sourceBottom NOTIFY sourceBottomChanged)

    /** @brief X coordinate of the center of the hex tile in the source space, with respect to the top/left of the source space (mm) */
    Q_PROPERTY(float sourceCenterX MEMBER sourceCenterX NOTIFY sourceCenterXChanged)

    /** @brief Y coordinate of the center of the hex tile in the source space, with respect to the top/left of the source space (mm) */
    Q_PROPERTY(float sourceCenterY MEMBER sourceCenterY NOTIFY sourceCenterYChanged)

    /** @brief Standard coordinate description, null by default; if used, autosets the source* properties so they must not be manually modified */
    Q_PROPERTY(Cellulo::HexTileStandardCoords* standardCoords WRITE setStandardCoords READ getStandardCoords NOTIFY standardCoordsChanged)

    /** @brief The fill color of the rendering of this tile, white by default */
    Q_PROPERTY(QColor fillColor MEMBER fillColor NOTIFY fillColorChanged)

    /** @brief The border color of the rendering of this tile, black by default */
    Q_PROPERTY(QColor borderColor MEMBER borderColor NOTIFY borderColorChanged)

    /** @brief Size of the border with respect to the width, between 0.0 and 1.0, by default 0.05 */
    Q_PROPERTY(qreal borderSize MEMBER borderSize NOTIFY borderSizeChanged)



    /** @brief Default read-only tile width (mm) */
    Q_PROPERTY(float tileWidthDefault CONSTANT MEMBER HEX_TILE_WIDTH_DEFAULT)

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

    static constexpr float HEX_TILE_WIDTH_DEFAULT = 99.0f; ///< Default physical width of the hex tile in mm (height would be 2*width/sqrt(3))

    /**
     * @brief Sets the new standard hex tile coordinate description
     *
     * @param standardCoords New standard hex tile coordinate description
     */
    void setStandardCoords(Cellulo::HexTileStandardCoords* standardCoords);

    /**
     * @brief Gets the standard hex tile coordinate description
     *
     * @return The current standard hex tile coordinate description
     */
    Cellulo::HexTileStandardCoords* getStandardCoords(){ return standardCoords; }

signals:

    /**
     * @brief Emitted when q changes
     */
    void qChanged();

    /**
     * @brief Emitted when r changes
     */
    void rChanged();

    /**
     * @brief Emitted when the standard hex tile coordinate definition changes
     */
    void standardCoordsChanged();

    /**
     * @brief Emitted when sourceLeft changes
     */
    void sourceLeftChanged();

    /**
     * @brief Emitted when sourceRight changes
     */
    void sourceRightChanged();

    /**
     * @brief Emitted when sourceTop changes
     */
    void sourceTopChanged();

    /**
     * @brief Emitted when sourceBottom changes
     */
    void sourceBottomChanged();

    /**
     * @brief Emitted when sourceCenterX changes
     */
    void sourceCenterXChanged();

    /**
     * @brief Emitted when sourceCenterY changes
     */
    void sourceCenterYChanged();

    /**
     * @brief Emitted when the fill color changes
     */
    void fillColorChanged();

    /**
     * @brief Emitted when the border color changes
     */
    void borderColorChanged();

    /**
     * @brief Emitted when the border size changes
     */
    void borderSizeChanged();

public slots:

    /**
     * @brief Gets whether the given point is in the source space
     *
     * @param Point Given point (mm)
     * @return Whether the given point is in the source space
     */
    bool sourceContains(QVector2D const& point);

    /**
     * @brief Gets the point's coordinates in the source space, with respect to the tile's center
     *
     * Gets (point - tileTopLeft - tileCenter).
     *
     * @param  point Given point (mm)
     * @return Given point's coordinates in the source space, width respect to the tile's center
     */
    QVector2D sourceCoordinates(QVector2D const& point);

    /**
     * @brief Gets the tile center's coordinates in the continuous mapped space composed of hex tiles
     *
     * @param  tileWidth Width of the tile in mm (height would be 2*width/sqrt(3))
     * @return Tile center's coordinates in the continuous mapped space composed of hex tiles
     */
    QVector2D hexOffset(float tileWidth = HEX_TILE_WIDTH_DEFAULT);

private slots:

    /**
     * @brief Sets the appropriate source coordinates according to the standard coordinate description
     */
    void updateFromStandardCoords();

private:

    /**
     * @brief Implementation of the rendering routine for this hex tile
     *
     * @param  oldNode             [description]
     * @param  updatePaintNodeData [description]
     * @return                     [description]
     */
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData) override;

    int q;                                          ///< Q index (horizontal) in axial hex tile coordinates
    int r;                                          ///< R index (vertical, 120 degrees to the Q axis) in axial hex tile coordinates
    float sourceLeft;                               ///< Starting X coordinate of the rectangular source space (mm)
    float sourceTop;                                ///< Starting Y coordinate of the rectangular source space (mm)
    float sourceRight;                              ///< Ending X coordinate of the rectangular source space (mm)
    float sourceBottom;                             ///< Ending Y coordinate of the rectangular source space (mm)
    float sourceCenterX;                            ///< X coordinate of the center of the hex tile in the source space, with respect to the top/left of the source space (mm)
    float sourceCenterY;                            ///< Y coordinate of the center of the hex tile in the source space, with respect to the top/left of the source space (mm)
    Cellulo::HexTileStandardCoords* standardCoords; ///< Standard hex tile coordinate description if available

    QColor fillColor;                               ///< Fill color of the rendering of this tile
    QColor borderColor;                             ///< Border color of the rendering of this tile
    qreal borderSize;                               ///< Border size of the rendering with respect to the width
};

/** @} */

}

Q_DECLARE_METATYPE(Cellulo::HexTile*)

#endif // HEXTILE_H
