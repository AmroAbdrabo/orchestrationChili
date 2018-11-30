import QtQuick 2.1
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Entity{
    id: root3d

    property var client
    property int numRobots: client ? client.robots.length : 0

    property Component sphereComponent: Qt.createComponent("RobotSphere.qml")

    onNumRobotsChanged: {
        var i;
        for(i=0;i<spheres.length;i++)
            spheres[i].destroy();
        spheres = [];

        for(i=0;i<numRobots;i++){
            var robotSphere = sphereComponent.createObject(root3d);
            robotSphere.robot = client.robots[i];
            spheres.push(robotSphere);
        }
    }

    property var spheres: []

    Entity{
        components: [
            //@disable-check M300
            Transform{ translation: Qt.vector3d(420.5, 420.5, -500) },
            PointLight{
                color: "white"
                intensity: 2
                constantAttenuation: 1.0
                linearAttenuation: 0.0
                quadraticAttenuation: 0.0
            }
        ]
    }
}
