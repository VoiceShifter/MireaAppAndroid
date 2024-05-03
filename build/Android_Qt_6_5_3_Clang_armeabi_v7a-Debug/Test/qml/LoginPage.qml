import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import "MyDir"
import com.SocketCall 1.0

Item {

    property int _XResolution: parent.width
    property int _YResolution: parent.height

    Rectangle
    {
        width: parent.width
        height: parent.height
        Popup
        {
            id: _Popup
            width: parent.width / ColorsNSizes._SubjectScaleX
            height: parent.height / ColorsNSizes._SubjectScaleY / 0.5
            anchors.centerIn: parent

            TextField
            {
                id: _Ip
                width: parent.width - 20
                anchors.centerIn: parent
            }
            Rectangle
            {
                id: _Login
                anchors.top: _Ip.bottom

                width: 80
                height: 40
                color: ColorsNSizes._PrimaryPurple
                anchors.horizontalCenter: _Ip.horizontalCenter

                Socket
                {
                    id: _Socket
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {

                        _Socket._CheckForIp(_Ip.text)
                        _Socket._Call(loginField.text, passwordField.text) === true ? _Loader.source = "Schedule.qml" : _Status.text = "Error"
                        console.log("Log")
                    }
                }
            }
            Text {
                id: _Status
                text: qsTr("")
                anchors.top: _Login.bottom
                font.pointSize: 16
                anchors.horizontalCenter: _Login.horizontalCenter
            }
        }

        color: "#7881AE"
        Text {
            id: _Logo
            text: qsTr("MIREA\nAPP")

            font.pointSize: 64/*
            anchors.topMargin: 20
            anchors.centerIn: parent*/

            y: 80
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter

            font.bold: true

            }
        Rectangle //main item
        {
            height: parent.height / 1.4
            width: parent.width
            color: "#112D4E"
            y: parent.height / 2.5
            radius: 60
            //<------------------------------------- Main Login screen


            Rectangle //Icon holder
            {

                id: _Ico
                radius: 180
                height: _XResolution * ColorsNSizes._IconHolderScale
                width: height
                color: "#DBE2EF"
                y: 20

                Image
                {
                    source: "MyDir/Icons/home.svg"
                    sourceSize.width: _XResolution * ColorsNSizes._IconHolderScale
                    sourceSize.height: _XResolution * ColorsNSizes._IconHolderScale
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.bottomMargin: 5
                }

                anchors.horizontalCenter: parent.horizontalCenter


            }
            Text {
                id: login_text
                text: qsTr("Login")
                font.pointSize: 48
                font.bold: true
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: _Ico.bottom

            }
            TextField
            {

                id: loginField
                placeholderText: "Login"
                placeholderTextColor: "red"
                anchors.top: login_text.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter

                background: Rectangle
                {
                    radius: 60
                    implicitWidth: _XResolution / ColorsNSizes._TextFieldScale
                    implicitHeight: 20
                    color: control.enabled ? "transparent" : "#7881ae"
                    border.color: control.enabled ? "#dbe2ef" : "transparent"
                }

            }

            TextField
            {
                id: passwordField
                placeholderText: "Password"
                placeholderTextColor: "red"

                echoMode: TextInput.Password
                anchors.top: loginField.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle
                {
                    radius: 60
                    implicitWidth: _XResolution / ColorsNSizes._TextFieldScale
                    implicitHeight: 20
                    color: control.enabled ? "transparent" : "#7881ae"
                    border.color: control.enabled ? "#dbe2ef" : "transparent"
                }
            }
            Rectangle
            {
                id: _LoginButton
                radius: 20
                width: _XResolution / ColorsNSizes._ButtonScaleX
                height: _YResolution / ColorsNSizes._ButtonScaleY
                Text {
                    text: qsTr("ENTER")
                    font.pointSize: 24
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#112D4E"
                }
                color: "#BBD0FF"
                anchors.horizontalCenter: parent.horizontalCenter

                anchors.topMargin: 20
                anchors.top: passwordField.bottom
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        //_Popup.open()
                        _Loader.source = "Schedule.qml"

                    }


                }

            }
        }
    }
}
