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
service.files = scripts/cellulorobothubd.service
service.path = /lib/systemd/system/
servicestartup.depends = service
servicestartup.extra = systemctl daemon-reload; systemctl enable cellulorobothubd.service
INSTALLS += target service servicestartup
