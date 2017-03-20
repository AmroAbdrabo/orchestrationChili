TEMPLATE = app

linux:!android {
    message("Building for Linux")

    TARGET = cellulorelayserverd

    QT += core bluetooth quick

    SOURCES += src/main_linux.cpp

    INCLUDEPATH += \
        ../../src/comm/ \
        ../../include/

    LIBS += -L$$[QT_INSTALL_QML]/Cellulo/ -lcelluloplugin
    QMAKE_RPATHDIR += $$[QT_INSTALL_QML]/Cellulo/

    target.path = /usr/local/bin/
    INSTALLS += target
}

android {
    message("Building for Android.")
    #LIBS += -L/path/to/android/libs
}

#android {
#    target.path = /libs/armeabi-v7a
#    export(target.path)
#    INSTALLS += target
#    export(INSTALLS)

#    ANDROID_EXTRA_LIBS = \
#        $$[QT_INSTALL_QML]/Cellulo/libcelluloplugin.so

#    ANDROID_PERMISSIONS += \
#        android.permission.BLUETOOTH
#}

#DISTFILES += \
#    android/AndroidManifest.xml \
#    android/gradle/wrapper/gradle-wrapper.jar \
#    android/gradlew \
#    android/res/values/libs.xml \
#    android/build.gradle \
#    android/gradle/wrapper/gradle-wrapper.properties \
#    android/gradlew.bat

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
