import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import "MyDir"
import com.JsonParser 1.0
Item
{

    id: _MainPage
    property int _XResolution: parent.width
    property int _YResolution: parent.height

    // ColorsNSizes
    // {
    //     id: ColorsNSizes
    // }


    MyDrawer
    {
        id: _Drawer
        z:0
    }
    Popup
    {
        id: _Popup
        width: 250
        height: 250

        anchors.centerIn: parent
        Text
        {
            id: _Message
            anchors.horizontalCenter: _Group.horizontalCenter
            anchors.bottom: _Group.top
            text:"Введите группу"
        }

        TextField
        {
            id: _Group
            width: parent.width - 20
            anchors.centerIn: parent
        }
        Rectangle
        {
            id: _GroupField
            anchors.top: _Group.bottom

            width: 100
            height: 40
            color: ColorsNSizes._PrimaryPurple
            anchors.horizontalCenter: _Group.horizontalCenter
            Text
            {
                anchors.centerIn: parent
                text:"Подтвердить"
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    _Parser._SetGroup(_Group.text)
                    _Parser._GetReply()
                    _Parser._FillCurrentDayS()
                    _Popup.close()
                }
            }
        }
        Text {
            id: _Status
            text: qsTr("")
            anchors.top: _Login.bottom
            font.pointSize: 16
            anchors.horizontalCenter: _Login.horizontalCenter
        }
    }
    Rectangle
    {
        z: -3
        anchors.fill: parent
//        width: parent.width
//        height: parent.height
        color: ColorsNSizes._PrimaryBlue

    }


    Text {
        id: _WeekDay
        text: _Parser._CurrentDayString
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: _Breaker.top
        anchors.bottomMargin: 10
        color: "white"

        font.bold: true
        font.pointSize: 28
    }
    Text
    {
        id: _LeftArrow
        text: "<----"
        anchors.left: parent.left
        anchors.verticalCenter: _WeekDay.verticalCenter
        color: ColorsNSizes._AttentionColor
        font.bold: true
        font.pointSize: 28
        MouseArea
        {
            anchors.fill: parent

            onClicked:
            {
                _Parser._DecrementDay()
                _Parser._FillCurrentDayS()
            }
        }
    }
    Text
    {
        id: _RightArrow
        text: "---->"
        anchors.right: parent.right
        anchors.verticalCenter: _WeekDay.verticalCenter
        color: ColorsNSizes._AttentionColor
        font.bold: true
        font.pointSize: 28
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
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
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
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
    Rectangle
    {
        z: -1
        id: _Hider
        color: ColorsNSizes._PrimaryBlue
        anchors.bottom: _Breaker.bottom
        anchors.top: parent.top
        width: parent.width
    }

    ListView
    {
//            y: 80
        spacing: 40
        z: -2
        width: parent.width
        height: parent.height*2
        model: _Parser._ItemName
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: _Breaker.bottom
        anchors.topMargin: 40
        delegate: Subject
        {
            id: _delegate
            _IsBold: false
            _SubjectName: modelData
            _PlaceName: _Parser._Place[index]
            _TeacherName: _Parser._TeacherName[index]
            _TypeName: _Parser._Type[index]
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                       //_Loader.source = "MainPage5.qml"
                       console.log("Clicked subject button")
                }

            }
        }


    }


}


