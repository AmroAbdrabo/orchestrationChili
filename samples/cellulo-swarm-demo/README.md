cellulo-swarm-demo
==================

Demonstrates swarm formations with the Cellulo robots. Also demonstrates the use of `cellulo-robot-pool` to easily
connect to many robots that can be used in any activity without disconnecting.

Tested with Qt 5.8.0 on Ubuntu 16.04. Does not work on Android yet.

Build
-----

1. Build and install [qml-cellulo](../../).
1. Build and install [tools/cellulo-robot-pool](../../tools/cellulo-robot-pool/).
1. Load into Qt Creator, click `Build Project`.

Run
---

1. Print [assets/map-dotted.pdf](assets/map-dotted.pdf); can be run on a smaller playground too, but the larger the better for manipulation comfort
1. Plug in external Bluetooth dongles,  at least one dongle for each 5 robots must be present; so for 15 robots, at least 2 external dongles are needed (in addition to the internal adapter)
1. Run `cellulo-robot-pool-gui` to launch the robot pool daemon
1. Click `Scan` to scan the robots around
1. Click `+` next to the discovered robots to add them to the pool or click `Add all above` to add all found robots
1. If more than 5 robots are desired, click `Equally distribute local adapters` or select local adapters manually (second drop-down box on each list item)
1. Click `Connect` on each robot one by one
1. Once all robots are connected, close `cellulo-robot-pool-gui`
1. Load `cellulo-swarm-demo` into Qt Creator, configure for Desktop and click `Run`
1. Check `Go`
1. Robots should come into a lattice formation, but you probably need to put the robots in their correct place manually at first since there is no pathfinding algorithm present
1. Touch any button of a robot to interact with it:
    - Move one robot around; the rest of the lattice should follow
    - Move two robots to do the "pinch-zoom" gesture on the whole lattice
