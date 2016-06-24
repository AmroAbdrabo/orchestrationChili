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
 * @file CelluloZoneTypes.cpp
 * @brief Source for zone type tools
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZoneTypes.h"

QString CelluloZoneTypes::typeToString(const CelluloZoneTypes::ZoneType &type){
    const QMetaObject &mo = CelluloZoneTypes::staticMetaObject;
    int index = mo.indexOfEnumerator("ZoneType");
    QMetaEnum metaEnum = mo.enumerator(index);
    return metaEnum.valueToKey(type);
}

CelluloZoneTypes::ZoneType CelluloZoneTypes::typeFromString(const QString &typeName){
    const QMetaObject &mo = CelluloZoneTypes::staticMetaObject;
    int index = mo.indexOfEnumerator("ZoneType");
    QMetaEnum metaEnum = mo.enumerator(index);
    int value = metaEnum.keyToValue(qPrintable(typeName));
    return static_cast<CelluloZoneTypes::ZoneType>(value);
}
