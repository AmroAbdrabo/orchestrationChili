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
 * @brief Source for SVG file parsing and dumping utils
 * @author Ayberk Özgür
 * @date 2016-07-26
 */

#include "CelluloSVGUtil.h"

#include "../../zones/CelluloZoneTypes.h"

#include <QDebug>
#include <QUrl>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <cstdio>
#include <cstring>
#include <cmath>
#define NANOSVG_IMPLEMENTATION
#include "nanosvg/src/nanosvg.h"

CelluloSVGUtil::CelluloSVGUtil(QObject* parent) : QObject(parent){}

CelluloSVGUtil::~CelluloSVGUtil(){}

QString CelluloSVGUtil::dumpAllPathsToJSON(const QString& inSVGFile, const QString& outJSONFile, float dpi){
    QString inFilePath = QUrl(inSVGFile).toLocalFile();
    if(inFilePath.isEmpty())
        inFilePath = inSVGFile;
    QString outFilePath = QUrl(outJSONFile).toLocalFile();
    if(outFilePath.isEmpty())
        outFilePath = outJSONFile;

    struct NSVGimage* image = nsvgParseFromFile(inFilePath.toLatin1(), "mm", dpi);
    if(!image)
        return "CelluloSVGUtil::dumpAllPathsToJSON(): Couldn't open input file.";
    else{
        QFile saveFile(outFilePath);
        if(!saveFile.open(QIODevice::WriteOnly))
            return "CelluloSVGUtil::dumpAllPathsToJSON(): Couldn't open output file.";

        QJsonArray jsonZones;
        int numZone = 0;
        for(NSVGshape* shape = image->shapes; shape != NULL; shape = shape->next)
            for(NSVGpath* path = shape->paths; path != NULL; path = path->next){

                //Dump each path as one zone
                QJsonObject zoneObj;
                zoneObj["type"] = "POLYBEZIERBORDER";
                zoneObj["name"] = "SVG_DUMP_ZONE_" + QString::number(numZone);

                QJsonArray controlPointsArray;
                QJsonObject controlPointObj;
                for(int i=0; i<2*path->npts; i+=2){
                    controlPointObj["x"] = path->pts[i];
                    controlPointObj["y"] = path->pts[i + 1];
                    controlPointsArray.append(controlPointObj);
                }
                zoneObj["controlPoints"] = controlPointsArray;

                jsonZones.append(zoneObj);

                numZone++;
            }

        nsvgDelete(image);

        saveFile.write(QJsonDocument(jsonZones).toJson());

        return "CelluloSVGUtil::dumpAllPathsToJSON(): Dumped " + QString::number(numZone) + " zones.";
    }
}
