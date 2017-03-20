cellulo-relay-server
====================

Daemon that encapsulates a `CelluloLocalRelayServer`, in other words, a server that stays alive and connected to the
Cellulo robots. Robots can be added/removed to/from this server by the [cellulo-robot-pool](../cellulo-robot-pool) tool.
While this daemon is alive, a `CelluloLocalRelayClient` in a Cellulo application can connect to the server and communicate
with its previously connected robots.

On desktop, all messages coming from the daemon are dumped via `syslog`. This is found in `/var/log/syslog` under Ubuntu.

Desktop build
-------------

Tested on Ubuntu 16.04.

1. Build and install [qml-cellulo](../../).
1. Run the following:

    ```
    mkdir build-desktop && cd build-desktop
    /path-to-qt-install-root/5.8/gcc_64/bin/qmake ..
    make -j5
    sudo make install
    ```

Desktop usage
-------------

Prefer [cellulo-robot-pool](../cellulo-robot-pool) to control the daemon from a GUI.

Alternatively, to start the daemon manually:

```
start-stop-daemon --start --exec /usr/local/bin/cellulorelayserverd
```

To stop the daemon manually:

```
start-stop-daemon --stop --exec /usr/local/bin/cellulorelayserverd
```

Android build
-------------

Coming soon...

Android usage
-------------

Coming soon...
