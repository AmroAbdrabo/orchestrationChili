cellulo-swarm-demo
==================

Demonstrates swarm formations with the Cellulo robots.

Tested with Qt 5.6.2 on Ubuntu 16.04. **Will not work properly on Android with more than 5 robots due to Bluetooth limitations.**

Build
-----

1. Build and install [qml-cellulo](../../).
1. Load into Qt Creator, click `Build Project`.

Run
---

1. Print [assets/map-dotted.pdf](assets/map-dotted.pdf); can be run on a smaller playground too, but the larger the better for manipulation comfort
1. Click `Run` inside Qt Creator
1. Connect to as many robots as you want (start from the top and leave no gaps in the list!); preferably to not more than 5 robots per Bluetooth adapter that is present, more than 7 per adapter is impossible anyway due to Bluetooth limitation
1. Check `Go`
1. Robots should come into a lattice formation, but you probably need to put the robots in their correct place manually at first since there is no pathfinding algorithm present
1. Touch any button of a robot to interact with it:
    - Move one robot around; the rest of the lattice should follow
    - Move two robots to do the "pinch-zoom" gesture on the whole lattice
