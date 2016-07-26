import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.3
import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true

    width: 640
    height: 480

    Column{
        spacing: 5

        TextField{
            id: inFile
            placeholderText: "Input .svg"
        }

        TextField{
            id: outFile
            placeholderText: "Output .json"
        }

        TextField{
            id: dpi
            placeholderText: "DPI (inkscape default is 90)"
            text: "90"
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        Button{
            text: "Go"
            onClicked: console.log(CelluloSVGUtil.dumpAllPathsToJSON(inFile.text, outFile.text, parseFloat(dpi.text)))
        }
    }

}
