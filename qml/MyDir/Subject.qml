import QtQuick

Rectangle {
      id: _SubjectObj
      color: ColorsNSizes._PrimaryPurple
      anchors.horizontalCenter: parent.horizontalCenter
      width: parent.width / ColorsNSizes._SubjectScaleX
      //height:
      radius: 25

      property string _SubjectName: "Empty"
      property string _PlaceName: "N/A"
      property string _TeacherName: "N/A"
      property string _TypeName: "N/A"
      property string _TimeName: "9:00 - 10:30"
      property bool _IsBold: false
      property int _Lenght: 0
      property int _ScreenX: 0
      property int _ScreenY: 0
      height: (_SubjectName == "Empty" ? _SubjectText.height + 5 :  _SubjectText.height + _TeacherText.height + _PlaceText.height + _TypeText.height + 25)
      Text {
            id: _SubjectText
            anchors.top: parent.top
            anchors.topMargin: 5
            text: (_SubjectName == "Empty" ? "Нет пар" : qsTr(_SubjectName))
            font.pointSize: 18
            font.bold: _IsBold
            color: "black"
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: parent.width - 10
            wrapMode: Text.Wrap
      }
      Text {
            id: _TeacherText
            anchors.top: _SubjectText.bottom
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: qsTr(_TeacherName)
            visible: (_SubjectName == "Empty" ? false : true)
            font.pointSize: 16
            font.bold: false
            color: "black"
            wrapMode: Text.Wrap
            width: parent.width
      }
      Text {

            id: _TypeText
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: _TeacherText.bottom
            anchors.topMargin: 5
            text: "Тип занятия - " + _TypeName
            visible: (_SubjectName == "Empty" ? false : true)
            font.pointSize: 16
            font.bold: false
            color: ColorsNSizes._AttentionColor
            wrapMode: Text.Wrap
      }

      Text {
            id: _PlaceText
            anchors.top: _TypeText.bottom
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottomMargin: 2
            text: qsTr(_PlaceName)
            color: ColorsNSizes._AttentionColor
            font.pointSize: 16
            visible: (_SubjectName == "Empty" ? false : true)
            wrapMode: Text.Wrap

      }
      Text {
            id: _TimeText
            text: qsTr(_TimeName)
            anchors.left: _TypeText.right
            anchors.leftMargin: 25
            font.pointSize: 16
            anchors.top: _TeacherText.bottom
            anchors.topMargin: 5
            visible: (_SubjectName == "Empty" ? false : true)
            width: _PlaceText.width - 10
            wrapMode: Text.Wrap

      }
      // signal clicked
      // MouseArea {}
}
