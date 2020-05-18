import QtQuick 2.0

//Item to display goal velocity (ALWAYS points to goalPose and uses robotComm.goalV to set the norm)
Item {
    function norm(vx,vy){ return Math.sqrt(vx*vx+vy*vy); }
    anchors.centerIn: parent
    height: parent.height * 2
    width: parent.width  * 2 + norm(robotComm.vx, robotComm.vx)/10000 //can use the width as the norm of the vector

    Canvas {
        id: canvas

        height: parent.height
        width: parent.width

        property var norm:  robotComm.goalV/2;

        antialiasing: true

        onPaint: {
            var ctx = canvas.getContext('2d')
            console.log("log completed" + norm)
            if(robotComm.isSelected) {
                ctx.strokeStyle = "#000000"
                ctx.lineWidth = canvas.height * 0.03
                ctx.beginPath()
                ctx.moveTo(canvas.width/2 , canvas.height/2)
                //ctx.lineTo(canvas.width/2 + arrowX*norm, canvas.height/2+arrowY*norm)
                ctx.lineTo(canvas.width/2 + norm, canvas.height/2)

                //arrow head
                ctx.lineWidth = canvas.height * 0.02
                ctx.moveTo(canvas.width/2 + norm, canvas.height/2);
                ctx.lineTo(canvas.width/2 + norm - 3 - norm/16, canvas.height/2 - 3 -norm/16);

                ctx.moveTo(canvas.width/2 + norm, canvas.height/2);
                ctx.lineTo(canvas.width/2 + norm - 3 - norm/16, canvas.height/2 + 3 + norm/16);

                ctx.stroke();
            } else {
                ctx.reset();
            }
        }
    }

}
