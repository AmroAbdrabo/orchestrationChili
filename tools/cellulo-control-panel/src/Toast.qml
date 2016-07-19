import QtQuick 2.0

/**
 * @brief An Android-like timed message text in a box that selfdestroys when finished if desired
 */
Rectangle{

    /**
     * Public
     */

    /**
     * @brief Shows this Toast
     *
     * @param {string} text Text to show
     * @param {real} duration Duration to show in milliseconds
     */
    function show(text, duration){
        theText.text = text;
        if(duration >= 2*fadeTime)
            time = duration;
        else
            time = 2*fadeTime;
        anim.start();
    }

    property bool selfDestroying: false ///< Whether this Toast will selfdestroy when it is finished

    /**
     * Private
     */

    id: root

    property real time: 3000
    readonly property real fadeTime: 300

    property real margin: 10

    width: childrenRect.width + 2*margin
    height: childrenRect.height + 2*margin
    radius: margin

    anchors.centerIn: parent

    opacity: 0
    color: "white"

    Text{
        id: theText
        text: ""

        horizontalAlignment: Text.AlignHCenter
        x: margin
        y: margin
    }

    SequentialAnimation on opacity{
        id: anim

        running: false

        NumberAnimation{
            to: 0.9
            duration: fadeTime
        }
        PauseAnimation{
            duration: time - 2*fadeTime
        }
        NumberAnimation{
            to: 0
            duration: fadeTime
        }

        onRunningChanged:{
            if(!running && selfDestroying)
                root.destroy();
        }
    }
}
