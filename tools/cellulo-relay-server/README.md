cellulo-relay-server
====================

Daemon that encapsulates a `CelluloLocalRelayServer`, in other words, a server that stays alive and connected to the
Cellulo robots. Robots can be added/removed to/from this server by the [cellulo-robot-pool](../cellulo-robot-pool) tool.

Desktop build
-------------

Tested on Ubuntu 16.04:

```
mkdir build-desktop && cd build-desktop
/path-to-qt-install-root/5.8/gcc_64/bin/qmake ..
make -j5
sudo make install
```

Android build
-------------

Coming soon...
