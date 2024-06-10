import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import com.JsonParser 1.0
import "MyDir"
Item {

    property int _XResolution: parent.width
    property int _YResolution: parent.height
    // ColorsNSizes
    // {
    //     id: ColorsNSizes
    // }
    function _SaveToFile(n)
    {
        _Parser._StartCycle()
        for(var _Iterator in _List.contentItem.children)
        {
            var _Shorter = _List.contentItem.children[_Iterator]
            console.log(_Shorter._StudentName)
            var _Results = _Shorter._First !== "" ? _Shorter._First : (_Shorter._Second !== "" ? _Shorter._Second : _Shorter._Third);
            console.log(_Results)
            _Parser._IterateCycle(_Shorter._StudentName, _Results)
        }
        _Parser._SaveResults()
    }
    MyDrawer
    {
        id: _Drawer
        z:6
    }

    Rectangle
    {
        anchors.fill: parent
//        width: parent.width
//        height: parent.height
        color: ColorsNSizes._PrimaryBlue

    }

    Text {
        id: _StudentName
        text: qsTr("username")
        color: "white"
        anchors.topMargin: 20
        anchors.right: parent.right
        font.pointSize: 24
        font.bold: false
    }

    Text {
        id: _Name
        text: "Посещаемость"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: _Breaker.top
        anchors.bottomMargin: 10
        color: "white"

        font.bold: true
        font.pointSize: 28
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

    AttendanceLine
    {
        z: 5
        id: _Template
        _StudentName: ""
        anchors.top: _Breaker.bottom
        anchors.topMargin: 20
        _First: "+"
        _Second: "-"
        _Third: "?"
    }

    ListView
    {
        id: _List
        anchors.top: _Template.bottom
        width: parent.width
        model: _Parser._Students
        height: parent.height
        delegate:
            AttendanceLine
        {
            id: _Delegat
            _StudentName:modelData
        }
}
    Rectangle
    {
        id: _SaveButton
        width: 100
        height: 50
        color: ColorsNSizes._CoolGray
        radius: 60
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        Text {

            text: qsTr("Отправить")
            font.bold: true
            font.pointSize: 16
            anchors.centerIn: parent
            color: ColorsNSizes._LightBlue
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                _SaveToFile(_Parser._GetAmountStudents())
            }
        }

    }

}
