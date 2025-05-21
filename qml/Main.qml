import QtQuick
import QtQuick.Controls

ApplicationWindow {

    visible: true
    id: _LoaderPage
    width: 480
    height:1000

    Loader
    {
        id: _Loader
        anchors.fill: parent
        source:"LoginPage.qml"

    }


}
