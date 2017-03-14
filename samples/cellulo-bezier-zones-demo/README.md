cellulo-bezier-zones-demo
=========================

Demonstrates more complicated PolyBézier zones that can be used with the Cellulo robots.

Tested with Qt 5.6.2 on Ubuntu 16.04 and Android SDK 25 and NDK r10e.

Build
-----

1. Build and install [qml-cellulo](../../).
1. Load into Qt Creator, click `Build Project`.

Run
---

1. Print [assets/page-dotted.pdf](assets/page-dotted.pdf)
1. Click `Run` inside Qt Creator
1. Connect to a robot
1. Move robot on the map and see:
    - Distance to the PolyBézier curve being calculated
    - Tangent and normal vectors to the curve on the point closest to the robot being calculated, via the closest point's parameter `t`
    - Inside of the PolyBézier curve making the robot red
    - Border of the PolyBézier curve making the robot blue
    - Intersection of border and inside of the PolyBézier curve making the robot violet
1. Enter maximum linear (100 mm/s is fine) and angular velocities (1 rad/s is fine) and click `Follow the path`; robot should follow the path with the given linear velocity while turning with the given angular velocity
1. Now enter desired aligned theta (increase angular velocity if low, 5 rad/s is fine) and click `Follow the path (aligned)`; robot should follow the path while keeping tangent orientation to the curve