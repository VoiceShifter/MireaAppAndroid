import QtQuick

Rectangle
{
    id: _SubjectObj
    color: ColorsNSizes._PrimaryPurple

    // ColorsNSizes
    // {
    //     id: ColorsNSizes
    // }

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width / ColorsNSizes._SubjectScaleX
    height: parent.parent.height / ColorsNSizes._SubjectScaleY
    Component.onCompleted:
    {
        console.log(parent.parent.height)
    }

    radius: 25

    property string _SubjectName: ""
    property string _PlaceName: ""
    property string _TeacherName: ""
    property string _TypeName: ""
    property bool _IsBold: false
    property int _Lenght: 0

    Text {
        id: _SubjectText
        anchors.top: parent.top
        anchors.topMargin: 10
        text: qsTr(_SubjectName)
        font.pointSize: 18
        font.bold: _IsBold
        color: "black"
        y: 10
        x: 10
        width: parent.width - 10
        wrapMode: Text.Wrap

    }
    Text
    {
        id: _TeacherText
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        text: qsTr(_TeacherName)
        font.pointSize: 16
        font.bold: false
        color: "black"
        y: 10
        x: 10
        wrapMode: Text.Wrap
        width: parent.width
    }
    Text
    {
        y: 10
        x: 120
        id: _TypeText
        anchors.verticalCenter: _PlaceText.verticalCenter
        anchors.bottomMargin: 2

        text: "Тип занятия - " + _TypeName
        font.pointSize: 16
        font.bold: false
        color: ColorsNSizes._AttentionColor
        wrapMode: Text.Wrap
        width: parent.width
    }

    Text {
        id: _PlaceText
        anchors.bottom: _TeacherText.top
        anchors.bottomMargin: 2
        text: qsTr(_PlaceName)
        color: ColorsNSizes._AttentionColor
        font.pointSize: 16
        x: 10; y: 10;
        wrapMode: Text.Wrap
        width: parent.width
    }


    signal clicked()
    MouseArea
    {

    }
}
