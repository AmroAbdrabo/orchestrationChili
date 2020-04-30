Simulated Cellulo
==================
On this branch, There is an extension of the cellulo-qml-plugin where I added an option to enable testing on a virtual cellulo instead of connecting to a real cellulo.
> you should build and install once you clone the new plugin. 

```sh
$ mkdir build && cd build
$ qt-install-root/qt-version/target-platform/bin/qmake ..
$ sudo make -j5 install
```

New Properties:
---------------

  - simulatedCellulo: boolean, true to enbale simulated robot, false to connect to real robot. 
  - initPose: Vector3D sets initial pose for the simulated robot, is zero for real robot

New simulator use examples:
----------------------
  - there is an example button "orangemap" that set's up an orange pacman map with zones
you can look at the code executed by that button in the controlsWindow.qml
to see how to setup your own background image, map dimensions and display size, aswell as create and add zones to the map.

Implemented functions: 
-----------------------
- setGoalVelocity 
- update Pose (x,y,theta)
- therefore all functionalities of zoneEngine works. 
- setGoalPose(along with all other setGoal methods for the robots pose)
- setVisualEffect(as of now only the effect "VisualEffectConstAll" works)
TODO: implement other visualEffets
TODO: vector on robot that can indicate some sort of haptic feedback

NOT Implemented functions: 
---------------------------

- everything related to touch sensors
- everything related to visual effects
- everything related to haptics

Sample App:
-----------
A sample app can be found in tools/cellulo-control-panel-test: 
[Video Demo](https://drive.google.com/file/d/1BJgI9DHwUodLcxog78unA2E0oDTqkI7s/view?usp=sharing)

Moving robot on click example in qml : 
--------------------------------------
click on the robot to choose the robot, click and drag the robot to make it move,(you can also scroll to rotate it manually)
click on the robot again to deactivate manual movement. 
```
CelluloRobot{
        id: robotComm
        property var init: Qt.vector3d(0,0,0)
        Image{
            id:img
            source: 'qrc:/assets/blue.svg'
            width: 75
            height: 75
            property bool isSelected: false
            x: isSelected?img.x:robotComm.x-img.width/2
            y: isSelected?img.y:robotComm.y-img.height/2
            rotation: robotComm.theta

            MouseArea {
                id: themouse
                anchors.fill: parent
                drag.target: parent
                onClicked: {
                    robotComm.init=Qt.vector3d(robotComm.x,robotComm.y,robotComm.theta)
                    parent.isSelected=!parent.isSelected
                    console.log(parent.isSelected)
                }
            }
        }
        simulatedCellulo: true
        initPose: img.isSelected?Qt.vector3d(img.x+img.width/2,img.y+img.height/2,img.rotation):robotComm.init
        onZoneValueChanged: console.log("zone changed")
    }
