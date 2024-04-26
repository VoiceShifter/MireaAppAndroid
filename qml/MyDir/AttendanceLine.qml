import QtQuick
Rectangle {

    property color _LightBlue: "#DBE2EF"
    property color _LightPurple: "#7881AE"
    width: parent.width
    height: 60
    color: _LightBlue
    property string _StudentName: ""
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
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        id: _aFirst
        width: parent.width / 6
        height: parent.height
        x: parent.width / 2 - 1
        color: _LightBlue
        border.color: "black"
        border.width: 1
        Text {

            text: qsTr(_First)
            font.pointSize: 24
            anchors.centerIn: parent
        }
    }

    Rectangle {

        width: parent.width / 6
        height: parent.height
        x: parent.width / 2 + parent.width / 6 - 1
        color: _LightBlue
        border.color: "black"
        border.width: 1
        Text {

            text: qsTr(_Second)
            font.pointSize: 24
            anchors.centerIn: parent
        }
    }



    Rectangle {

        width: parent.width / 6
        height: parent.height
        x: parent.width / 2 + 2 * parent.width / 6 - 1
        color: _LightBlue
        border.color: "black"
        border.width: 1
        Text {

            text: qsTr(_Third)
            font.pointSize: 24
            anchors.centerIn: parent
        }
    }

}
