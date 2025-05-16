import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import com.Schedule
import "MyDir"

Item {

      id: _MainPage
      property int _XResolution: parent.width
      property int _YResolution: parent.height
      implicitHeight: 800
      implicitWidth: 400
      Schedule {
            id: _Schedule
      }

      MyDrawer {
            id: _Drawer
            z: 0
      }
      Popup {
            id: _Popup
            width: 250
            height: 250

            anchors.centerIn: parent
            Text {
                  id: _Message
                  anchors.horizontalCenter: _Group.horizontalCenter
                  anchors.bottom: _Group.top
                  text: "Введите группу"
            }

            TextField {
                  id: _Group
                  width: parent.width - 20
                  anchors.centerIn: parent
            }
            Rectangle {
                  id: _GroupField
                  anchors.top: _Group.bottom

                  width: 100
                  height: 40
                  color: ColorsNSizes._PrimaryPurple
                  anchors.horizontalCenter: _Group.horizontalCenter
                  Text {
                        anchors.centerIn: parent
                        text: "Подтвердить"
                  }

                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              _Parser._SetGroup(_Group.text)
                              _Parser._GetReply()
                              _Parser._FillCurrentDayS()
                              _Popup.close()
                        }
                  }
            }
      }
      Rectangle {
            z: -3
            anchors.fill: parent
            //        width: parent.width
            //        height: parent.height
            color: ColorsNSizes._PrimaryBlue
      }

      Text {
            id: _WeekDay
            text: _Schedule._Days[2]._Day
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: _Breaker.top
            anchors.bottomMargin: 10
            color: "white"

            font.bold: true
            font.pointSize: 28
      }
      Text {
            id: _LeftArrow
            text: "<----"
            anchors.left: parent.left
            anchors.verticalCenter: _WeekDay.verticalCenter
            color: ColorsNSizes._AttentionColor
            font.bold: true
            font.pointSize: 28
            MouseArea {
                  anchors.fill: parent

                  onClicked: {
                        _Parser._DecrementDay()
                        _Parser._FillCurrentDayS()
                  }
            }
      }
      Text {
            id: _RightArrow
            text: "---->"
            anchors.right: parent.right
            anchors.verticalCenter: _WeekDay.verticalCenter
            color: ColorsNSizes._AttentionColor
            font.bold: true
            font.pointSize: 28
            MouseArea {
                  anchors.fill: parent
                  onClicked: {
                        _Parser._IncrementDay()
                        _Parser._FillCurrentDayS()
                  }
            }
      }

      Text {
            id: _StudentName
            text: qsTr("username")
            color: "white"
            anchors.topMargin: 20
            anchors.right: parent.right
            font.pointSize: 24
            font.bold: false
            MouseArea {
                  anchors.fill: parent
                  onClicked: {
                        _Popup.open()
                  }
            }
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
      Rectangle {
            z: -1
            id: _Hider
            color: ColorsNSizes._PrimaryBlue
            anchors.bottom: _Breaker.bottom
            anchors.top: parent.top
            width: parent.width
      }

      ListView {
            //            y: 80
            spacing: 40
            z: -2
            width: parent.width
            height: parent.height - _Breaker.y - 5
            contentHeight: height
            model: _Schedule._Days[0]._ItemNames
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.top: _Breaker.bottom
            anchors.topMargin: 40
            //reuseItems: True what?


            //cacheBuffer: 5
            delegate: Subject {
                  id: _delegate
                  _IsBold: false
                  _SubjectName: modelData
                  _PlaceName: _Schedule._Days[0]._Places[index]
                  _TeacherName: _Schedule._Days[0]._TeacherNames[index]
                  _TypeName: _Schedule._Days[0]._Types[index]
                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              //_Loader.source = "MainPage5.qml"
                              console.log("Clicked subject button")
                              for (var i = 0; i < 12; i++)  {
                                    console.log(_Schedule._Days[0]._Places[i])
                                }
                        }
                  }
            }
      }
}
