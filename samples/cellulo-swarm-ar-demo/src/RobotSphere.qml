import QtQuick 2.9
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Entity{
    id: root

    property var robot ///< To be set by the user

    property real x: robot.x
    property real y: robot.y
    property real w: robot.w

    readonly property real minabsw: 0.5
    readonly property real cdeltaz: 2.0

    property real z: maxz
    readonly property real maxz: -55 -40
    readonly property real minz: maxz - 200

    onWChanged: {
        if(Math.abs(w) > minabsw){
            z += cdeltaz*w;
            if(z > maxz)
                z = maxz;
            else if(z < minz)
                z = minz;
        }
    }

    components: [
        PhongMaterial{
            ambient: "#A0A0A0"
            diffuse: "#A0A0A0"
        },

        //@disable-check M300
        Transform{ translation: Qt.vector3d(root.x, root.y, root.z) },
        SphereMesh{ radius: 40 }
    ]

    Component.onCompleted: console.log("*******************************************SPHERE COMPLETE")
} 
