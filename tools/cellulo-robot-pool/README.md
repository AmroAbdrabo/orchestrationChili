cellulo-robot-pool
==================

A suite of tools that provide a server that stays alive and connected to the Cellulo robots:

  - `cellulorobotpoold`: Daemon that encapsulates a `CelluloLocalRelayServer` where the Bluetooth sockets to Cellulo robots stay connected.
    - *Linux*: Launch as daemon (`start-stop-daemon [--start|--stop] --exec /usr/local/bin/cellulorobotpoold`) or manage from `cellulo-robot-pool-gui`. All messages coming from the daemon are dumped via `syslog`. This is found in `/var/log/syslog` under Ubuntu.
    - *macOS*: Must be launched manually as an app (named `Cellulo Robot Pool Daemon`) and must be left running. All messages coming from the daemon are dumped via `syslog`. This is found in `/var/log/system.log` under macOS.
  - `cellulo-robot-pool-gui`: controls `cellulorobotpoold` to add or remove robots as well as connect to or disconnect from them.
    - *Linux*: Can start and stop `cellulorobotpoold` as well.
    - *macOS*: Launch as an app (called `Cellulo Robot Pool GUI`). Cannot start and stop `cellulorobotpoold`, it must be launched manually as an app and must be left running.

While `cellulorobotpoold` is alive, a `CelluloRobotPoolClient` in a Cellulo application can connect to the server and
communicate with its already connected robots.

Tested with Qt 5.10.0 on:

  - Ubuntu 17.10
  - macOS 10.13.3
  - ~~Android~~ not yet, ongoing work

Desktop build
-------------

Regardless of the platform:

1. Build and install [qml-cellulo](../../).
1. Run the following:

    ```
    mkdir build && cd build
    qt-install-root/qt-version/target-platform/bin/qmake ..
    make -j5
    sudo make install
    ```

Linux usage
-----------

Run `cellulo-robot-pool-gui` to launch the pool control panel. At startup, `cellulorobotpoold` will be started
automatically, which can be manually stopped or started as well from the "Server controls" panel. "Scan for robots"
panel can be used to scan and add available robots to the pool. Once added, they can be connected to using the "Robots
on server" panel. Once all desired robots are added and connected to, `cellulo-robot-pool-gui` can be closed. Then,
these robots in the pool can be used in an application through `CelluloRobotPoolClient`, see
[samples/cellulo-swarm-demo/](../../samples/cellulo-swarm-demo/) for an example.

macOS usage
-----------

First, launch the `Cellulo Robot Pool Daemon` app. Then launch the `Cellulo Robot Pool GUI` app to launch the pool
control panel. "Scan for robots" panel can be used to scan and add available robots to the pool. Once added, they can be
connected to using the "Robots on server" panel. Once all desired robots are added and connected to,
`cellulo-robot-pool-gui` can be closed. Then, these robots in the pool can be used in an application through
`CelluloRobotPoolClient`, see [samples/cellulo-swarm-demo/](../../samples/cellulo-swarm-demo/) for an example.

**Important note**: Multiple adapters are not supported on macOS, only the internal one is available. This will limit
the number of connectable robots certainly to 7 and practically to around 5.
