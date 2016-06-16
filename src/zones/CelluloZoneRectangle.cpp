#include "CelluloZoneRectangle.h"

CelluloZoneRectangle::CelluloZoneRectangle() :
    CelluloZone()
{
    x = 0;
    y = 0;
    height = 0;
    width = 0;
}

QVariantMap CelluloZoneRectangle::getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight){
    QVariantMap properties;
    properties["name"] = QVariant(name);
    properties["stackingOrder"] = QVariant(stackingOrder);
    properties["marginThickeness"] = QVariant(marginThickeness/realPlaygroundWidth);
    properties["x"] = QVariant(x/realPlaygroundWidth);
    properties["y"] = QVariant(y/realPlaygroundHeight);
    properties["width"] = QVariant(width/realPlaygroundWidth);
    properties["height"] = QVariant(height/realPlaygroundHeight);
    return properties;

}

void CelluloZoneRectangle::write(QJsonObject &json){
    json["type"] = CelluloZoneTypes::typeToString(type);
    json["name"] = name;
    json["stackingOrder"] = stackingOrder;
    json["marginThickeness"] = marginThickeness;
    json["x"] = x;
    json["y"] = y;
    json["width"] = width;
    json["height"] = height;
}

void CelluloZoneRectangle::read(const QJsonObject &json){
    type = CelluloZoneTypes::typeFromString(json["type"].toString());
    name = json["name"].toString();
    stackingOrder= json["stackingOrder"].toInt();
    marginThickeness = json["marginThickeness"].toDouble();
    x = json["x"].toDouble();
    y = json["y"].toDouble();
    width = json["width"].toDouble();
    height = json["height"].toDouble();
}

CelluloZoneRectangleInner::CelluloZoneRectangleInner() :
    CelluloZoneRectangle()
{
    type = CelluloZoneTypes::RECTANGLEINNER;
}

float CelluloZoneRectangleInner::calculate(float xRobot, float yRobot, float thetaRobot){
    return x <= xRobot && x + width >= xRobot && y <= yRobot && y + height >= yRobot? 1 : 0;
}

CelluloZoneRectangleBorder::CelluloZoneRectangleBorder() :
    CelluloZoneRectangle()
{
    type = CelluloZoneTypes::RECTANGLEBORDER;
}

float CelluloZoneRectangleBorder::calculate(float xRobot, float yRobot, float thetaRobot){
    return ((((x - (marginThickeness/2)) <= xRobot && (x + width + (marginThickeness/2)) >= xRobot && (y - (marginThickeness/2)) <= yRobot && (y + height + (marginThickeness/2)) >= yRobot) == 1) &&
            (((x + (marginThickeness/2)) <= xRobot && (x + width - (marginThickeness/2)) >= xRobot && (y + (marginThickeness/2)) <= yRobot && (y + height - (marginThickeness/2)) >= yRobot) == 0));
}

CelluloZoneRectangleDistance::CelluloZoneRectangleDistance() :
    CelluloZoneRectangle()
{
    type = CelluloZoneTypes::RECTANGLEDISTANCE;
}

float CelluloZoneRectangleDistance::calculate(float xRobot, float yRobot, float thetaRobot){
    float distances [4] = { pointToSegmentDistance(xRobot, yRobot, x,y,width+x,y),
                            pointToSegmentDistance(xRobot, yRobot, width+x,y,width+x,height+y),
                            pointToSegmentDistance(xRobot, yRobot, width+x,height+y,x,height+y),
                            pointToSegmentDistance(xRobot, yRobot, x,height+y,x,y)};

    float min = std::numeric_limits<float>::max();
    for ( int i = 0; i < 4; i++ ){
        if ( distances[i] < min ){
            min = distances[i];
        }
    }

    return min;
}
