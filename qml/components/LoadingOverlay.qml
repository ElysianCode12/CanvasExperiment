import QtQuick

Rectangle {
    id: loadingOverlay
    anchors.fill: parent
    color: "#80000000"
    visible: isLoading
    opacity: isLoading ? 1 : 0

    property bool isLoading: false

    Text {
        anchors.centerIn: parent
        text: "Loading..."
        color: "white"
        font.pixelSize: 24
    }

    Behavior on opacity {
        NumberAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
} 