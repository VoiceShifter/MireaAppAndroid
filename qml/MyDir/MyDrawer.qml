import QtQuick
import QtQuick.Controls
import com.Reseter 1.0

Drawer {
      id: _Drawer
      width: _XResolution * 0.66
      height: _YResolution

      readonly property int _ButtonHeight: _YResolution / ColorsNSizes._SideButtonScaleY
      Reseter {
            id: _Reseter
      }

      Row {
            spacing: 10
            height: _YResolution / ColorsNSizes._SliderScaleY
            y: 10
            width: parent.width

            Switch {
                  id: _Controll

                  checked: ColorsNSizes._SwitchState
                  indicator: Rectangle {
                        implicitHeight: 32
                        implicitWidth: 56
                        x: _Controll.leftPadding
                        y: parent.height / 2 - height / 2
                        radius: width / 2
                        color: _Controll.checked ? ColorsNSizes._PrimaryBlue : ColorsNSizes._PrimaryPurple
                        border.width: _Controll.checked ? 2 : 1
                        border.color: _Controll.checked ? ColorsNSizes._PrimaryGray : ColorsNSizes._SecondaryBlue

                        Rectangle {
                              x: _Controll.checked ? (parent.width - width) - 2 : 2
                              width: 28
                              height: 28
                              radius: height / 2
                              color: _Controll.checked ? "#FFFFFF" : "#7a859b"
                              anchors.verticalCenter: parent.verticalCenter
                        }
                  }

                  contentItem: Label {
                        color: "black"
                        text: ColorsNSizes._ThemeName
                        font.pixelSize: 16
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: parent.right
                  }

                  onToggled: {
                        if (checked) {
                              ColorsNSizes._CurrentTheme = ColorsNSizes.themes._Light
                              ColorsNSizes._SwitchState = true
                        } else {
                              ColorsNSizes._CurrentTheme = ColorsNSizes.themes._Dark
                              ColorsNSizes._SwitchState = false
                        }
                  }
            }
      }

      Rectangle
      {
            id: _Background
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height
            z: -1
            color: ColorsNSizes._PrimaryPurple

      Column {
            id: _Column
            spacing: -1
            width: parent.width


            anchors.top: parent.top
            anchors.topMargin: 140

            Rectangle {
                  width: parent.width
                  border.color: "black"
                  border.width: 1
                  height: _ButtonHeight
                  color: ColorsNSizes._PrimaryGray
                  Text {
                        id: _ToSchedule
                        text: qsTr("Расписание")
                        font.pointSize: Math.round((parent.width + parent.height)/20)
                        color: "black"
                        anchors.centerIn: parent
                  }
                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              _Loader.source = "Schedule.qml"
                              _Drawer.close()
                              console.log("Clicked Schedule button")
                        }
                  }
            }
            Rectangle {
                  width: parent.width
                  border.color: "black"
                  border.width: 1
                  height: _ButtonHeight
                  color: ColorsNSizes._PrimaryGray
                  Text {
                        id: _ToTeachers
                        text: qsTr("Преподователи")
                        font.pointSize: Math.round((parent.width + parent.height)/20)
                        color: "black"
                        anchors.centerIn: parent
                  }
                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              _Loader.source = "Teachers.qml"
                              _Drawer.close()
                              console.log("Clicked Teachers button")
                        }
                  }
            }
            Rectangle {
                  width: parent.width
                  border.color: "black"
                  border.width: 1
                  height: _ButtonHeight
                  color: ColorsNSizes._PrimaryGray
                  Text {
                        id: _Attendance
                        text: qsTr("Посещаемость")
                        font.pointSize: Math.round((parent.width + parent.height)/20)
                        color: "black"
                        anchors.centerIn: parent
                  }
                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              _Loader.source = "Attendance.qml"
                              _Drawer.close()
                              console.log("Clicked Attendance button")
                        }
                  }
            }
            Rectangle {
                  width: parent.width
                  border.color: "black"
                  border.width: 1

                  height: _ButtonHeight
                  color: ColorsNSizes._PrimaryGray
                  Text {
                        id: _ToExit
                        text: qsTr("Выйти")
                        font.pointSize: Math.round((parent.width + parent.height)/20)
                        color: "red"
                        anchors.centerIn: parent
                  }
                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              _Reseter._Reset()
                              _Loader.source = "LoginPage.qml"
                              _Drawer.close()
                              console.log("Clicked LoginButton")
                        }
                  }
            }
      }
      }
}
