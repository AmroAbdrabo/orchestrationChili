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

#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define NANOSVG_IMPLEMENTATION
#include "nanosvg/src/nanosvg.h"

CelluloSVGUtil::CelluloSVGUtil(QObject* parent) : QObject(parent){}

CelluloSVGUtil::~CelluloSVGUtil(){}

void CelluloSVGUtil::dumpAllPathsToJSON(const QString& inSVGFile, const QString& outJSONFile, float dpi){
    struct NSVGimage* image = nsvgParseFromFile(inSVGFile.toLatin1(), "mm", dpi);
    if(!image)
        qWarning() << "CelluloSVGUtil::dumpAllPathsToJSON(): Input file cannot be opened.";
    else{
        qDebug() << "CelluloSVGUtil::dumpAllPathsToJSON():" << image->width << " " << image->height;

        for(NSVGshape* shape = image->shapes; shape != NULL; shape = shape->next){
            for(NSVGpath* path = shape->paths; path != NULL; path = path->next){
                for(int i=0; i<2*path->npts; i++){
                    qDebug() << path->pts[i];
                }
            }
        }
        nsvgDelete(image);
    }
}
