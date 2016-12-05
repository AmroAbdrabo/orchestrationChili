QT += qml quick bluetooth

CONFIG += qt plugin c++11 nostrip

linux:!android {
    CONFIG += link_pkgconfig

    packagesExist(bluez){
        PKGCONFIG += bluez
        DEFINES += BT_MULTIADAPTER_SUPPORT
        message("BlueZ found, enabling Bluetooth multiadapter support.")
    }
    else{
        message("BlueZ not found, disabling Bluetooth multiadapter support.")
    }
}

HEADERS += \
    src/CelluloPlugin.h \
    src/comm/CelluloBluetooth.h \
    src/comm/CelluloBluetoothRelayServer.h \
    src/comm/CelluloBluetoothRelayClient.h \
    src/comm/CelluloBluetoothEMP.h \
    src/comm/CelluloBluetoothEnums.h \
    src/comm/CameraFrameImageProvider.h \
    src/comm/CelluloBluetoothPacket.h \
    src/zones/CelluloZoneClient.h \
    src/zones/CelluloZonePoint.h \
    src/zones/CelluloZoneLine.h \
    src/zones/CelluloZoneCircle.h \
    src/zones/CelluloZonePolygon.h \
    src/zones/CelluloZonePolyBezier.h \
    src/zones/CelluloZone.h \
    src/zones/CelluloZoneRectangle.h \
    src/zones/CelluloZoneAngle.h \
    src/zones/CelluloZoneAngleInterval.h \
    src/zones/CelluloZoneEngine.h \
    src/zones/CelluloZoneJsonHandler.h \
    src/zones/CelluloZoneTypes.h \
    src/zones/CelluloZonePaintedItem.h \
    src/util/math/CelluloMathUtil.h \
    src/util/math/CubicBezier.h \
    src/util/svg/CelluloSVGUtil.h \
    src/util/lang/TranslationTool.h

SOURCES += \
    src/CelluloPlugin.cpp \
    src/comm/CelluloBluetooth.cpp \
    src/comm/CelluloBluetoothRelayServer.cpp \
    src/comm/CelluloBluetoothRelayClient.cpp \
    src/comm/CelluloBluetoothEMP.cpp \
    src/comm/CelluloBluetoothEnums.cpp \
    src/comm/CameraFrameImageProvider.cpp \
    src/comm/CelluloBluetoothPacket.cpp \
    src/zones/CelluloZoneClient.cpp \
    src/zones/CelluloZonePoint.cpp \
    src/zones/CelluloZoneLine.cpp \
    src/zones/CelluloZoneCircle.cpp \
    src/zones/CelluloZonePolygon.cpp \
    src/zones/CelluloZonePolyBezier.cpp \
    src/zones/CelluloZone.cpp \
    src/zones/CelluloZoneRectangle.cpp \
    src/zones/CelluloZoneAngle.cpp \
    src/zones/CelluloZoneAngleInterval.cpp \
    src/zones/CelluloZoneEngine.cpp \
    src/zones/CelluloZoneJsonHandler.cpp \
    src/zones/CelluloZoneTypes.cpp \
    src/zones/CelluloZonePaintedItem.cpp \
    src/util/math/CelluloMathUtil.cpp \
    src/util/math/CubicBezier.cpp \
    src/util/svg/CelluloSVGUtil.cpp \
    src/util/lang/TranslationTool.cpp

INCLUDEPATH += \
    include/

QML_SOURCES = \
    src/util/ui/MacAddrSelector.qml \
    src/util/ui/Toast.qml \
    src/util/ui/ToastManager.qml

JS_SOURCES =

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
    javascript.files = $$JS_SOURCES
    qml.files = $$QML_SOURCES

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
