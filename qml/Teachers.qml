import QtQuick
import QtLocation 5.15
import QtQuick.Controls
import "MyDir"
import com.Searcher 1.0
Item
{
    property int _XResolution: parent.width
    property int _YResolution: parent.height
    Rectangle
    {



        width: parent.width
        height: parent.height

        color: ColorsNSizes._PrimaryBlue

        MyDrawer
        {
            id: _Drawer
            z: 0
        }

        Text
        {
            id: _Name
            text: qsTr("Преподаватели")
            anchors.horizontalCenter: _Breaker.horizontalCenter
            anchors.bottom: _Breaker.top
            anchors.bottomMargin: 10
            color: "white"
            font.bold: true
            font.pointSize: 28
        }
        Item
        {
            id: _Menu
            y:20
            x:20
        }

        Searcher
        {
            id: _Searcher
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


        TextField
        {
            z:1
            id: _SearchField
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 100
            anchors.top: _Breaker.bottom
            anchors.topMargin: 40
            color: "white"
            text: _Searcher.Cache
        }



        Rectangle
        {
            id: _SearchButton
            width: _XResolution / ColorsNSizes._ButtonScaleX
            height: _YResolution / ColorsNSizes._ButtonScaleY
            radius: 60
            anchors.horizontalCenter:  parent.horizontalCenter
            anchors.top: _SearchField.bottom
            anchors.topMargin: 10
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    _Searcher._Search(_SearchField.text)
                    _Searcher._Items = _SearchField.text
                }
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Search")
            }
        }



        ListView
        {
            id: _TeachersView
            anchors.top: _SearchButton.bottom
            anchors.topMargin: 10
            width: parent.width
            model: _Searcher._Items


            height: parent.height
            spacing: 0
            delegate: Rectangle
            {
                border.color: "black"
                border.width: 1
                width: parent.width
                height: 60
                Text {
                    id: name
                    font.bold: true
                    text: modelData
                    font.pointSize: 24
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

            }
        }
    }

}
