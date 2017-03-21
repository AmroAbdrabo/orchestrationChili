cellulo-robot-pool
==================

Controls a `CelluloLocalRelayServer` daemon, in other words, a pool of `CelluloBluetooth` connections that are
persistent even if the application is closed. Includes the GUI to perform all controls on this daemon. Requires that
this daemon, i.e [cellulo-relay-server](../cellulo-relay-server/), is built and installed.

Desktop build
-------------

Tested on Ubuntu 16.04.

1. Build and install [qml-cellulo](../../).
1. Build and install [cellulo-relay-server](../cellulo-relay-server/).
1. Run the following:

    ```
    mkdir build-desktop && cd build-desktop
    /path-to-qt-install-root/5.8/gcc_64/bin/qmake ..
    make -j5
    sudo make install
    ```

Desktop usage
-------------

```
cellulo-robot-pool
```

Android build
-------------

Coming soon...

Android usage
-------------

Coming soon...
