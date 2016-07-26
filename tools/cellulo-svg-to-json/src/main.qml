import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import Cellulo 1.0

ApplicationWindow{
    id: window
    visible: true

    width: root.width
    height: root.height

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    Item{
        id: root

        width: childrenRect.width
        height: childrenRect.height

        Column{
            spacing: 5

            Row{
                spacing: 5

                TextField{
                    id: inFile
                    width: 500
                    anchors.verticalCenter: parent.verticalCenter
                    placeholderText: "Input .svg file"
                }
                Button{
                    text: "Choose file"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: inputFilePicker.open()
                }
            }

            Row{
                spacing: 5

                TextField{
                    id: outFile
                    width: 500
                    anchors.verticalCenter: parent.verticalCenter
                    placeholderText: "Output .json file"
                }
                Button{
                    text: "Choose file"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: outputFilePicker.visible = true
                }
            }

            Row{
                spacing: 5

                Text{
                    text: "DPI:"
                    anchors.verticalCenter: parent.verticalCenter
                }
                TextField{
                    id: dpi
                    width: 500
                    anchors.verticalCenter: parent.verticalCenter
                    placeholderText: "(inkscape default is 90)"
                    text: "90"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                }
            }


            Button{
                text: "Go"
                onClicked: toast.show(CelluloSVGUtil.dumpAllPathsToJSON(inFile.text, outFile.text, parseFloat(dpi.text)))
            }
        }

        FileDialog{
            id: inputFilePicker
            nameFilters: [ "SVG files (*.svg)", "All files (*)" ]
            title: "Choose input file"
            folder: shortcuts.home
            selectFolder: false
            selectExisting: true
            selectMultiple: false
            onAccepted: inFile.text = fileUrl.toString()
        }

        FileDialog{
            id: outputFilePicker
            nameFilters: [ "JSON file (*.json)", "All files (*)" ]
            title: "Choose output file"
            folder: shortcuts.home
            selectFolder: false
            selectExisting: false
            selectMultiple: false
            onAccepted: outFile.text = fileUrl.toString()
        }

        ToastManager{ id: toast }
    }
}
