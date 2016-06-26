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
 * @file CelluloZoneTypes.h
 * @brief Header for zone type tools
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#ifndef CELLULOZONETYPES_H
#define CELLULOZONETYPES_H

#include <QQuickItem>

/**
 * @brief holds Q_ENUMS used from frontend and associtated conversion functions
 */
class CelluloZoneTypes : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */
    Q_ENUMS(ZoneType)

public:

    enum ZoneType {
        CIRCLEINNER = 0,
        CIRCLEBORDER,
        CIRCLEDISTANCE,
        RECTANGLEINNER,
        RECTANGLEBORDER,
        RECTANGLEDISTANCE,
        LINEINNER,
        LINEDISTANCE,
        POINTDISTANCE,
        RPOLYGONINNER,
        RPOLYGONBORDER,
        RPOLYGONDISTANCE,
        IRPOLYGONINNER,
        IRPOLYGONBORDER,
        IRPOLYGONDISTANCE
    };

    /**
     * @brief convert the enum type to a Qstring
     * @param type ZoneType to be converted
     * @return QString representation of the ZoneType
     */
    Q_INVOKABLE static QString typeToString(const CelluloZoneTypes::ZoneType &type);

    /**
     * @brief convert the QString to its ZoneType representation
     * @param typeName QString to be converted
     * @return ZoneType reprensentation of the QString
     */
    Q_INVOKABLE static CelluloZoneTypes::ZoneType typeFromString(const QString &typeName);

};

#endif // CELLULOZONETYPES_H
