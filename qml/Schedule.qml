import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import com.Schedule
import "MyDir"
import com.ServerCall
Item {

      id: _MainPage
      property int _XResolution: parent.width
      property int _YResolution: parent.height
      implicitHeight: 800
      implicitWidth: 400
      Schedule {
            id: _Schedule
      }
      ServerCall
      {
            id: _ServerCall
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
                  anchors.bottomMargin: 15
                  font.pointSize: ColorsNSizes._SmallFont
                  text: "Введите группу"
            }

            TextField {
                  id: _Group
                  width: parent.width / (ColorsNSizes._ButtonScaleX * 0.6)
                  font.pointSize: (ColorsNSizes._MediumFont * 0.8)
                  anchors.centerIn: parent
            }
            Rectangle {
                  id: _GroupField
                  anchors.top: _Group.bottom
                  anchors.topMargin: 25
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
                              console.log(_Group.text)
                              if (_Schedule._ChangeSchedule(_Group.text) == 1)
                              {
                                    _Popup.close()
                              }
                              else
                              {
                                    _Message.text = "Неверная группа"
                              }


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
            text: _Schedule._OddDays[_Schedule._CurrentDayInt]._Day
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
                        _Schedule._IncrementDay(-1)
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
                        _Schedule._IncrementDay(1)
                  }
            }
      }

      Text {
            id: _StudentName
            text: qsTr(_Schedule._UserName)
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
      property list<string> _TimesNames: ["9:00 - 10:30",
            "10:40 - 12:10", "12:40 - 14:10", "14:20 - 15:50",
            "16:20 - 17:50", "18:00 - 19:30"] //, "19:40 - 21:10"

      function _OddEven()
      {
            if (_Schedule._CurrentWeekNumber % 2 == 0)
            {
                  return _Schedule._EvenDays
            }
            else
            {
                  return _Schedule._OddDays
            }
      }

      ListView {
            spacing: 20
            z: -2
            id: _SubjectView
            width: parent.width
            height: parent.height - _Breaker.y - 5
            model: _TimesNames
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.top: _Breaker.bottom
            anchors.topMargin: 20
            displayMarginEnd: 170

            delegate: Subject {
                  id: _delegate

                  _IsBold: false
                  _SubjectName: _OddEven()[_Schedule._CurrentDayInt]._ItemNames[index] == undefined ? "Empty" : _OddEven()[_Schedule._CurrentDayInt]._ItemNames[index]
                  _PlaceName: _OddEven()[_Schedule._CurrentDayInt]._Places[index]
                  _TeacherName: _OddEven()[_Schedule._CurrentDayInt]._TeacherNames[index]
                  _TypeName: _OddEven()[_Schedule._CurrentDayInt]._Types[index]
                  _TimeName: modelData                  

                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              //_Loader.source = "MainPage5.qml"
                              console.log("Clicked subject button")
                              for (var i = 0; i < 12; i++)  {
                                    console.log(modelData)
                                }
                        }
                  }                  
            }
      }
}
