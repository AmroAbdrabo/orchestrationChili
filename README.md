qml-cellulo
===========

This is a qml module for communicating with Cellulo robots over bluetooth or simulated robots over web sockets for
debugging purposes. It supports desktop and Android and was tested with Qt 5.8.0. Below are the USB Bluetooth dongles
that were confirmed to work with the Cellulo robots under Ubuntu 16.04 with BlueZ 5.37:

  - Asus USB-BT400, reports a `Broadcom BCM20702A0` to be present, bought from https://www.conrad.ch/ce/fr/product/1090718/
  - Vivanco 30447, reports a `Broadcom BCM20702A0` to be present, bought from https://www.conrad.ch/ce/fr/product/673433/
  - No-brand pcDuino USB dongle, reports a `Cambridge Silicon Radio, Ltd` to be present, bought from https://www.conrad.ch/ce/fr/product/1233685/
  - Conrad 448876, reports a `Cambridge Silicon Radio, Ltd` to be present, bought from https://www.conrad.ch/ce/fr/product/448876/
  - Digitus DN-30210-1, reports a `Cambridge Silicon Radio, Ltd` to be present, bought from https://www.conrad.ch/ce/fr/product/395775/
  - Renkforce Bluetooth® 4.0 stick, reports a `Cambridge Silicon Radio, Ltd` to be present, bought from https://www.conrad.ch/ce/fr/product/1483951/

Dependencies
-------------

  - `nanosvg` to convert SVG paths into Cellulo zone paths, run `git submodule init && git submodule update` on the root directory to obtain it.
  - [qml-bluetooth-extras](https://github.com/chili-epfl/qml-bluetooth-extras) must be installed to obtain the list of local Bluetooth adapters, see the repository for installation instructions.

Desktop build
-------------

Tested on Ubuntu 16.04:

```
mkdir build-desktop && cd build-desktop
/path-to-qt-install-root/5.8/gcc_64/bin/qmake ..
make -j5 install
```

This will install the QML plugin inside the Qt sysroot, so it must be writable by you. **Be aware that this is not a sandboxed installation.**

Android build
-------------

Tested with Android SDK API 25 and Android NDK r10e:

```
export ANDROID_NDK_ROOT=/path-to-android-ndk/
```

```
mkdir build-android && cd build-android
/path-to-qt-install-root/5.8/android_armv7/bin/qmake ..
make -j5 install
```

This will install the QML plugin inside the Qt sysroot, so it must be writable by you. **Be aware that this is not a sandboxed installation.**

Build & run unit tests
----------------------

```
mkdir build-test && cd build-test
/path-to-qt-install-root/5.8/gcc_64/bin/qmake .. "CONFIG += test"
make -j5
./celluloplugintests
```

Tools & Samples
---------------

Tools are under [tools/](tools/), samples are under [samples/](samples/). See their README's for instructions.

QML API
-------

See [DOCUMENTATION.md](DOCUMENTATION.md).
