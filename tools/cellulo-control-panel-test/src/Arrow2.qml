import QtQuick 2.0


Item {
    function norm(vx,vy){ return Math.sqrt(vx*vx+vy*vy); }
    anchors.centerIn: parent
    height: parent.height * 2
    width: parent.width  * 2 +norm(robotComm.goalXY.x - hex.x, robotComm.goalXY.y - hex.y)//norm(robotComm.vx, robotComm.vy) //can use the width as the norm of the vector

    Canvas {
        id: canvas

        height: parent.height
        width: parent.width


        //thing a little more about if i should decouple the x and y component?
        //and the signs
        //probably needa things more about the vx, vy probably will have to decouple it !!
        //(image we wanna move (vx, vy) = (1,1) but we pulling the robot back like (0,-1)
        //then the difference is (1,1)-(0,-1) =  (1,2) so the vector arrow should be (1,2)
        //so we should compute a y norm and a x norm and maybe dont even need to rotate? or even know
        //the goalPose!!! dont even needa kno the goalPose to compute speed differences!!

        //property var norm:  /*(robotComm.goalV - */parent.norm(robotComm.vx, robotComm.vy)/2;
        property var norm:  1;
        property var arrowX : robotComm.goalV - robotComm.vy;
        property var arrowY: robotComm.goalV - robotComm.vx;
        antialiasing: true

        onPaint: {
            var ctx = canvas.getContext('2d')
            ctx.strokeStyle = "#000000"
            ctx.lineWidth = canvas.height * 0.03
            ctx.beginPath()
            ctx.moveTo(canvas.width/2 , canvas.height/2)
            ctx.lineTo(canvas.width/2 + arrowX*norm, canvas.height/2+arrowY*norm)
            //ctx.lineTo(canvas.width/2 + norm, canvas.height/2+ norm)

            //arrow head
            /*ctx.lineWidth = canvas.height * 0.02
            ctx.moveTo(canvas.width/2 + norm, canvas.height/2);
            ctx.lineTo(canvas.width/2 + norm - 3 -  norm/16, canvas.height/2 - 3 -norm/16);

            ctx.moveTo(canvas.width/2 + norm, canvas.height/2);
            ctx.lineTo(canvas.width/2 + norm - 3 - norm/16, canvas.height/2 + 3 + norm/16);*/

            ctx.stroke();
        }
    }

}
