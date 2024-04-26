import QtQuick

Rectangle
{
    id: _SubjectObj
    color: "#DBE2EF"

    // ColorsNSizes
    // {
    //     id: ColorsNSizes
    // }

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width / ColorsNSizes._SubjectScaleX
    height: parent.height / ColorsNSizes._SubjectScaleY
    radius: 25

    property string _SubjectName: ""
    property bool _IsBold: false
    property int _Lenght: 0
    Text {
        text: qsTr(_SubjectName)
        font.pointSize: 24
        font.bold: _IsBold
        color: "black"
        y: 10
        x: 20
    }

    signal clicked()
    MouseArea
    {

    }
}
