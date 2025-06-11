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
        onSourceChanged: animation.start()


                NumberAnimation {
                    id: animation
                    target: _Loader.item
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 350
                    easing.type: Easing.Linear
                }


    }


}
