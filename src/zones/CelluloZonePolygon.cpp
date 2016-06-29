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
 * @file CelluloZonePolygon.cpp
 * @brief Source for the polygon zone
 * @author Joanna Salathé
 * @date 2016-03-04
 */

#include "CelluloZonePolygon.h"

/**
 * CelluloZonePolygon
 */

CelluloZonePolygon::CelluloZonePolygon() :
    CelluloZone()
{
    maxX = std::numeric_limits<qreal>::min();
    maxY = std::numeric_limits<qreal>::min();
    minX = std::numeric_limits<qreal>::max();
    minY = std::numeric_limits<qreal>::max();
}

void CelluloZonePolygon::setMaxMinOuterRectangle(const QList<QPointF> &pointsQt, float *minX, float *maxX, float *minY, float *maxY){
    for(int i = 0; i < pointsQt.size(); ++i){
        if(pointsQt.at(i).x() < *minX){
            *minX = pointsQt.at(i).x();
        }
        if(pointsQt.at(i).x() > *maxX){
            *maxX = pointsQt.at(i).x();
        }
        if(pointsQt.at(i).y() < *minY){
            *minY = pointsQt.at(i).y();
        }
        if(pointsQt.at(i).y() > *maxY){
            *maxY = pointsQt.at(i).y();
        }
    }
}

void CelluloZonePolygon::setPointsQt(const QList<QPointF> &newPointsQt){
    if(newPointsQt!=pointsQt){
        pointsQt = newPointsQt;
        setMaxMinOuterRectangle(pointsQt, &minX, &maxX, &minY, &maxY);
    }
}

float CelluloZonePolygon::isPointOnPolygonBorder(float xPoint, float yPoint){
    if(!(xPoint>maxX || xPoint<minX || yPoint>maxY || yPoint<minY)){
        float result = 0;
        for(int i = 0; i < pointsQt.length(); ++i){
            //result = pointInPoly(xPoint, yPoint, minX, maxX, minY, maxY, getRectangleFromLine(pointsQt.at(i%pointsQt.length()).x(),pointsQt.at(i%pointsQt.length()).y(),pointsQt.at((i+1)%pointsQt.length()).x(),pointsQt.at((i+1)%pointsQt.length()).y(),marginThickeness/2));
            //
            //TODO: GET MARGIN THICKNESS IN HERE
            if(result == 1){
                return 1;
            }
        }
        return 0;
    }
    else{
        return 0;
    }
}

float CelluloZonePolygon::getPointToPolygonDistance(float xPoint, float yPoint){
    float distances [pointsQt.length()];
    for(int i = 0; i < pointsQt.length(); ++i){
        distances[i] = pointToSegmentDistance(xPoint, yPoint, pointsQt.at(i%pointsQt.length()).x(),pointsQt.at(i%pointsQt.length()).y(),pointsQt.at((i+1)%pointsQt.length()).x(),pointsQt.at((i+1)%pointsQt.length()).y());
    }
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < pointsQt.length(); i++){
        if( distances[i] < min ){
            min = distances[i];
        }
    }
    return min;
}

void CelluloZonePolygon::paint(QPainter* painter, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){

}

/**
 * CelluloZoneIrregularPolygon
 */

 void CelluloZoneIrregularPolygon::setVertices(QList<QVariant> newPoints) {
     if(newPoints != vertices){
         vertices = newPoints;
         emit(verticesChanged());
         setPointsQt(convertQVariantToQPointF());
         updatePaintedItem();
     }
 }

void CelluloZoneIrregularPolygon::write(QJsonObject &json){
    CelluloZone::write(json);

    QJsonObject obj;
    QJsonArray verticesArray;
    foreach(QPointF point, convertQVariantToQPointF()) {
        QJsonObject pointObject;
        pointObject["x"] = point.x();
        pointObject["y"] = point.y();
        verticesArray.append(pointObject);
    }
    json["vertices"] = verticesArray;
}

void CelluloZoneIrregularPolygon::read(const QJsonObject &json){
    CelluloZone::read(json);

    vertices.clear();
    QJsonArray verticesArray = json["vertices"].toArray();
    foreach(QVariant pointObject, verticesArray.toVariantList()) {
        QMap<QString, QVariant> pointMap = pointObject.toMap();
        QPointF point;
        point.setX(pointMap["x"].toDouble());
        point.setY(pointMap["y"].toDouble());
        vertices.append(point);
    }
    setPointsQt(convertQVariantToQPointF());
}

QList<QPointF> CelluloZoneIrregularPolygon::convertQVariantToQPointF(){
    QList<QPointF> newPointsQt;
    for(int i = 0; i < vertices.size(); ++i){
        if(vertices.at(i).canConvert(QVariant::PointF)){
            if(QVariant(vertices.at(i)).convert(QVariant::PointF)){
                QPointF newPoint = vertices.at(i).toPointF();
                newPointsQt.append(newPoint);
            } else{
                qDebug() << "Problem with convert() at index " << i;
            }
        }else {
            qDebug() << "Problem with canConvert() at index " << i;
        }
    }
    return newPointsQt;
}

/**
 * CelluloZoneIrregularPolygonInner
 */

CelluloZoneIrregularPolygonInner::CelluloZoneIrregularPolygonInner() :
    CelluloZoneIrregularPolygon()
{
    type = CelluloZoneTypes::IRPOLYGONINNER;
}

float CelluloZoneIrregularPolygonInner::calculate(float xRobot, float yRobot, float thetaRobot){
    return pointInPoly(xRobot, yRobot, minX, maxX, minY, maxY, pointsQt);
}

/**
 * CelluloZoneIrregularPolygonBorder
 */

CelluloZoneIrregularPolygonBorder::CelluloZoneIrregularPolygonBorder() :
    CelluloZoneIrregularPolygon()
{
    type = CelluloZoneTypes::IRPOLYGONBORDER;
}

float CelluloZoneIrregularPolygonBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    return isPointOnPolygonBorder(xRobot, yRobot);
}

/**
 * CelluloZoneIrregularPolygonDistance
 */

CelluloZoneIrregularPolygonDistance::CelluloZoneIrregularPolygonDistance() :
    CelluloZoneIrregularPolygon()
{
    type = CelluloZoneTypes::IRPOLYGONDISTANCE;
}

float CelluloZoneIrregularPolygonDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    return getPointToPolygonDistance(xRobot, yRobot);
}

/**
 * CelluloZoneRegularPolygon
 */

CelluloZoneRegularPolygon::CelluloZoneRegularPolygon() :
    CelluloZonePolygon()
{
    x = 0;
    y = 0;
    r = 0;
    numEdges = 3;
    rotAngle = 0;
}

void CelluloZoneRegularPolygon::setNumEdges(int newNumEdge) {
    if(newNumEdge > 2 && newNumEdge != numEdges){
        numEdges = newNumEdge;
        emit(numEdgesChanged());
        setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

QList<QVariant> CelluloZoneRegularPolygon::getVertices() {
    QList<QVariant> newVertices;
    for(int i = 0; i < pointsQt.size(); ++i)
        newVertices.append(QVariant::fromValue(pointsQt.at(i)));
    return newVertices;
}

void CelluloZoneRegularPolygon::setX(float newX) {
    if(newX != x){
        x = newX;
        emit(xChanged());
        setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::setY(float newY) {
    if(newY != y){
        y = newY;
        emit(yChanged());
        setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::setR(float newR) {
    if(newR != r){
        r = newR;
        emit(rChanged());
        setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::setRotAngle(float newRotAngle) {
    if(newRotAngle != rotAngle){
        rotAngle = newRotAngle;
        emit(rotAngleChanged());
        setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::write(QJsonObject &json){
    CelluloZonePolygon::write(json);

    json["numEdges"] = numEdges;
    json["x"] = x;
    json["y"] = y;
    json["r"] = r;
    json["rotAngle"] = rotAngle;
}

void CelluloZoneRegularPolygon::read(const QJsonObject &json){
    CelluloZonePolygon::read(json);

    numEdges = json["numEdges"].toDouble();
    x = json["x"].toDouble();
    y = json["y"].toDouble();
    r = json["r"].toDouble();
    rotAngle = json["rotAngle"].toDouble();
    setPointsQt(createPolygonPointsFromOuterCircle());
}

QList<QPointF> CelluloZoneRegularPolygon::createPolygonPointsFromOuterCircle(){
    QList<QPointF> newPointsQt;
    float rotAngleRadian = rotAngle * (M_PI/180);
    if(numEdges>2){
        for(int i = 0; i < numEdges; i++){
            //taken from: http://stackoverflow.com/questions/3436453/calculate-coordinates-of-a-regular-polygons-vertices
            QPointF newPoint = QPointF(x + r * cos(2 * M_PI * i / numEdges + rotAngleRadian), y + r * sin(2 * M_PI * i / numEdges + rotAngleRadian));
            newPointsQt.append(newPoint);
        }
    } else {
        qDebug() << "n must be >2";
    }
    return newPointsQt;
}

/**
 * CelluloZoneRegularPolygonInner
 */

CelluloZoneRegularPolygonInner::CelluloZoneRegularPolygonInner() :
    CelluloZoneRegularPolygon()
{
    type = CelluloZoneTypes::RPOLYGONINNER;
}

float CelluloZoneRegularPolygonInner::calculate(float xRobot, float yRobot, float thetaRobot){
    return pointInPoly(xRobot, yRobot, x-r, x+r, y-r, y+r, pointsQt);
}

/**
 * CelluloZoneRegularPolygonBorder
 */

CelluloZoneRegularPolygonBorder::CelluloZoneRegularPolygonBorder() :
    CelluloZoneRegularPolygon()
{
    type = CelluloZoneTypes::RPOLYGONBORDER;
}

float CelluloZoneRegularPolygonBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    return isPointOnPolygonBorder(xRobot, yRobot);
}

/**
 * CelluloZoneRegularPolygonDistance
 */

CelluloZoneRegularPolygonDistance::CelluloZoneRegularPolygonDistance() :
    CelluloZoneRegularPolygon()
{
    type = CelluloZoneTypes::RPOLYGONDISTANCE;
}

float CelluloZoneRegularPolygonDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    return getPointToPolygonDistance(xRobot, yRobot);
}
