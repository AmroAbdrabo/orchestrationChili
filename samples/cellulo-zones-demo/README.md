cellulo-zones-demo
==================

Demonstrates some of the different types of zones (everything except more complicated PolyBézier zones) that can be used with the Cellulo robots.

Tested with Qt 5.8.0 on Ubuntu 16.04 and Android SDK 25 and NDK r10e.

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
