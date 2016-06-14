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
 * @file CelluloEnumDecl.h
 * @brief Header for CelluloBluetooth enums
 *
 * Adds the following methods to a Q_OBJECT given an enum E that starts with 0 and has
 * ENumElements as its last element:
 *
 *      QString EString(E value): Returns name of enum value
 *      QVariantList EStrings(): Returns list of all names of enum
 *
 * @author Ayberk Özgür
 * @date 2016-06-07
 */

#ifndef CELLULOENUMDECL_H
#define CELLULOENUMDECL_H

#include <QObject>
#include <QMetaEnum>
#include <QVariantList>
#include <QString>

#define CELLULO_ENUM_DECL(ENUMNAME) \
    QMetaEnum ENUMNAME ## _MetaEnum = QMetaEnum::fromType<ENUMNAME>(); \
    Q_INVOKABLE QString ENUMNAME ## String(ENUMNAME value){ \
        return ENUMNAME ## _MetaEnum.valueToKey(value); \
    } \
    Q_PROPERTY(QVariantList ENUMNAME ## Strings READ get ## ENUMNAME ## Strings() CONSTANT) \
    QVariantList get ## ENUMNAME ## Strings(){ \
        QVariantList list; \
        for(int i = 0; i < ENUMNAME ## NumElements; i++) \
            list << ENUMNAME ## String((ENUMNAME)i); \
        return list; \
    }

#endif // CELLULOENUMDECL_H
