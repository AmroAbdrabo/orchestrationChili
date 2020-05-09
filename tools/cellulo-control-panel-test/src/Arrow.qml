import QtQuick 2.0


Item {
    function norm(vx,vy){ return Math.sqrt(vx*vx+vy*vy); }
    anchors.centerIn: parent
    height: parent.height * 2
    width: parent.width  * 2 + norm(robotComm.vx, robotComm.vy) //can use the width as the norm of the vector

    Canvas {
        id: canvas

        height: parent.height
        width: parent.width


        property var norm: parent.norm(robotComm.vx, robotComm.vy)/2// - parent.norm(robotComm.goalVelX, robotComm.goalVelY);
        antialiasing: true

        onPaint: {
            var ctx = canvas.getContext('2d')
            ctx.strokeStyle = "#000000"
            ctx.lineWidth = canvas.height * 0.03
            ctx.beginPath()
            ctx.moveTo(canvas.width/2 , canvas.height/2)
            ctx.lineTo(canvas.width/2 + norm, canvas.height/2)
            ctx.stroke();
        }
    }

}
