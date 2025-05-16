import QtQuick

Rectangle {
      id: _SubjectObj
      color: ColorsNSizes._PrimaryPurple
      anchors.horizontalCenter: parent.horizontalCenter
      width: parent.width / ColorsNSizes._SubjectScaleX
      height: _SubjectText.height + _TeacherText.height + _PlaceText.height + _TypeText.height + 25
      radius: 25

      property string _SubjectName: ""
      property string _PlaceName: ""
      property string _TeacherName: ""
      property string _TypeName: ""
      property bool _IsBold: false
      property int _Lenght: 0
      property int _ScreenX: 0
      property int _ScreenY: 0

      Text {
            id: _SubjectText
            anchors.top: parent.top
            anchors.topMargin: 5
            text: qsTr(_SubjectName)
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
            font.pointSize: 16
            font.bold: false
            color: ColorsNSizes._AttentionColor
            wrapMode: Text.Wrap
            width: parent.width
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
            wrapMode: Text.Wrap
            width: parent.width
      }
      // signal clicked
      // MouseArea {}
}
