#include "CelluloZoneLine.h"

CelluloZoneLine::CelluloZoneLine() :
    CelluloZone()
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
}

QVariantMap CelluloZoneLine::getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight){
    QVariantMap properties;
    properties["name"] = QVariant(name);
    properties["stackingOrder"] = QVariant(stackingOrder);
    properties["marginThickeness"] = QVariant(marginThickeness/realPlaygroundWidth);
    properties["x1"] = QVariant(x1/realPlaygroundWidth);
    properties["y1"] = QVariant(y1/realPlaygroundHeight);
    properties["x2"] = QVariant(x2/realPlaygroundWidth);
    properties["y2"] = QVariant(y2/realPlaygroundHeight);
    return properties;
}

void CelluloZoneLine::write(QJsonObject &json){
    json["type"] = CelluloZoneTypes::typeToString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
    json["x1"] = x1;
    json["y1"] = y1;
    json["x2"] = x2;
    json["y2"] = y2;
}

void CelluloZoneLine::read(const QJsonObject &json){
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
    x1 = json["x1"].toDouble();
    y1 = json["y1"].toDouble();
    x2 = json["x2"].toDouble();
    y2 = json["y2"].toDouble();
}

CelluloZoneLineInner::CelluloZoneLineInner() :
    CelluloZoneLine()
{
    type = CelluloZoneTypes::LINEINNER;
}


float CelluloZoneLineInner::calculate(float xRobot, float yRobot, float thetaRobot){
    float distancePointToLine = pointToSegmentDistance(xRobot, yRobot, x1, y1, x2, y2);
    return distancePointToLine==0? 1:0;
}

CelluloZoneLineDistance::CelluloZoneLineDistance() :
    CelluloZoneLine()
{
    type = CelluloZoneTypes::LINEDISTANCE;
}

float CelluloZoneLineDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    return pointToSegmentDistance(xRobot, yRobot, x1, y1, x2, y2);
}
