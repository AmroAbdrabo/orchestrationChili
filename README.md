Simulated Cellulo
==================
On this branch, There is an extension of the cellulo-qml-plugin where I added an option to enable testing on a virtual cellulo instead of connecting to a real cellulo.
> you should build and install once you clone the new plugin(and "sudo make j5 install" every time you pull it, to update it)

```sh
$ mkdir build && cd build
$ qt-install-root/qt-version/target-platform/bin/qmake ..
$ sudo make -j5 install
```

New Properties:
---------------
  - simulatedCellulo: boolean, true to enbale simulated robot, false to connect to real robot. 
  - initPose: Vector3D sets initial pose for the simulated robot, is zero for real robot
  - color: the color of the robot
  - lediColor: represents the color of the i'th led of the robot (for i between 0 and 5)

Implemented functions :
-----------------------
- setGoalVelocity 
- update Pose (x,y,theta)
- therefore all functionalities of zoneEngine works. 
- setGoalPose(along with all other setGoal methods for the robots pose)
- setVisualEffect(for all visual effects)(However gesture features are still not implemented)
TODO: vector on robot that can indicate some sort of haptic feedback
TODO: correctly implement other functions related to leds(see not implemented functions)

NOT Implemented functions: 
---------------------------
- gesture for visual effects + suspendLedsIdle+suspendLedsSleep+resumeLedSleep+resumeLedsIdle functions
- everything related to touch sensors
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
```

New simulator use examples:
----------------------
  - There is an example button "orangemap" that set's up an orange pacman map with zones
you can look at the code executed by that button in the controlsWindow.qml
to see how to setup your own background image, map dimensions and display size, aswell as create and add zones to the map.
- Here is a snippet on what clicking that button does:

```
Button{
    text: "orangemap"
    onClicked: {
        //update backgroundsize and windowsize to desired map dimensions in mm
        paper.height = 420;
        paper.width = 980;
        
        //be default window takes paper dimensions(i.e 1 unit of the window  size will 
        //represent 1mm in real life.)
        //but can scale the window size up or down as long as both the height
        //and width are scaled equally(i.e the relation "width/height" stays the same)
        window2.width = paper.width;
        window2.height = paper.height;
        //load background image
        backgroundImg.source = 'qrc:/assets/orangemapcorrected.svg'

        //create zones and add robots to the zoneEngine
        MyFuncs.createZones();
        zoneEngine.addNewClient(robotComm1)
        zoneEngine.addNewClient(robotComm2)
    }
}
 ```
