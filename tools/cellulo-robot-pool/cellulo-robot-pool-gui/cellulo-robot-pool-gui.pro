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
