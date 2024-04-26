import QtQuick
import QtQuick.Controls

Drawer {
    id: _Drawer
    width: _XResolution * 0.66
    height: _YResolution
    // ColorsNSizes
    // {
    //     id: ColorsNSizes
    // }
    // Overlay.modal: Rectangle {
    //                   color: "transparent"
    //               }

    readonly property int _ButtonHeight : _YResolution / ColorsNSizes._SideButtonScaleY
    Column
    {
        spacing: -1
        width: parent.width

        anchors.top: parent.top
        anchors.topMargin: 140

        Rectangle
        {
            width: parent.width
            border.color: "black"
            border.width: 1
            height: _ButtonHeight
            color: ColorsNSizes._CoolGray
            Text {
                id: _ToSchedule
                text: qsTr("Schedule")
                font.pointSize: ColorsNSizes._MediumFont
                color: "black"
                anchors.centerIn: parent
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    _Loader.source = "Schedule.qml"
                    _Drawer.close()
                    console.log("Clicked Schedule button")
                }

            }
        }
        Rectangle
        {
            width: parent.width
            border.color: "black"
            border.width: 1
            height: _ButtonHeight
            color: ColorsNSizes._CoolGray
            Text {
                id: _ToTeachers
                text: qsTr("Teachers")
                font.pointSize: ColorsNSizes._MediumFont
                color: "black"
                anchors.centerIn: parent
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                       _Loader.source = "Teachers.qml"
                     _Drawer.close()
                       console.log("Clicked Teachers button")
                }

            }

        }
        Rectangle
        {
            width: parent.width
            border.color: "black"
            border.width: 1
            height: _ButtonHeight
            color: ColorsNSizes._CoolGray
            Text {
                id: _Attendance
                text: qsTr("Attendance")
                font.pointSize: ColorsNSizes._MediumFont
                color: "black"
                anchors.centerIn: parent
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                       _Loader.source = "Attendance.qml"
                     _Drawer.close()
                       console.log("Clicked Attendance button")
                }

            }

        }

}


}
