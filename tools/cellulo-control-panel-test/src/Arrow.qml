import QtQuick 2.0

Item {
    height: parent.height
    width: parent.width  //can use the width as the norm of the vector

    Canvas {
        id: canvas

        height: parent.height
        width: parent.width

        antialiasing: true

        onPaint: {
            var ctx = canvas.getContext('2d')
            ctx.strokeStyle = "#808080"
            ctx.lineWidth = canvas.height * 0.05
            ctx.beginPath()
            ctx.moveTo(canvas.width/2, canvas.height/2)
            ctx.lineTo(canvas.width, canvas.height/2)
            ctx.stroke()
        }
    }

}
