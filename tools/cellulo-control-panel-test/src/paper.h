#ifndef PAPER_H
#define PAPER_H

#include <QObject>

class Paper : public QObject {
    Q_OBJECT  //to use signals and slots
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
public:
    explicit Paper(QObject *parent = nullptr);

    float width();
    float height();

    void setWidth(float width);
    void setHeight(float height);

signals:
    void widthChanged();
    void heightChanged();
private:
    float m_width;
    float m_height;
};


#endif // PAPER_H
