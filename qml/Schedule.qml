import QtQuick
import "MyDir"
Item
{

    id: _MainPage
    property int _XResolution: parent.width
    property int _YResolution: parent.height

    ColorsNSizes
    {
        id: _Colors
    }

    MyDrawer
    {
        id: _Drawer
    }

    Rectangle
    {
        z: -1
        anchors.fill: parent
//        width: parent.width
//        height: parent.height
        color: "#7881AE"

    }
    Rectangle
    {
        z:7
        id: _Menu
        radius: 180
        color: "#112D4E"
        height: 100
        width: 100
        y:20
        x:20
        Text
        {
            text: qsTr("+")
            font.pointSize: 36
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -5
        }


    }
    MouseArea
    {
        anchors.fill: _Menu
        onClicked:
        {
            console.log("Button clicked")
            _Drawer.position == 0 ? _Drawer.open(): _Drawer.close()

        }
    }

    Text {
        id: _Name
        text: qsTr("<-- Понедельник -->")
        anchors.horizontalCenter: _Breaker.horizontalCenter
        anchors.bottom: _Breaker.top
        anchors.bottomMargin: 10
        color: "white"

        font.bold: true
        font.pointSize: 28

    }
    Text {
        id: _StudentName
        text: qsTr("username")
        color: "white"
        anchors.topMargin: 20
        anchors.right: parent.right
        font.pointSize: 24
        font.bold: false
    }

    Rectangle //breaker
    {
        id: _Breaker
        color: "white"
        width: parent.width - 60
        height: 5
        anchors.top: _Menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }

    Column
    {
//            y: 80
        spacing: 40

        width: parent.width


        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: _Breaker.bottom
        anchors.topMargin: 40
        Subject
        {
            id: _First
            _IsBold: false
            _SubjectName: "Кафедра ---\nЛинейная математика"
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                       _Loader.source = "MainPage5.qml"
                       console.log("Clicked subject button")
                }

            }
        }
        Subject
        {
            id: _Second
            _IsBold: false
            _SubjectName: "Кафедра ---\nЛинейная математика"
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                       _Loader.source = "MainPage5.qml"
                       console.log("Clicked Subject button")
                }

            }
        }

    }
}

