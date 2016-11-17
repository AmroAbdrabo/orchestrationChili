TEMPLATE = app

QT += core qml quick bluetooth

SOURCES += \
    src/main.cpp \
    ../../src/util/svg/CelluloSVGUtil.cpp

HEADERS += \
    ../../src/util/svg/CelluloSVGUtil.h

INCLUDEPATH += \
    ../../src/util/svg/ \
    ../../include/

LIBS += -L$$[QT_INSTALL_QML]/Cellulo/ -lcelluloplugin
QMAKE_RPATHDIR += $$[QT_INSTALL_QML]/Cellulo/

unix{
    target.path = /usr/local/bin/
    INSTALLS += target
}
