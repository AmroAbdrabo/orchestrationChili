cellulo-locomotion-demo
=======================

Demonstrates the locomotion capability of the Cellulo robots.

Tested with Qt 5.6.2 on Ubuntu 16.04 and Android SDK 25 and NDK r10e.

Build
-----

1. Build and install [qml-cellulo](../../).
1. Load into Qt Creator, click `Build Project`.

Run
---

1. Print [assets/paper-dotted.pdf](assets/paper-dotted.pdf)
1. Click `Run` inside Qt Creator
1. Connect to a robot
1. Click `Go`
1. Robot should go to the designated pose, even after being kidnapped and put elsewhere; robot should light up in a random color every time it reaches the pose again
1. Play with the pose parameters