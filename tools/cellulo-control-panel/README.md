cellulo-control-panel
=====================

Tool to control and listen to all features of a single Cellulo robot.

Tested with Qt 5.6.2 on Ubuntu 16.04 and Android SDK 25 and NDK r10e.

Desktop build
-------------

1. Build and install [qml-cellulo](../../).
1. Run the following:

    ```
    mkdir build-desktop && cd build-desktop
    /path-to-qt-install-root/5.8/gcc_64/bin/qmake ..
    make -j5
    sudo make install
    ```

Android build
-------------

1. Build and install [qml-cellulo](../../).
1. Load into Qt Creator, connect your device over USB, click `Run`.

Desktop usage
-------------

Run `cellulo-control-panel`.

Android usage
-------------

Click `Run` from within Qt Creator to install and launch or manually launch the app if it's already installed.
