cellulo-cellulorobot-pose-vel-control-demo
==========================================

Demonstrates the simultaneous pose and velocity controller within `CelluloRobot.qml` that is a loop over Bluetooth. Needs at least 400 mm by 400 mm playground, one is already provided: [assets/map-dotted.pdf](assets/map-dotted.pdf). The connected robot moves on a circle while turning around itself; self rotation is clockwise during the first half of the motion and counter-clockwise during the second half. Can be built with Qt 5.6.2 on Ubuntu 16.04 for Ubuntu 16.04. It needs [qml-cellulo](../../) to be installed. It is intended to be loaded into Qt Creator, built and deployed from there.
