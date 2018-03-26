TEMPLATE = app

linux:!android {
    message("Building for Linux")

    TARGET = cellulorobotpoold

    QT += core bluetooth quick

    SOURCES += src/main_linux.cpp

    INCLUDEPATH += \
        ../../../src/comm/ \
        ../../../src/comm/relay/ \
        ../../../include/

    LIBS += -L$$[QT_INSTALL_QML]/Cellulo/ -lcelluloplugin
    QMAKE_RPATHDIR += $$[QT_INSTALL_QML]/Cellulo/

    target.path = /usr/local/bin/
    INSTALLS += target
}

macx:!android {
    message("Building for macOS")

    TARGET = "Cellulo Robot Pool Daemon"

    QT += core bluetooth quick

    SOURCES += src/main_macos.cpp

    RESOURCES += qml.qrc

    ICON = assets/cellulorobotpoold.icns
    QMAKE_INFO_PLIST = assets/Info.plist

    target.path = /Applications/
    INSTALLS += target
}
