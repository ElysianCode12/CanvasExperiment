import QtQuick

Rectangle {
    id: errorOverlay
    anchors.fill: parent
    color: "#80000000"
    visible: errorMessage !== ""
    opacity: errorMessage !== "" ? 1 : 0

    property string errorMessage: ""

    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            text: "Error loading video"
            color: "white"
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: errorMessage
            color: "white"
            font.pixelSize: 16
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Behavior on opacity {
        NumberAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
} 