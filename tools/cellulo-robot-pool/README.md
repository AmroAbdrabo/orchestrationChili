cellulo-robot-pool
==================

A suite of tools that provide a server that stays alive and connected to the Cellulo robots:

  - `cellulorobotpoold`: Daemon that encapsulates a `CelluloLocalRelayServer` where the Bluetooth sockets to Cellulo robots stay connected. All messages coming from the daemon are dumped via `syslog`. This is found in `/var/log/syslog` under Ubuntu.
  - `cellulo-robot-pool-gui`: Starts, stops and controls `cellulorobotpoold` to add or remove robots as well as connect to or disconnect from them.

While `cellulorobotpoold` is alive, a `CelluloRobotPoolClient` in a Cellulo application can connect to the server and
communicate with its already connected robots.

Tested with Qt 5.10.0 on:

  - Ubuntu 17.10
  - ~~macOS 10.13.3~~ not yet, ongoing work
  - ~~Android~~ not yet, ongoing work

Desktop build
-------------

1. Build and install [qml-cellulo](../../).
1. Run the following:

    ```
    mkdir build && cd build
    qt-install-root/5.10.0/target-platform/bin/qmake ..
    make -j5
    sudo make install
    ```

Desktop usage
-------------

Run `cellulo-robot-pool-gui` to launch the pool control panel. At startup, `cellulorobotpoold` will be started
automatically, which can be manually stopped or started as well from the "Server controls" panel. "Scan for robots"
panel can be used to scan and add available robots to the pool. Once added, they can be connected to using the "Robots
on server" panel. Once all desired robots are added and connected to, `cellulo-robot-pool-gui` can be closed. Then,
these robots in the pool can be used in an application through `CelluloRobotPoolClient`, see
[samples/cellulo-swarm-demo/](../../samples/cellulo-swarm-demo/) for an example.
