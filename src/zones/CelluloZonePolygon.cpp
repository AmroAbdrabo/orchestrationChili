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
            result = pointInPoly(xPoint, yPoint, minX, maxX, minY, maxY, getRectangleFromLine(pointsQt.at(i%pointsQt.length()).x(),pointsQt.at(i%pointsQt.length()).y(),pointsQt.at((i+1)%pointsQt.length()).x(),pointsQt.at((i+1)%pointsQt.length()).y(),marginThickeness/2));
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

/**
 * CelluloZoneIrregularPolygon
 */

QVariantMap CelluloZoneIrregularPolygon::getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight){
    QVariantMap properties;
    properties["name"] = QVariant(name);
    properties["stackingOrder"] = QVariant(stackingOrder);
    properties["marginThickeness"] = QVariant(marginThickeness/realPlaygroundWidth);
    QList<QVariant> ratioVertices;
    foreach(QPointF point, convertQVariantToQPointF()) {
        QPointF ratioPoint = QPointF(point.x()/realPlaygroundWidth, point.y()/realPlaygroundHeight);
        ratioVertices.append(QVariant(ratioPoint));
    }
    properties["vertices"] = ratioVertices;
    return properties;
}

void CelluloZoneIrregularPolygon::write(QJsonObject &json){
    json["type"] = CelluloZoneTypes::ZoneTypeString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
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
    vertices.clear();
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
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
 * CelluloZoneRegularPolygon
 */

CelluloZoneRegularPolygon::CelluloZoneRegularPolygon() :
    CelluloZonePolygon()
{
    x = 0;
    y = 0;
    r = 0;
    numEdges = 0;
    rotAngle = 0;
}

QVariantMap CelluloZoneRegularPolygon::getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight){
    QVariantMap properties;
    properties["name"] = QVariant(name);
    properties["stackingOrder"] = QVariant(stackingOrder);
    properties["marginThickeness"] = QVariant(marginThickeness/realPlaygroundWidth);
    properties["numEdges"] = QVariant(numEdges);
    properties["x"] = QVariant(x/realPlaygroundHeight);
    properties["y"] = QVariant(y/realPlaygroundWidth);
    properties["r"] = QVariant((r*r)/(realPlaygroundWidth*realPlaygroundHeight));
    properties["rotAngle"] = QVariant(rotAngle);
    QList<QVariant> ratioVertices;
    foreach(QPointF point, pointsQt) {
        QPointF ratioPoint = QPointF(point.x()/realPlaygroundWidth, point.y()/realPlaygroundHeight);
        ratioVertices.append(QVariant(ratioPoint));
    }
    properties["vertices"] = ratioVertices;
    return properties;
}

void CelluloZoneRegularPolygon::write(QJsonObject &json){
    json["type"] = CelluloZoneTypes::ZoneTypeString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
    json["numEdges"] = numEdges;
    json["x"] = x;
    json["y"] = y;
    json["r"] = r;
    json["rotAngle"] = rotAngle;
}

void CelluloZoneRegularPolygon::read(const QJsonObject &json){
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
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

void CelluloZoneIrregularPolygonInner::paint(QPainter* painter, qreal width, qreal height){

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

void CelluloZoneIrregularPolygonBorder::paint(QPainter* painter, qreal width, qreal height){

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

void CelluloZoneIrregularPolygonDistance::paint(QPainter* painter, qreal width, qreal height){

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

void CelluloZoneRegularPolygonInner::paint(QPainter* painter, qreal width, qreal height){

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

void CelluloZoneRegularPolygonBorder::paint(QPainter* painter, qreal width, qreal height){

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

void CelluloZoneRegularPolygonDistance::paint(QPainter* painter, qreal width, qreal height){

}
