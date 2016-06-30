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

#include <QPolygon>

#include "../util/CelluloMathUtil.h"

/**
 * CelluloZonePolygon
 */

CelluloZonePolygon::CelluloZonePolygon() : CelluloZone(){
    maxX = std::numeric_limits<qreal>::min();
    maxY = std::numeric_limits<qreal>::min();
    minX = std::numeric_limits<qreal>::max();
    minY = std::numeric_limits<qreal>::max();
}

void CelluloZonePolygon::updateBounds(){
    for(const QVector2D& vertex : vertices){
        if(vertex.x() < minX)
            minX = vertex.x();
        if(vertex.x() > maxX)
            maxX = vertex.x();
        if(vertex.y() < minY)
            minY = vertex.y();
        if(vertex.y() > maxY)
            maxY = vertex.y();
    }
}

void CelluloZonePolygon::setVertices(const QList<QVector2D> &newVertices){
    if(newVertices != vertices){
        vertices = newVertices;
        emit verticesChanged();
        updateBounds();
        updatePaintedItem();
    }
}

void CelluloZonePolygon::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    Q_UNUSED(color);
    Q_UNUSED(canvasWidth);
    Q_UNUSED(canvasHeight);
    Q_UNUSED(physicalWidth);
    Q_UNUSED(physicalHeight);
    painter->setRenderHint(QPainter::Antialiasing);
}

/**
 * CelluloZoneIrregularPolygon
 */

void CelluloZoneIrregularPolygon::write(QJsonObject& json){
    CelluloZone::write(json);

    QJsonArray verticesArray;
    for(const QVector2D& vertex : vertices){
        QJsonObject vertexObj;
        vertexObj["x"] = vertex.x();
        vertexObj["y"] = vertex.y();
        verticesArray.append(vertexObj);
    }
    json["vertices"] = verticesArray;
}

void CelluloZoneIrregularPolygon::read(const QJsonObject &json){
    CelluloZone::read(json);

    QList<QVector2D> newVertices;
    QJsonArray verticesArray = json["vertices"].toArray();
    for(const QJsonValue& vertexValue : verticesArray){
        const QJsonObject& vertexObj = vertexValue.toObject();
        newVertices.append(QVector2D(vertexObj["x"].toDouble(), vertexObj["y"].toDouble()));
    }
    setVertices(newVertices);
}

void CelluloZoneIrregularPolygon::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);
}

/**
 * CelluloZoneIrregularPolygonInner
 */

CelluloZoneIrregularPolygonInner::CelluloZoneIrregularPolygonInner() : CelluloZoneIrregularPolygon(){
    type = CelluloZoneTypes::IRPOLYGONINNER;
}

float CelluloZoneIrregularPolygonInner::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);

    if(minX <= xRobot && xRobot <= maxX && minY <= yRobot && yRobot <= maxY)
        return CelluloMathUtil::pointInPoly(QVector2D(xRobot, yRobot), vertices) ? 1 : 0;
    else
        return 0;
}

void CelluloZoneIrregularPolygonInner::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneIrregularPolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(QBrush(color));
    painter->setPen(Qt::NoPen);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    QPolygonF poly;
    for(const QVector2D& vertex : vertices)
        poly.append(QPointF(vertex.x()*horizontalScaleCoeff, vertex.y()*verticalScaleCoeff));

    painter->drawPolygon(poly);
}

/**
 * CelluloZoneIrregularPolygonBorder
 */

CelluloZoneIrregularPolygonBorder::CelluloZoneIrregularPolygonBorder() : CelluloZoneIrregularPolygon(){
    type = CelluloZoneTypes::IRPOLYGONBORDER;
}

void CelluloZoneIrregularPolygonBorder::setBorderThickness(qreal newThickness){
    if(borderThickness != newThickness){
        borderThickness = newThickness;
        emit borderThicknessChanged();
        updatePaintedItem();
    }
}

void CelluloZoneIrregularPolygonBorder::write(QJsonObject &json){
    CelluloZoneIrregularPolygon::write(json);

    json["borderThickness"] = borderThickness;
}

void CelluloZoneIrregularPolygonBorder::read(const QJsonObject &json){
    CelluloZoneIrregularPolygon::read(json);

    borderThickness = json["borderThickness"].toDouble();
}

float CelluloZoneIrregularPolygonBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    return CelluloMathUtil::pointToPolyBorderDist(QVector2D(xRobot, yRobot), vertices) <= borderThickness/2 ? 1 : 0;
}

void CelluloZoneIrregularPolygonBorder::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneIrregularPolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QBrush(color), borderThickness*(horizontalScaleCoeff + verticalScaleCoeff)/2));

    QPolygonF poly;
    for(const QVector2D& vertex : vertices)
        poly.append(QPointF(vertex.x()*horizontalScaleCoeff, vertex.y()*verticalScaleCoeff));

    painter->drawPolygon(poly);
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
    Q_UNUSED(thetaRobot);
    //return getPointToPolygonDistance(xRobot, yRobot);
    return 0;
}

void CelluloZoneIrregularPolygonDistance::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneIrregularPolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);
















}

/**
 * CelluloZoneRegularPolygon
 */

CelluloZoneRegularPolygon::CelluloZoneRegularPolygon() : CelluloZonePolygon(){
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
        //setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::setX(float newX) {
    if(newX != x){
        x = newX;
        emit(xChanged());
        //setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::setY(float newY) {
    if(newY != y){
        y = newY;
        emit(yChanged());
        //setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::setR(float newR) {
    if(newR != r){
        r = newR;
        emit(rChanged());
        //setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::setRotAngle(float newRotAngle) {
    if(newRotAngle != rotAngle){
        rotAngle = newRotAngle;
        emit(rotAngleChanged());
        //setPointsQt(createPolygonPointsFromOuterCircle());
        updatePaintedItem();
    }
}

void CelluloZoneRegularPolygon::write(QJsonObject &json){
    json["numEdges"] = numEdges;
    json["x"] = x;
    json["y"] = y;
    json["r"] = r;
    json["rotAngle"] = rotAngle;
}

void CelluloZoneRegularPolygon::read(const QJsonObject &json){
    numEdges = json["numEdges"].toDouble();
    x = json["x"].toDouble();
    y = json["y"].toDouble();
    r = json["r"].toDouble();
    rotAngle = json["rotAngle"].toDouble();






    //setPointsQt(createPolygonPointsFromOuterCircle());
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

void CelluloZoneRegularPolygon::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZonePolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);












}

/**
 * CelluloZoneRegularPolygonInner
 */

CelluloZoneRegularPolygonInner::CelluloZoneRegularPolygonInner() : CelluloZoneRegularPolygon(){
    type = CelluloZoneTypes::RPOLYGONINNER;
}

float CelluloZoneRegularPolygonInner::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    //return pointInPoly(xRobot, yRobot, x-r, x+r, y-r, y+r, pointsQt);
    return 0;
}

void CelluloZoneRegularPolygonInner::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneRegularPolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);

    painter->setBrush(QBrush(color));
    painter->setPen(Qt::NoPen);

    qreal horizontalScaleCoeff = canvasWidth/physicalWidth;
    qreal verticalScaleCoeff = canvasHeight/physicalHeight;

    QPolygonF poly;
    for(const QVector2D& vertex : vertices)
        poly.append(QPointF(vertex.x()*horizontalScaleCoeff, vertex.y()*verticalScaleCoeff));

    painter->drawPolygon(poly);
}

/**
 * CelluloZoneRegularPolygonBorder
 */

CelluloZoneRegularPolygonBorder::CelluloZoneRegularPolygonBorder() : CelluloZoneRegularPolygon(){
    type = CelluloZoneTypes::RPOLYGONBORDER;
}

float CelluloZoneRegularPolygonBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    //return isPointOnPolygonBorder(xRobot, yRobot);
    return 0;
}

void CelluloZoneRegularPolygonBorder::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneRegularPolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);








}

/**
 * CelluloZoneRegularPolygonDistance
 */

CelluloZoneRegularPolygonDistance::CelluloZoneRegularPolygonDistance() : CelluloZoneRegularPolygon(){
    type = CelluloZoneTypes::RPOLYGONDISTANCE;
}

float CelluloZoneRegularPolygonDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    Q_UNUSED(thetaRobot);
    //return getPointToPolygonDistance(xRobot, yRobot);
    return 0;
}

void CelluloZoneRegularPolygonDistance::paint(QPainter* painter, QColor color, qreal canvasWidth, qreal canvasHeight, qreal physicalWidth, qreal physicalHeight){
    CelluloZoneRegularPolygon::paint(painter, color, canvasWidth, canvasHeight, physicalWidth, physicalHeight);








}
