import QtQuick 2.1
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Entity{
    property var client: null

    Repeater{
        model: client.robots.length

        Item{
            Connections{
                target: client.robots[index]

                onKeyTouched: console.log("key touched " + index)
            }
        }
    }

    Entity {
        components: [
            PhongMaterial{
                ambient: "white"
                diffuse: "white"
            },

            //@disable-check M300
            Transform{
                matrix: {
                    var m = Qt.matrix4x4();
                    m.translate(Qt.vector3d(420.5, 420.5, 0));
                    return m;
                }
            },
            SphereMesh{ radius: 40 }
        ]
    }

    Entity{
        components: [
            //@disable-check M300
            Transform{ translation: Qt.vector3d(420.5, 420.5, -500) },
            PointLight{
                color: "white"
                intensity: 3
                constantAttenuation: 1.0
                linearAttenuation: 0.0
                quadraticAttenuation: 0.0
            }
        ]
    }
}
