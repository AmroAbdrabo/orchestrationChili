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
 * @file CelluloSVGUtil.h
 * @brief Header for SVG file parsing and dumping utils
 * @author Ayberk Özgür
 * @date 2016-07-26
 */

#ifndef CELLULOSVGUTIL_H
#define CELLULOSVGUTIL_H

#include <QObject>
#include <QString>

class CelluloSVGUtil : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloSVGUtil(QObject* parent = 0);
    ~CelluloSVGUtil();

    /**
     * @brief Parses the given SVG file and dumps all paths into the given JSON file in the CelluloZonePolyBezier format
     *
     * @param inSVGFile Full path to the SVG file
     * @param outJSONFile Full path to the JSON file, it will be overwritten
     * @param dpi Dots Per Inch to be used during conversion to millimeters
     */
    Q_INVOKABLE static void dumpAllPathsToJSON(const QString& inSVGFile, const QString& outJSONFile, float dpi);

};

#endif // CELLULOSVGUTIL_H
