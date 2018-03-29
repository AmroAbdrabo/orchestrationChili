cellulo-zones-demo
==================

Demonstrates some of the different types of zones (everything except more complicated PolyBézier zones) that can be used with the Cellulo robots.

Tested with Qt 5.10.0 on:

  - Ubuntu 17.10
  - macOS 10.13.3
  - Android 7.1.2

Build
-----

1. Build and install [qml-cellulo](../../).
1. Load into Qt Creator, click `Build Project`.

Run
---

1. Print [assets/map.pdf](assets/map.pdf)
1. Click `Run` inside Qt Creator
1. Click `Load from zones.json`
1. Connect to up to 2 robots
1. Move robot(s) on the map and see inner/border zones affect the color of the robot and distance zones calculate the distance to the robot
