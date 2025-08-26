import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import com.SubjectSystem 1.0
import "MyDir"


Item {
      id: _MainPage
      property int _XResolution: parent.width
      property int _YResolution: parent.height
      implicitHeight: 800
      implicitWidth: 400
      Rectangle {
            z: -3
            anchors.fill: parent
            //        width: parent.width
            //        height: parent.height
            color: ColorsNSizes._PrimaryBlue
      }
      MyDrawer {
            id: _Drawer
            z: 0
      }
      SubjectSystem
      {
            id: _System
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

      Text {
            id: _StudentName
            text: qsTr(_System._UserName)
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
      Text {
            id: _Name
            text: _System._SubjectName
            wrapMode: Text.Wrap
            font.pointSize: ColorsNSizes._SmallFont + 8
            horizontalAlignment: Text.AlignHCenter
            width: _Breaker.width
            anchors.top: _StudentName.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: _Breaker.horizontalCenter
      }
      ListView {
            spacing: 20
            z: -2
            id: _SubjectView
            width: parent.width
            height: parent.height - _Breaker.y - 5
            model: _System._FileNames
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.top: _Breaker.bottom
            anchors.topMargin: 20
            displayMarginEnd: 170
            delegate: File
            {
                  id: _delegate
                  _FileName: modelData
                  MouseArea
                  {
                        anchors.fill: parent
                        onClicked:
                        {
                              _System._ItemPressed(_delegate._FileName)
                        }

                  }
            }


      }

}
