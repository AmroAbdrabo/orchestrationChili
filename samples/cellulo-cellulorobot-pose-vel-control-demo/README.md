cellulo-cellulorobot-pose-vel-control-demo
==========================================

Demonstrates the simultaneous pose and velocity controller within `CelluloRobot.qml` that is a loop over Bluetooth.

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

1. Print [assets/map-dotted.pdf](assets/map-dotted.pdf) or any other playground that is at least 400mm by 400mm
1. Click `Run` inside Qt Creator
1. Connect to a robot
1. Check `Go`
1. Robot should move on a circle while turning around itself; self rotation is clockwise during the first half of the motion and counter-clockwise during the second half
1. Robot can be kidnapped and put elsewhere, should still converge to the trajectory
