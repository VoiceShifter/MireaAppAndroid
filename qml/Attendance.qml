import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import "MyDir"
Item {

    property int _XResolution: parent.width
    property int _YResolution: parent.height
    // ColorsNSizes
    // {
    //     id: ColorsNSizes
    // }

    MyDrawer
    {
        id: _Drawer
        z:6
    }

    Rectangle
    {
        anchors.fill: parent
//        width: parent.width
//        height: parent.height
        color: "#7881AE"

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

    Text {
        id: _Name
        text: "Посещаемость"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: _Breaker.top
        anchors.bottomMargin: 10
        color: "white"

        font.bold: true
        font.pointSize: 28
    }

    Rectangle //breaker
    {
        id: _Breaker
        color: "white"
        width: parent.width - 60
        height: 5
        y: _YResolution / ColorsNSizes._BreakerScaleY
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }

    AttendanceLine
    {
        z: 5
        id: _Template
        _StudentName: ""
        anchors.top: _Breaker.bottom
        anchors.topMargin: 20
        _First: "+"
        _Second: "-"
        _Third: "?"
    }

    // ListView
    // {
    //     anchors.top: _Template.bottom
    //     width: parent.width
    //     model: _DataModel
    //     height: parent.height


    // }
    // ObjectModel
    // {
    //     id: _DataModel
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }
    //     AttendanceLine
    //     {
    //         _StudentName: "Username"
    //     }


    // }
}
