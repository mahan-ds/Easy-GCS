import QtQuick
import QtQuick.Controls 2.15


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    id : root
    property string statusText: "Disconnected"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Status: " + root.statusText
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        Button {
            text: "Connect to Pixhawk"
            onClicked: {
                root.statusText = "Scanning..."
                serialHandler.startScanning()
            }
        }

        Button {
            text: "Disconnect"
            onClicked: {
                serialHandler.disconnectFromPixhawk()
                root.statusText = "Disconnected"
            }
        }
    }
    Connections {
        target: serialHandler

        onConnectedToPixhawk: function(portName) {
            root.statusText = "Connected to " + portName
        }

        onDisconnect: function(){
            root.statusText = "Scanning..."
        }
    }
}
