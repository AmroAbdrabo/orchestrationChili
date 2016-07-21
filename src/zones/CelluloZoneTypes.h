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

#include <QObject>

#include "../CelluloEnumDecl.h"
class CelluloZone;

class CelluloZoneTypes : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloZoneTypes(QObject* parent = 0);
    ~CelluloZoneTypes();

    /**
     * @brief List of possible zones
     */
    enum ZoneType {
        ANGLEDIFFERENCE = 0,
        ANGLEINTERVALINNER,
        ANGLEINTERVALBORDER,
        ANGLEINTERVALDISTANCE,
        CIRCLEINNER,
        CIRCLEBORDER,
        CIRCLEDISTANCE,
        RECTANGLEINNER,
        RECTANGLEBORDER,
        RECTANGLEDISTANCE,
        LINESEGMENTDISTANCE,
        LINEDISTANCESIGNED,
        LINEBORDER,
        POINTDISTANCE,
        RPOLYGONINNER,
        RPOLYGONBORDER,
        RPOLYGONDISTANCE,
        IRPOLYGONINNER,
        IRPOLYGONBORDER,
        IRPOLYGONDISTANCE,
        POLYBEZIERINNER,
        ZoneTypeNumElements
    };
    Q_ENUM(ZoneType)
    CELLULO_ENUM_DECL(ZoneType)

    /**
     * @brief Converts the QString to its ZoneType representation
     *
     * @param typeName QString to be converted
     * @return ZoneType Reprensentation of the QString
     */
    Q_INVOKABLE static ZoneType typeFromString(const QString &typeName);

    /**
     * @brief Creates a new zone based on the given type
     *
     * @param type The desired type
     * @return Pointer to the created zone
     */
    Q_INVOKABLE static CelluloZone* newZoneFromType(ZoneType type);

};

Q_DECLARE_METATYPE(CelluloZoneTypes::ZoneType)

#endif // CELLULOZONETYPES_H
