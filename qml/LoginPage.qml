import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import "MyDir"
import com.SocketCall 1.0
import com.ServerCall 1.0
import QtQuick.Controls.Basic
Item {

    property int _XResolution: parent.width //480  //debug
    property int _YResolution: parent.height //1000 //debug
    Component.onCompleted: {
        console.log(_XResolution, _YResolution)
        console.log("this is a resolutions")
    }
    ServerCall
    {
          id: _ServerCall
    }

    Rectangle
    {
        width: parent.width
        height: parent.height
        /*onWidthChanged:
        {
            console.log("Size changed")
        }*/ //debug

        color: "#7881AE"
        Text {
            id: _Logo
            text: qsTr("MIREA\nAPP")

            font.pointSize: 64 /*
            anchors.topMargin: 20
            anchors.centerIn: parent*/

            anchors.bottom: _MainItem.top
            anchors.bottomMargin: _YResolution * (ColorsNSizes._IconHolderScale - 0.1)
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter

            font.bold: true

            }
        Rectangle //main item
        {
            id: _MainItem
            height: parent.height / 1.4
            width: parent.width
            color: "#112D4E"
            y: parent.height / 2.5
            radius: 60
            //<------------------------------------- Main Login screen
            Component.onCompleted:
            {
                Qt.callLater(setSize)
            }
            function setSize()
            {
                _Ico.height = _XResolution * ColorsNSizes._IconHolderScale //debug
                _Ico.width = _Ico.height
            }


            Rectangle //Icon holder
            {
                id: _Ico
                anchors.top: parent.top
                anchors.topMargin: 20
                radius: 180
                height: _XResolution * ColorsNSizes._IconHolderScale
                width: height


                onHeightChanged:
                {
                    if (height > 200)
                    {
                        _Ico.height = 200
                        _Ico.width = Ico.height
                    }
                }

                // }
                // onWidthChanged:
                // {
                //     if (width > 100)
                //     {
                //         height: 100
                //         console.log(height)
                //     }
                // }


                color: "#DBE2EF"

                Image
                {
                    source: "MyDir/Icons/home.svg"
                    sourceSize.width: parent.height
                    sourceSize.height: parent.width
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
            TextField //login field
            {

                id: loginField
                placeholderText: "Login"
                placeholderTextColor: "red"

                anchors.top: login_text.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: _XResolution / ColorsNSizes._TextFieldScale
                onWidthChanged:
                {
                    if (loginField.width > 400)
                    {
                        loginField.width = 400
                        passwordField.width = 400
                    }
                    if(_LoginButton.width > 300)
                    {
                          _LoginButton.width = 300
                    }
                }
                background: Rectangle
                {
                    radius: 60
                    implicitWidth: _XResolution / ColorsNSizes._TextFieldScale
                    implicitHeight: _YResolution * ColorsNSizes._TextFieldScaleY
                    //color: control.enabled ? "transparent" : "#7881ae" debug
                    //border.color: control.enabled ? "#dbe2ef" : "transparent"
                }
            }

            TextField //password field
            {
                id: passwordField
                placeholderText: "Password"
                placeholderTextColor: "red"

                //echoMode: TextInput.Password debug - to size field
                anchors.top: loginField.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: _XResolution / ColorsNSizes._TextFieldScale

                background: Rectangle
                {
                    radius: 60
                    implicitWidth: _XResolution / ColorsNSizes._TextFieldScale
                    implicitHeight: _YResolution * ColorsNSizes._TextFieldScaleY
                    //color: control.enabled ? "transparent" : "#7881ae" debug
                    //border.color: control.enabled ? "#dbe2ef" : "transparent"
                }

            }
            Rectangle //login button
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
                        if (_ServerCall._LoginInto(loginField.text, passwordField.text))
                        {

                              console.log("Login succesful")
                              _Loader.source = "Schedule.qml"
                        }
                        else
                        {
                              console.log("Login failed")
                        }
                    }
                }
            }
        }
    }
}
