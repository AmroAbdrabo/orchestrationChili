TEMPLATE = app

QT += qml quick bluetooth

SOURCES += src/main.cpp

RESOURCES += qml.qrc

linux:!android {
    message("Building for Linux")

    TARGET = cellulo-robot-pool

    target.path = /usr/local/bin/
    INSTALLS += target
}

android {
    message("Building for Android.")

    target.path = /libs/armeabi-v7a
    export(target.path)
    INSTALLS += target
    export(INSTALLS)

    DISTFILES += \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}
