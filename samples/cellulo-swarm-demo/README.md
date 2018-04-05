cellulo-swarm-demo
==================

Demonstrates swarm formations with the Cellulo robots. Also demonstrates the use of `cellulo-robot-pool` to easily
connect to many robots that can be used in any activity without disconnecting.

Tested with Qt 5.10.1 on:

- Ubuntu 17.10
- macOS 10.13.3 with Xcode 9.3
- Android 7.1.2 with Ubuntu 17.10 host with Android API 23, Android SDK Tools 25.2.5 and Android NDK r10e

As the swarm functionality requires `cellulorobotpoold`, this sample will not work on Windows since WinRT sandboxing prevents multiple apps from communicating with each other.

Build
-----

1. Build and install [qml-cellulo](../../).
1. Build and install [tools/cellulo-robot-pool](../../tools/cellulo-robot-pool/). The build and install heavily depends on your platform, see [tools/cellulo-robot-pool/README.md](../../tools/cellulo-robot-pool/README.md).
1. Load into Qt Creator, click `Build Project`.

Run
---

1. Print [assets/map-dotted.pdf](assets/map-dotted.pdf); can be run on a smaller playground too, but the larger the better for manipulation comfort
1. Plug in external Bluetooth dongles,  at least one dongle for each 5 robots must be present; so for 15 robots, at least 2 external dongles are needed (in addition to the internal adapter.
1. Depending on your platform, follow one of these steps:
  - *Linux* - Run `cellulo-robot-pool-gui` to launch the robot pool daemon and its GUI. The daemon can be managed from the GUI if desired, but should work as it is.
  - *macOS* - Launch the **Cellulo Robot Pool Daemon** app. You can minimize it to the dock without closing it. Then, launch the **Cellulo Robot Pool GUI** app.
  - *Android* - Run the **Cellulo Robot Pool Service** app and click `Start service`. When connected (might take few seconds), exit the app. Then, launch the **Cellulo Robot Pool GUI** app (it might also take a few seconds to connect to the service).
1. Click `Scan` to scan the robots around
1. Click `+` next to the discovered robots to add them to the pool or click `Add all above` to add all found robots
1. [Only available on *Linux*] If more than 5 robots are desired, click `Equally distribute local adapters` or select local adapters manually (second drop-down box on each list item)
1. Click `Connect` on each robot one by one
1. Once all robots are connected, close the Robot Pool GUI.
1. Load `cellulo-swarm-demo` into Qt Creator, configure for Desktop and click `Run`
1. Check `Go`
1. Robots should come into a lattice formation, but you probably need to put the robots in their correct place manually at first since there is no pathfinding algorithm present
1. Touch any button of a robot to interact with it:
    - Move one robot around; the rest of the lattice should follow
    - Move two robots to do the "pinch-zoom" gesture on the whole lattice
