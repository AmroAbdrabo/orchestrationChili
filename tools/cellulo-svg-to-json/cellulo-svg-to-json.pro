TEMPLATE = app

QT += core

SOURCES += \
    src/main.cpp \
    ../../src/util/svg/CelluloSVGUtil.cpp

HEADERS += \
    ../../src/util/svg/CelluloSVGUtil.h

INCLUDEPATH += ../../src/util/svg/

unix{
    target.path = /usr/local/bin/
    INSTALLS += target
}
