#ifndef HEXAGON_H
#define HEXAGON_H

#include <QQuickPaintedItem>


class Hexagon : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    Hexagon(QQuickItem *parent = Q_NULLPTR);

protected:
    void paint(QPainter *painter);

    QColor color() const;
    void setColor(const QColor &color);

private:
    QColor m_color;
    bool m_needUpdate;

signals:
    void colorChanged();
};
#endif // HEXAGON_H

