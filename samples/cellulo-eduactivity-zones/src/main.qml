import QtQuick 2.5
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import Cellulo 1.0


ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 1000
    minimumWidth: 1500
    width: mainActivity.width
    height: mainActivity.height

    MainActvity{
        id: mainActivity
        window: window
        visible: true
    }
}
