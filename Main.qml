import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.VirtualKeyboard 2.1
import QtWebEngine


Window {
    id: wifipage
    width: 800
    height: 480
    visible: true
    color: "#F0EAD6"
    title: "Wifi Manager"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20
        anchors.bottomMargin: 40
        // Title
        RowLayout{
        Text {
            text: "WiFi Manager"
            font.bold: true
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }
        Text {
            id: ip
            font.bold: true
            color: "grey"
            text: "NULL"
        }

        Timer {
            id: timeFetcher
            interval: 3000 // Update time every 2 seconds
            running: true
            repeat: true
            onTriggered: {
                ip.text = "IP: "+ wifi.cuurent_ip() /*+ net.netStatus*/
                console.log("ip in qml " + wifi.cuurent_ip() /*+ net.netStatus*/)
            }
        }
        }

        // WiFi SSID Input
        TextField {
            id: user
            Layout.alignment: Qt.AlignHCenter
            placeholderText: "Enter WiFi SSID"
            font.italic: true
            Layout.preferredHeight: 40
            Layout.preferredWidth: 300
        }

        // WiFi Password Input
        TextField {
            id: pass
            Layout.alignment: Qt.AlignHCenter
            placeholderText: "Enter WiFi Password"
            font.italic: true
            echoMode: TextInput.Password
            Layout.preferredHeight: 40
            Layout.preferredWidth: 300
        }
        Text{
            id: error_msg
            Layout.alignment: Qt.AlignHCenter
            color: "red"
            font.bold: true
        }

        RowLayout{
        Layout.alignment: Qt.AlignHCenter
        spacing: 20
        // Connect Button
        RoundButton {
            id: connect
            text: "Connect"
            font.bold: true
            palette.button: "black"
            Layout.preferredHeight: 40
            Layout.preferredWidth: 130
            onClicked: {
                // Handle connect logic
                if(user.text == "" && pass.text==""){
                    error_msg.text="Please enter wifi SSID and password."
                }
                else{
                     error_msg.text=""
                    connect.enabled=false
                    connect.text="connecting.."
                    timer.start()
                    console.log(user.text)
                    wifi.connect(user.text, pass.text)
                    console.log("Connect to SSID: " + user.text + " with Password: " + pass.text);
                }
                // TODO: Call backend function to connect to WiFi
            }
        }

        // Disconnect Button
        RoundButton {
            text: "Disconnect"
            font.bold: true
            palette.button: "black"
            Layout.preferredHeight: 40
            Layout.preferredWidth: 130
            onClicked: {
                // Handle disconnect logic
                if(user.text == "" && pass.text == ""){
                    error_msg.text="Please enter wifi SSID and password."
                }
                else{
                     error_msg.text=""
                wifi.disconnect()
                console.log("Disconnecting from WiFi");
                }
                // TODO: Call backend function to disconnect from WiFi
            }
        }

        Timer{
            id: timer
            interval: 10000
            running: true
            repeat: false
            onTriggered: {
                connect.enabled=true
                connect.text="Connect"
            }
        }
}

        // Scan Button
        RoundButton {
            text: "Scan for WiFi Networks"
            font.bold: true
            palette.button: "black"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 40
            Layout.preferredWidth: 280
            onClicked: {
                // Handle scan logic
                 wifi.interfacesChanged()
                wifilist.visible=true
                wifilist_Omouse.visible=true
                // popup.open()
                console.log("Scanning for WiFi Networks");
                // TODO: Call backend function to scan for WiFi networks
            }
        }

    }

MouseArea{
    id: wifilist_Omouse
    anchors.fill: parent
    visible: false
    onClicked: {
        wifilist.visible=false
        wifilist_Omouse.visible=false
    }
}

Rectangle {
    id:wifilist
    width: 300
    height: 300
    color: "white"
    border.color: "black"
    border.width: 2
    visible: false
    anchors.centerIn: parent
    Text{
        text:"Wifi List"
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
    }


    ListView {
        id: listView
        width: parent.width
        height: 230
        anchors.centerIn:parent
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds

        ListModel {
            id: stringListModel
        }

        Timer {
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                var ele = wifi.setwifi_name()
                stringListModel.clear()
                for (var i = 0; i < ele.length; ++i) {
                    stringListModel.append({ "text": ele[i] });
                }
            }
        }

        model: stringListModel

        delegate: Button {
            text: model.text
            height: 40
            width: 300
            onClicked: {
                user.text = model.text
                wifilist.visible=false
            }
        }

        ScrollBar.vertical: ScrollBar {}
    }
}

}
