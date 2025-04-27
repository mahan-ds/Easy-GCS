// import QtQuick
// import QtQuick.Controls 2.15


// Window {
//     width: 640
//     height: 480
//     visible: true
//     title: qsTr("Hello World")
//     id : root
//     property string statusText: "Disconnected"

//     Rectangle{
//         id : connectionrec
//         width: parent.width/8
//         height: parent.height/15
//         color: "black"
//         radius: 15
//         anchors.top: parent.top
//         anchors.right: parent.right
//         anchors.rightMargin : 5
//         anchors.topMargin: 5
//         Row {
//             anchors.fill: parent
//             anchors.margins: 5
//             spacing: 10

//             Image {
//                 id : connectionImage
//                 source: "qrc:/image/redchain.png"
//                 width: parent.height
//                 height: parent.height/2
//                 anchors.verticalCenter: parent.verticalCenter
//             }

//             Label {
//                 id : connectionLabel
//                 text:  root.statusText
//                 color: "white"
//                 font.pointSize: parent.height / 3
//                 verticalAlignment: Text.AlignVCenter
//                 horizontalAlignment: Text.AlignHCenter
//                 anchors.verticalCenter: parent.verticalCenter
//             }
//         }
//         MouseArea{
//             anchors.fill : parent
//             onClicked: {
//                 if(root.statusText == "Disconnected")
//                 {
//                     root.statusText = "Scanning..."
//                     connectionImage.source = "qrc:/image/redchain.png"
//                     serialHandler.startScanning()
//                 }
//                 else
//                 {
//                     serialHandler.disconnectFromPixhawk()
//                     root.statusText = "Disconnected"
//                     connectionImage.source = "qrc:/image/redchain.png"
//                 }
//             }
//         }
//     }


//     Connections {
//         target: serialHandler

//         onConnectedToPixhawk: function(portName) {
//             root.statusText = "Connected"
//             connectionImage.source = "qrc:/image/greenchain.png"
//         }

//         onUnintentionaldisconnect: function(){
//             root.statusText = "Scanning..."
//             connectionImage.source = "qrc:/image/redchain.png"
//         }
//     }




//     property string mavlinkText: "Waiting for messages..."

//         Column {
//             anchors.centerIn: parent
//             spacing: 20

//             Text {
//                 text: "Status: " + mavlinkText
//             }

//             Connections {
//                 target: mavlinkParser

//                 onHeartbeatReceived: {
//                     mavlinkText = "Heartbeat received!"

//                 }

//                 onSysStatusReceived: {
//                     mavlinkText = "Battery Remaining: " + sysStatusReceived.battery_remaining + "%"
//                 }

//                 onPositionReceived: {
//                     mavlinkText = "GPS Position: " + positionReceived.lat + ", " + positionReceived.lon
//                 }
//             }
//         }

// }
import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    id : root
    property string statusText: "Disconnected"

    Rectangle{
        id : connectionrec
        width: parent.width/8
        height: parent.height/15
        color: "black"
        radius: 15
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin : 5
        anchors.topMargin: 5
        Row {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 10

            Image {
                id : connectionImage
                source: "qrc:/image/redchain.png"
                width: parent.height
                height: parent.height/2
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                id : connectionLabel
                text:  root.statusText
                color: "white"
                font.pointSize: parent.height / 3
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MouseArea{
            anchors.fill : parent
            onClicked: {
                if(root.statusText == "Disconnected")
                {
                    root.statusText = "Scanning..."
                    connectionImage.source = "qrc:/image/redchain.png"
                    //serialHandler.startScanning()
                    serialHandler.requestStartScanning()
                }
                else
                {
                    serialHandler.disconnectFromPixhawk()
                    root.statusText = "Disconnected"
                    connectionImage.source = "qrc:/image/redchain.png"
                }
            }
        }
    }

    Connections {
        target: serialAdaptor

        onConnectedToPixhawk: function(portName) {
            root.statusText = "Connected"
            connectionImage.source = "qrc:/image/greenchain.png"
        }

        onUnintentionaldisconnect: function(){
            root.statusText = "Scanning..."
            connectionImage.source = "qrc:/image/redchain.png"
        }
    }

    // برای نمایش وضعیت mavlink
    // property string mavlinkText: "Waiting for messages..."

    // Column {
    //     anchors.centerIn: parent
    //     spacing: 20

    //     Text {
    //         text: "Status: " + mavlinkText
    //     }

    //     Connections {
    //         target: mavlinkParser

    //         onHeartbeatReceived: {
    //             mavlinkText = "Heartbeat received!"
    //         }

    //         onSysStatusReceived: {
    //             mavlinkText = "Battery Remaining: " + sysStatusReceived.battery_remaining + "%"
    //         }

    //         onPositionReceived: {
    //             mavlinkText = "GPS Position: " + positionReceived.lat + ", " + positionReceived.lon
    //         }
    //     }
    // }
}
