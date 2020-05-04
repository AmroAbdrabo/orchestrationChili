#include "hexagon.h"

#include <QPainterPath>
#include <QSGGeometryNode>
#include <qsgflatcolormaterial.h>
#include <QPainter>
#include <math.h>

#define PI 3.14159265

Hexagon::Hexagon(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_color(Qt::red),
    m_needUpdate(true)
{
    setFlag(QQuickItem::ItemHasContents);
}

void Hexagon::paint(QPainter *painter)
{

    float r = PI/180;
    //float tan60 = tan(60*r);
    float cos60 = cos(60*r);
    //float cos30 = cos(30*r);
    //float sin30 = sin(30*r);
    //float sin60 = sin(60*r);
    //float sin120 = sin(120*r);
    float cos120 = cos(120*r);
    /*float sin240 = sin(240*r);
    float cos240 = cos(240*r);
    float sin300 = sin(300*r);
    float cos300 = cos(300*r);*/
    float a = width()/2;
    float h = a;
    //float v = a*sin60;
    float v = height()/2;
    QPainterPath path;

    //commented we have the code for the hexagon to always be perfect hexagon
    //using 'a' (i.e width/2) as the distance from the center to a vertices

    /*path.moveTo(width(), 0+v); //A
    path.lineTo(a*cos60+h, a*sin60+v); // B
    path.lineTo(a*cos120+h, a*sin120+v); // C
    path.lineTo(-a+h, v); //D
    path.lineTo(a*cos240+h, a*sin240+v);//E
    path.lineTo(a*cos300+h, a*sin300+v);//f
    path.lineTo(a+h, +v);//A*/

    //the current hexagon path is not forced to always be a perfect hexagon, and can accurately morph with given height and width
    //(For a perfect hexagon the height is determined by the width(or vice-versa) but here u can choose the height and width of the hexagon)
    path.moveTo(width(), 0+v); //A
    path.lineTo(a*cos60+h, height()/2+v); // B
    path.lineTo(a*cos120+h, height()/2+v); // C
    path.lineTo(-a+h, v); //D
    path.lineTo(a*cos120+h, -height()/2+v);//E
    path.lineTo(a*cos60+h, -height()/2+v);//f
    path.lineTo(a+h, +v);//A

    painter->fillPath(path, m_color);
}

QColor Hexagon::color() const
{
    return m_color;
}

void Hexagon::setColor(const QColor &color)
{
    if(m_color != color) {
        m_color = color;
        m_needUpdate = true;
        update();
        colorChanged();
    }
}

