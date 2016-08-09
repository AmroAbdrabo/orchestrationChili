qml-cellulo
===========

This is a qml module for communicating with Cellulo robots over bluetooth or
simulated robots over web sockets for debugging purposes. It supports desktop
and Android and was tested with Qt 5.4.2.

Dependencies
-------------
- For the haptics-dev branch : 
nanosvg : https://github.com/memononen/nanosvg
Need to copy the src directory of nanosvg into cellulo-qml-plugin/src/util/svg/


Desktop build
-------------

Tested on Ubuntu 14.04:

```
mkdir build-desktop && cd build-desktop
/path-to-qt-install-root/5.4/gcc_64/bin/qmake ..
make -j5 install
```

Android build
-------------

Tested with Android API 17 (Android version 4.2) and Android NDK r10e:

```
export ANDROID_NDK_ROOT=/path-to-android-ndk/
```

```
mkdir build-android && cd build-android
/path-to-qt-install-root/5.4/android_armv7/bin/qmake ..
make -j5 install
```

Build & run unit tests
----------------------

```
mkdir build-test && cd build-test
/path-to-qt-install-root/5.4/gcc_64/bin/qmake .. "CONFIG += test"
make -j5
./celluloplugintests
```
