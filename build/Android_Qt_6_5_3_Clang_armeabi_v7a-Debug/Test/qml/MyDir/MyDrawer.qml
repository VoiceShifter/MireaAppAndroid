import QtQuick
import QtQuick.Controls

Drawer {
    id: _Drawer
    width: _XResolution * 0.66
    height: _YResolution
    ColorsNSizes
    {
        id: _ColorsNSizes
    }

    Rectangle
    {
        z:6

        color: _ColorsNSizes._PowderBlue
        border.color: "black"
        border.width: 2
        anchors.fill : parent
        Column
        {
            spacing: -1
            width: parent.width

            anchors.top: parent.top
            anchors.topMargin: 140

            Rectangle
            {
                width: parent.width - 1
                border.color: "black"
                border.width: 1
                height: _ColorsNSizes._SideButtonHeight
                color: _ColorsNSizes._CoolGray
                Text {
                    id: _ToSchedule
                    text: qsTr("Schedule")
                    font.pointSize: _ColorsNSizes._MediumFont
                    color: "black"
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                           _Loader.source = "../MainPage2.qml"
                           console.log("Clicked Attendance button")
                    }

                }
            }
            Rectangle
            {
                width: parent.width - 1
                border.color: "black"
                border.width: 1
                height: _ColorsNSizes._SideButtonHeight
                color: _ColorsNSizes._CoolGray
                Text {
                    id: _ToTeachers
                    text: qsTr("Teachers")
                    font.pointSize: _ColorsNSizes._MediumFont
                    color: "black"
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                           _Loader.source = "../Teachers.qml"
                           console.log("Clicked Teachers button")
                    }

                }

            }
            Rectangle
            {
                width: parent.width - 1
                border.color: "black"
                border.width: 1
                height: _ColorsNSizes._SideButtonHeight
                color: _ColorsNSizes._CoolGray
                Text {
                    id: _Attendance
                    text: qsTr("Attendance")
                    font.pointSize: _ColorsNSizes._MediumFont
                    color: "black"
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                           _Loader.source = "../MainPage4.qml"
                           console.log("Clicked Attendance button")
                    }

                }
            }
        }

    }


}
