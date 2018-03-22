cellulo-control-panel
=====================

Tool to control and listen to all features of a single Cellulo robot.

Tested with Qt 5.10.0 on:

  - Ubuntu 17.10
  - macOS 10.13.3
  - Android 7.1.2 (also available on the Play Store)

Linux & macOS build
-------------------

1. Build and install [qml-cellulo](../../).
1. Run the following:

    ```
    mkdir build && cd build
    qt-install-root/5.10.0/target-platform/bin/qmake ..
    make -j5
    sudo make install
    ```

Android build
-------------

1. Build and install [qml-cellulo](../../).
1. Load into Qt Creator, connect your device over USB, click `Run`.

Linux usage
-----------

Run `cellulo-control-panel` in the terminal.

macOS usage
-----------

Launch the `cellulo-control-panel` app from Launchpad.

Android usage
-------------

Click `Run` from within Qt Creator to install and launch or manually launch the app if it's already installed.
