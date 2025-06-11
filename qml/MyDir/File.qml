import QtQuick

Rectangle {
      id: _FileObj
      color: ColorsNSizes._PrimaryPurple
      anchors.horizontalCenter: parent.horizontalCenter
      width: parent.width / ColorsNSizes._SubjectScaleX
      height: _FileText.height + 5
      radius: 25
      property string _FileName: "Empty"
      property bool _IsBold: false
      property int _Lenght: 0
      property int _ScreenX: 0
      property int _ScreenY: 0
      Text {
            id: _FileText
            anchors.top: parent.top
            anchors.topMargin: 5
            text: _FileName
            font.pointSize: 18
            font.bold: _IsBold
            color: "black"
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: parent.width - 10
            wrapMode: Text.Wrap
      }

}
