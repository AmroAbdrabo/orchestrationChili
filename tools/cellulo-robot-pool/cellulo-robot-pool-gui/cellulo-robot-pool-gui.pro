TEMPLATE = app

QT += qml quick bluetooth

SOURCES += src/main.cpp

RESOURCES += qml.qrc

linux:!android {
    message("Building for Linux")

    TARGET = cellulo-robot-pool-gui

    target.path = /usr/local/bin/
    INSTALLS += target
}

macx:!android {
    message("Building for macOS")

    TARGET = "Cellulo Robot Pool GUI"

    ICON = assets/cellulo-robot-pool-gui.icns
    QMAKE_INFO_PLIST = assets/Info.plist

    target.path = /Applications/
    INSTALLS += target
}
