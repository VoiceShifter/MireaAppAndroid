import QtQuick
import QtQuick.Controls
ApplicationWindow {

    visible: true
    id: _LoaderPage




    Loader
    {
        id: _Loader
        anchors.fill: parent
        source:"LoginPage.qml"
    }



}
