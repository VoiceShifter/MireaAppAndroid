import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import "MyDir"
Item
{

    id: _MainPage
    property int _XResolution: parent.width
    property int _YResolution: parent.height

    // ColorsNSizes
    // {
    //     id: ColorsNSizes
    // }

    MyDrawer
    {
        id: _Drawer
        z:0
    }

    Rectangle
    {
        z: -1
        anchors.fill: parent
//        width: parent.width
//        height: parent.height
        color: ColorsNSizes._PrimaryBlue

    }


    Text {
        id: _Name
        text: "<-- Понедельник -->"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _StudentName.bottom
        anchors.topMargin: 20
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
        anchors.top: _Name.bottom
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
                       //_Loader.source = "MainPage5.qml"
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
                       //_Loader.source = "MainPage5.qml"
                       console.log("Clicked Subject button")
                }

            }
        }

    }
}

