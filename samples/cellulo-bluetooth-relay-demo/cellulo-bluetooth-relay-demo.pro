TEMPLATE = app

QT += qml quick bluetooth

SOURCES += src/main.cpp

RESOURCES += qml.qrc

android {
    target.path = /libs/armeabi-v7a
    export(target.path)
    INSTALLS += target
    export(INSTALLS)
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    ../../../firmware/src/qml-plugin/samples/cellulo-bluetooth-relay-demo/android/AndroidManifest.xml \
    ../../../firmware/src/qml-plugin/samples/cellulo-bluetooth-relay-demo/android/gradle/wrapper/gradle-wrapper.jar \
    ../../../firmware/src/qml-plugin/samples/cellulo-bluetooth-relay-demo/android/gradlew \
    ../../../firmware/src/qml-plugin/samples/cellulo-bluetooth-relay-demo/android/res/values/libs.xml \
    ../../../firmware/src/qml-plugin/samples/cellulo-bluetooth-relay-demo/android/build.gradle \
    ../../../firmware/src/qml-plugin/samples/cellulo-bluetooth-relay-demo/android/gradle/wrapper/gradle-wrapper.properties \
    ../../../firmware/src/qml-plugin/samples/cellulo-bluetooth-relay-demo/android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
