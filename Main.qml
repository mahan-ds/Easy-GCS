import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Easy GCS")
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
                width: parent.width/4
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

    Rectangle{
        id : telemetryrec
        width: parent.width/2
        height: parent.height/12
        color: "black"
        anchors.top:parent.top
        anchors.horizontalCenter:  parent.horizontalCenter
        radius: 15
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "black"
            radius: 0
            anchors.top: parent.top
            anchors.bottomMargin: telemetryrec.radius
        }

        Row {
            id: telemetryRow
            anchors.centerIn: parent
            anchors.margins: 10
            spacing: Math.pow(telemetryrec.width, 1.25) / 80

            Row {
                spacing: 5
                Image {
                    source: "qrc:/image/satellite.png"
                    width: telemetryrec.width * 0.05
                    height: telemetryrec.height * 0.4
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label {
                    id: satelliteLabel
                    text: "0"
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: telemetryrec.height * 0.4
                }
            }

            Row {
                spacing: 5
                Image {
                    source: "qrc:/image/battery.png"
                    width: telemetryrec.width * 0.05
                    height: telemetryrec.height * 0.4
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label {
                    id: batteryLabel
                    text: "0%"
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: telemetryrec.height * 0.4
                }
            }

            Row {
                spacing: 5
                Image {
                    source: "qrc:/image/speed.png"
                    width: telemetryrec.width * 0.05
                    height: telemetryrec.height * 0.4
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label {
                    id: speedLabel
                    text: "0 m/s"
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: telemetryrec.height * 0.4
                }
            }

            Row {
                spacing: 5
                Image {
                    source: "qrc:/image/altitude.png"
                    width: telemetryrec.width * 0.05
                    height: telemetryrec.height * 0.4
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label {
                    id: altitudeLabel
                    text: "0 m"
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: telemetryrec.height * 0.4
                }
            }

            Label {
                id: modeLabel
                text: "Unknown"
                color: "white"
                font.pixelSize: parent.height * 0.5
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Connections {
        target: serialAdaptor

        function onConnectedToPixhawk(portName){
            root.statusText = "Connected"
            connectionImage.source = "qrc:/image/greenchain.png"
        }

        function onUnintentionaldisconnect(){
            root.statusText = "Scanning..."
            connectionImage.source = "qrc:/image/redchain.png"

            modeLabel.text = "Unknown"
            batteryLabel.text = "0%"
            speedLabel.text = "0 m/s"
            altitudeLabel.text = "0 m"
            satelliteLabel.text = "0"
        }

        function onManualdisconnect(){
            modeLabel.text = "Unknown"
            batteryLabel.text = "0%"
            speedLabel.text = "0 m/s"
            altitudeLabel.text = "0 m"
            satelliteLabel.text = "0"
        }
    }


    Connections{
        target: mavlinkController

        function onHeartbeatUpdated(mode) {
            modeLabel.text = mode
        }

        function onBatteryUpdated(battery){
            batteryLabel.text = battery+ "v"
        }

        function onSpeedUpdated(speed){
            speedLabel.text = speed+"m/s"
        }

        function onAltitudeUpdated(altitude){
            altitudeLabel.text = altitude+ "m"
        }

        function onSatelliteNumberUpdated(satellite){
            satelliteLabel.text = satellite
        }
    }


}
