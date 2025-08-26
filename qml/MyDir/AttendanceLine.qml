import QtQuick
Rectangle {

    property color _LightBlue: ColorsNSizes._PrimaryPurple
    property color _LightPurple: ColorsNSizes._PrimaryBlue
    width: parent.width
    height: 60
    color: _LightBlue
    property string _StudentName: "Имя студента"
    property string _First: ""
    property string _Second: ""
    property string _Third: ""
    border.color: "black"
    border.width: 1

    Text {
        text: _StudentName
        anchors.right: _aFirst.left
        anchors.rightMargin: 20
        font.bold: true
        font.pointSize: (ColorsNSizes._SmallFont)
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        id: _aFirst
        width: parent.width / 6 + 1
        height: parent.height
        x: parent.width / 2
        color: _LightBlue
        border.color: "black"
        border.width: 1
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                console.log("First clicked")
                _First = "+"
                _Second = ""
                _Third = ""
            }
        }
        Text {

            text: qsTr(_First)
            font.pointSize: 24
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: _aSecond
        width: parent.width / 6
        height: parent.height
        x: parent.width / 2 + parent.width / 6
        color: _LightBlue
        border.color: "black"
        border.width: 1

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                console.log("Second clicked")
                _Second = "-"
                _First = ""
                _Third = ""
            }
        }
        Text {

            text: qsTr(_Second)
            font.pointSize: 24
            anchors.centerIn: parent
        }
    }



    Rectangle {
        id: _aThird
        width: parent.width / 6
        height: parent.height
        x: parent.width / 2 + 2 * parent.width / 6 - 1
        color: _LightBlue
        border.color: "black"
        border.width: 1

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                console.log("Third clicked")
                _Third = "?"
                _First = ""
                _Second = ""


            }
        }
        Text {

            text: qsTr(_Third)
            font.pointSize: 24
            anchors.centerIn: parent
        }
    }

}
