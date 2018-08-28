TEMPLATE = app

TARGET = cellulorobothubd

QT += core bluetooth quick

SOURCES += src/main.cpp

INCLUDEPATH += \
    ../../../src/comm/ \
    ../../../src/comm/relay/ \
    ../../../include/

LIBS += -L$$[QT_INSTALL_QML]/Cellulo/ -lcelluloplugin
QMAKE_RPATHDIR += $$[QT_INSTALL_QML]/Cellulo/

target.path = /usr/local/bin/
INSTALLS += target
