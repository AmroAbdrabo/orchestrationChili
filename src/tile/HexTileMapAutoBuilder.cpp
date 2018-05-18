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
 * @file HexTileMapAutoBuilder.cpp
 * @brief Source for a hexagonal tile autobuilder
 * @author Ayberk Özgür
 * @date 2018-05-18
 */

#include "HexTileMapAutoBuilder.h"

#include "../util/math/CelluloMathUtil.h"

namespace Cellulo{

HexTileMapAutoBuilder::HexTileMapAutoBuilder(QObject* parent) : QObject(parent){
    autoBuildKnownCoordsExist = false;
    autoBuildUnknownStdCoords = nullptr;
}

HexTileMapAutoBuilder::~HexTileMapAutoBuilder(){}

void HexTileMapAutoBuilder::resetAutoBuild(){
    autoBuildKnownHistory.clear();
    autoBuildUnknownHistory.clear();
    autoBuildKnownCoordsExist = false;
    if(autoBuildUnknownStdCoords){
        delete autoBuildUnknownStdCoords;
        autoBuildUnknownStdCoords = nullptr;
    }
}

void HexTileMapAutoBuilder::processKnownTile(QVector2D const& position, AxialHexCoords* coords){
    if(autoBuildKnownCoordsExist){
        if(autoBuildKnownCoords.getQ() != coords->getQ() || autoBuildKnownCoords.getR() != coords->getR()){
            autoBuildKnownCoords.copyFrom(*coords);
            autoBuildKnownHistory.clear();
        }
    }
    else{
        autoBuildKnownCoordsExist = true;
        autoBuildKnownCoords.copyFrom(*coords);
    }
    autoBuildKnownHistory.append(position);
    if(autoBuildKnownHistory.size() > autoBuildKnownHistorySize)
        autoBuildKnownHistory.removeFirst();
}

QVector3D HexTileMapAutoBuilder::processUnknownTile(QVector3D const& sourcePose, bool addNewTile, bool mapEmpty, Cellulo::HexTileMap* tileMap){
    QVector2D sourcePosition = sourcePose.toVector2D();
    QVector3D result(0,0,0);

    //Get the standard tile coords of the unknown position
    HexTileStandardCoords* newUnknownStdCoords = new HexTileStandardCoords();
    if(newUnknownStdCoords->estimateFromCoords(sourcePosition)){

        //Update old std coords if necessary and position history
        if(autoBuildUnknownStdCoords){
            if(autoBuildUnknownStdCoords->equals(*newUnknownStdCoords)){
                delete newUnknownStdCoords;
                autoBuildUnknownHistory.append(sourcePosition);
                if(autoBuildUnknownHistory.size() > autoBuildUnknownHistorySize)
                    autoBuildUnknownHistory.removeFirst();
            }
            else{
                delete autoBuildUnknownStdCoords;
                autoBuildUnknownStdCoords = newUnknownStdCoords;
                autoBuildUnknownHistory.clear();
                autoBuildUnknownHistory.append(sourcePosition);
            }
        }
        else{
            autoBuildUnknownStdCoords = newUnknownStdCoords;
            autoBuildUnknownHistory.clear();
            autoBuildUnknownHistory.append(sourcePosition);
        }

        //Build imaginary tile
        HexTile* imaginaryTile = new HexTile(); //No need for screen rendering now, no need for parent
        imaginaryTile->setStandardCoords(autoBuildUnknownStdCoords);

        //This is the first tile ever, assume q,r = 0,0
        if(!autoBuildKnownCoordsExist){

            //If map is empty, we can try to get coordinates
            if(mapEmpty){
                result = (imaginaryTile->sourceCoordinates(sourcePosition) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
                result.setZ(sourcePose.z());
            }

            //Add this tile
            if(mapEmpty && addNewTile && autoBuildUnknownHistory.size() >= autoBuildUnknownHistorySize){
                autoBuildUnknownStdCoords = nullptr; //Detach std coords from the map, rests only with imaginaryTile
                imaginaryTile->setParent(tileMap);
                imaginaryTile->setParentItem(tileMap); //Child added detection will call addTile(), no need to call here
                resetAutoBuild();
            }
            else
                delete imaginaryTile;
        }

        //There are existing tiles
        else{
            QVector<QVector2D> corners;
            autoBuildKnownCoords.cornerList(corners);
            int deltaQ = 0;
            int deltaR = 0;
            static QVector<int> deltaQs = {0,   -1, -1, 0,  1,  1};
            static QVector<int> deltaRs = {-1,  0,  1,  1,  0,  -1};

            if(autoBuildKnownHistory.length() >= 2){

                //Detect raycast exit to estimate unknown coordinates for a short while
                //Order: top-left, left, bottom-left, bottom-right, right, top-right
                QVector2D origin(0,0);
                for(QVector2D const& vec : autoBuildKnownHistory)
                    origin += vec;
                origin /= autoBuildKnownHistory.length();
                QVector2D mainVec = autoBuildKnownHistory.last() - autoBuildKnownHistory.first();
                for(int i=0;i<6;i++)
                    if(CelluloMathUtil::rayCrossesLineSeg(origin, mainVec, corners[i], corners[(i + 1) % 6])){
                        deltaQ = deltaQs[i];
                        deltaR = deltaRs[i];
                        break;
                    }
                imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + deltaQ);
                imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + deltaR);
                result = (imaginaryTile->sourceCoordinates(sourcePosition) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
                result.setZ(sourcePose.z());
            }

            //Enough samples on the known and unknown tiles, pick best direction
            if(addNewTile && autoBuildUnknownHistory.size() >= autoBuildUnknownHistorySize && autoBuildKnownHistory.size() >= autoBuildKnownHistoryMinSize){

                //Directions on the known tile
                QList<QVector2D> knownVecs;
                for(auto it = autoBuildKnownHistory.begin() + 1; it != autoBuildKnownHistory.end(); it++){
                    QVector2D vec = *it - *(it - 1);
                    if(vec.length() > autoBuildMinVecSize)
                        knownVecs.append(vec);
                }

                //Directions on the unknown tile calculated from the raw source coordinates, will result in the same if calculated from remapped coordinates
                QList<QVector2D> unknownVecs;
                for(auto it = autoBuildUnknownHistory.begin() + 1; it != autoBuildUnknownHistory.end(); it++){
                    QVector2D vec = *it - *(it - 1);
                    if(vec.length() > autoBuildMinVecSize)
                        unknownVecs.append(vec);
                }

                float bestScore = std::numeric_limits<float>::infinity();
                deltaQ = 0;
                deltaR = 0;
                for(int i=0;i<6;i++){
                    float hypotDeltaQ = deltaQs[i];
                    float hypotDeltaR = deltaRs[i];
                    imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + hypotDeltaQ);
                    imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + hypotDeltaR);

                    //Passage direction from the known tile to the unknown tile
                    QVector2D fromKnownToUnknownDir =
                        (imaginaryTile->sourceCoordinates(autoBuildUnknownHistory.first()) + imaginaryTile->getCoords()->hexOffset()) - autoBuildKnownHistory.last();

                    //Score is the sum of angles between all direction pairs, minimum score wins
                    //We don't add known-known, known-unknown and unknown-unknown pairs to the score as they are the same in all 6 cases
                    float score = 0;
                    for(auto it = knownVecs.begin(); it != knownVecs.end(); it++)
                        score += CelluloMathUtil::angleBetween(*it, fromKnownToUnknownDir);
                    for(auto it = unknownVecs.begin(); it != unknownVecs.end(); it++)
                        score += CelluloMathUtil::angleBetween(*it, fromKnownToUnknownDir);
                    if(score < bestScore){
                        bestScore = score;
                        deltaQ = hypotDeltaQ;
                        deltaR = hypotDeltaR;
                    }
                }

                //Add tile
                if(deltaQ != 0 || deltaR != 0){
                    imaginaryTile->getCoords()->setQ(autoBuildKnownCoords.getQ() + deltaQ);
                    imaginaryTile->getCoords()->setR(autoBuildKnownCoords.getR() + deltaR);
                    result = (imaginaryTile->sourceCoordinates(sourcePosition) + imaginaryTile->getCoords()->hexOffset()).toVector3D();
                    result.setZ(sourcePose.z());
                    //TODO: TRANSFER UNKNOWN TO KNOWN
                    autoBuildUnknownStdCoords = nullptr; //Detach std coords from the map, rests only with imaginaryTile
                    imaginaryTile->setParent(tileMap);
                    imaginaryTile->setParentItem(tileMap); //Child added detection will call addTile(), no need to call here
                }
                resetAutoBuild();
            }
            else
                delete imaginaryTile;
        }
    }

    //Estimate somehow failed
    else{
        delete newUnknownStdCoords;
        qCritical() << "HexTileMapAutoBuilder::processUnknownTile(): Standard coordinate estimate somehow failed.";
    }

    return result;
}

}
