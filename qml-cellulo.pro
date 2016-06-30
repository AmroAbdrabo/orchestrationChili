QT += qml quick bluetooth

CONFIG += qt plugin c++11 nostrip

HEADERS += \
    src/CelluloPlugin.h \
    src/comm/CelluloBluetooth.h \
    src/comm/CelluloBluetoothEnums.h \
    src/comm/CameraFrameImageProvider.h \
    src/comm/CelluloBluetoothPacket.h \
    src/zones/CelluloZoneClient.h \
    src/zones/CelluloZonePoint.h \
    src/zones/CelluloZoneLine.h \
    src/zones/CelluloZoneCircle.h \
    src/zones/CelluloZonePolygon.h \
    src/zones/CelluloZone.h \
    src/zones/CelluloZoneRectangle.h \
    src/zones/CelluloZoneEngine.h \
    src/zones/CelluloZoneJsonHandler.h \
    src/zones/CelluloZoneTypes.h \
    src/zones/CelluloZonePaintedItem.h \
    src/util/CelluloMathUtil.h

SOURCES += \
    src/CelluloPlugin.cpp \
    src/comm/CelluloBluetooth.cpp \
    src/comm/CelluloBluetoothEnums.cpp \
    src/comm/CameraFrameImageProvider.cpp \
    src/comm/CelluloBluetoothPacket.cpp \
    src/zones/CelluloZoneClient.cpp \
    src/zones/CelluloZonePoint.cpp \
    src/zones/CelluloZoneLine.cpp \
    src/zones/CelluloZoneCircle.cpp \
    src/zones/CelluloZonePolygon.cpp \
    src/zones/CelluloZone.cpp \
    src/zones/CelluloZoneRectangle.cpp \
    src/zones/CelluloZoneEngine.cpp \
    src/zones/CelluloZoneJsonHandler.cpp \
    src/zones/CelluloZoneTypes.cpp \
    src/zones/CelluloZonePaintedItem.cpp \
    src/util/CelluloMathUtil.cpp

INCLUDEPATH += \
    include/

test{
    message(Configuring test build...)

    TEMPLATE = app
    TARGET = celluloplugintests

    QT += testlib

    HEADERS += \
        test/TestCelluloBluetoothPacket.h

    SOURCES += \
        test/TestCelluloBluetoothPacket.cpp
}
else{
    TEMPLATE = lib
    TARGET = celluloplugin

    CONFIG += plugin
    CONFIG -= android_install

    TARGET = $$qtLibraryTarget($$TARGET)
    uri = Cellulo

    #File installation

    qmldir.files = qmldir
    javascript.files = src/cellulo-toolkit.js \
    src/zones/cellulo-zonesdrawer.js
    qml.files = src/CelluloRobot.qml src/comm/MacAddrSelector.qml

    OTHER_FILES += qmldir.files javascript.files qml.files

    unix {
        installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
        qmldir.path = $$installPath
        javascript.path = $$installPath
        qml.path = $$installPath
        target.path = $$installPath
        INSTALLS += target qmldir javascript qml
    }
}
