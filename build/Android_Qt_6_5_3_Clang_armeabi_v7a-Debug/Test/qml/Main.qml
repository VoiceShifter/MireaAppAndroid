import QtQuick
import QtQuick.Controls
import com.JsonParser 1.0

ApplicationWindow {

    visible: true
    id: _LoaderPage




    Loader
    {
        id: _Loader
        anchors.fill: parent
        source:"LoginPage.qml"
    }
    JsonParser
    {
        id: _Parser
        Component.onCompleted:
        {


        }
    }


}
