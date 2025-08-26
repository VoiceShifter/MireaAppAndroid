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
            Component.onCompleted: {
                  if (_Schedule._ErrorMessage != "") {
                        _ErrorPopup.open()
                  }
            }
      }

      MyDrawer {
            id: _Drawer
            z: 0
      }

      Popup {
            id: _ErrorPopup
            enter: Transition {
                  NumberAnimation {
                        property: "opacity"
                        from: 0.0
                        to: 1.0
                  }
            }
            exit: Transition {
                  NumberAnimation {
                        property: "opacity"
                        from: 1.0
                        to: 0.0
                  }
            }
            width: parent.width / 2
            height: parent.height / 6
            background: Rectangle {
                  anchors.fill: parent
                  radius: 30
                  color: ColorsNSizes._PrimaryPurple
                  border.color: ColorsNSizes._SecondaryBlue
                  border.width: 3
            }
            anchors.centerIn: parent
            Text {
                  id: _ErrorText
                  anchors.horizontalCenter: _ErrorPopup.horizontalCenter
                  anchors.top: parent.top
                  anchors.topMargin: 10
                  horizontalAlignment: Text.AlignHCenter
                  width: parent.width
                  wrapMode: Text.Wrap
                  font.pointSize: ColorsNSizes._SmallFont
                  text: _Schedule._ErrorMessage
            }
            Rectangle {
                  anchors.bottom: parent.bottom
                  anchors.horizontalCenter: parent.horizontalCenter
                  anchors.bottomMargin: 15
                  width: parent.width / 2
                  height: parent.height / 3
                  radius: 30
                  color: ColorsNSizes._PrimaryBlue
                  Text {
                        text: qsTr("OK")
                        font.pointSize: ColorsNSizes._SmallFont
                        anchors.centerIn: parent
                  }
                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              console.log("popup closed")
                              _ErrorPopup.close()
                        }
                  }
            }
      }

      Popup {
            id: _Popup
            width: parent.width / 2
            height: parent.height / 6
            background: Rectangle {
                  anchors.fill: parent
                  radius: 30
                  color: ColorsNSizes._PrimaryPurple
                  border.color: ColorsNSizes._SecondaryBlue
                  border.width: 3
            }
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
                  anchors.bottom: parent.bottom
                  anchors.bottomMargin: 5
                  width: 100
                  height: 40
                  radius: 30
                  color: ColorsNSizes._SecondaryBlue
                  anchors.horizontalCenter: _Group.horizontalCenter
                  Text {
                        anchors.centerIn: parent
                        text: "Подтвердить"
                  }

                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              console.log(_Group.text)
                              var Results = _Schedule._ChangeSchedule(
                                                _Group.text)
                              if (Results == 1) {
                                    _Popup.close()
                              } else if (Results == 2) {
                                    _Message.text = "Ошибка сервера"
                              } else {
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

            color: "white"
            anchors.top: _CurrentGroup.bottom
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
      Text {
            id: _CurrentGroup
            text: qsTr(_Schedule._QCurrentGroup)
            color: "white"
            anchors.top: _StudentName.bottom
            anchors.topMargin: -5
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
            anchors.top: _WeekDay.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
      }
      Rectangle {
            z: -1
            id: _Hider
            color: ColorsNSizes._PrimaryBlue
            anchors.bottom: _Breaker.bottom
            anchors.top: parent.top
            width: parent.width
      }
      property list<string> _TimesNames: ["9:00 - 10:30", "10:40 - 12:10", "12:40 - 14:10", "14:20 - 15:50", "16:20 - 17:50", "18:00 - 19:30"] //, "19:40 - 21:10"

      function _OddEven() {
            if (_Schedule._CurrentWeekNumber % 2 == 0) {
                  return _Schedule._EvenDays
            } else {
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
                  _SubjectName: _OddEven(
                                      )[_Schedule._CurrentDayInt]._ItemNames[index]
                                == undefined ? "Empty" : _OddEven(
                                                     )[_Schedule._CurrentDayInt]._ItemNames[index]
                  _PlaceName: _OddEven(
                                    )[_Schedule._CurrentDayInt]._Places[index]
                  _TeacherName: _OddEven(
                                      )[_Schedule._CurrentDayInt]._TeacherNames[index]
                  _TypeName: _OddEven()[_Schedule._CurrentDayInt]._Types[index]
                  _TimeName: modelData

                  MouseArea {
                        anchors.fill: parent
                        onClicked: {
                              //_Loader.source = "MainPage5.qml"
                              console.log(_delegate._SubjectName)
                              if (_delegate._SubjectName != "Empty")
                              {
                                    if (_Schedule._SubjectClicked(
                                                      _delegate._SubjectName) == 0) {
                                          _ErrorPopup.open()
                                    } else {
                                          _Loader.source = "SubjectPage.qml"
                                          console.log("Open subject")
                                    }
                              }
                        }
                  }
            }
      }
}
