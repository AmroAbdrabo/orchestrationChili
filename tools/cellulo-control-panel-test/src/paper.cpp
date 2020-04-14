#include "paper.h"

Paper::Paper(QObject *parent) : QObject(parent)
{
    m_width = 500;
    m_height = 500;
}

void Paper::setHeight(float width) {
    m_height = width;
    emit heightChanged();
}

void Paper::setWidth(float width) {
    m_width = width;
    emit widthChanged();
}

float Paper::width() {
    return m_width;
}
float Paper::height() {
    return m_height;
}

