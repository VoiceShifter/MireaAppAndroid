import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import "MyDir"
Item {

    property int _XResolution: parent.width
    property int _YResolution: parent.height

    ColorsNSizes
    {
        id: _ColorsNSizes
    }

    Rectangle
    {
        width: parent.width
        height: parent.height

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
            radius: 90
            //<------------------------------------- Main Login screen
            Rectangle //Icon holder
            {

                id: _Ico
                radius: 180
                height: _XResolution * _ColorsNSizes._IconHolderScale
                width: height
                color: "#DBE2EF"
                y: 20

                Image
                {
                    source: "MyDir/Icons/home.svg"
                    sourceSize.width: _XResolution * _ColorsNSizes._IconHolderScale
                    sourceSize.height: _XResolution * _ColorsNSizes._IconHolderScale
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
                anchors.top: login_text.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle
                {
                    radius: 60
                    implicitWidth: _XResolution / _ColorsNSizes._TextFieldScale
                    implicitHeight: 40
                    color: control.enabled ? "transparent" : "#7881ae"
                    border.color: control.enabled ? "#dbe2ef" : "transparent"
                }

            }

            TextField
            {
                id: passwordField
                placeholderText: "Password"
                echoMode: TextInput.Password
                anchors.top: loginField.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle
                {
                    radius: 60
                    implicitWidth: _XResolution / _ColorsNSizes._TextFieldScale
                    implicitHeight: 40
                    color: control.enabled ? "transparent" : "#7881ae"
                    border.color: control.enabled ? "#dbe2ef" : "transparent"
                }
            }
            Rectangle
            {
                id: _LoginButton
                radius: 20
                width: _XResolution / _ColorsNSizes._ButtonScaleX
                height: _YResolution / _ColorsNSizes._ButtonScaleY
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
                        _Loader.source = "Schedule.qml"

                    }


                }

            }
        }
    }
}
