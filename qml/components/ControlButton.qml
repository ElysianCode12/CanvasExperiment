import QtQuick

Rectangle {
    id: controlButton
    width: 40
    height: 40
    radius: 20
    color: "#80000000"  // Semi-transparent black
    visible: !isIdle || opacity > 0
    opacity: isIdle ? 0 : 1

    property string icon: ""
    property bool isIdle: true
    signal clicked()

    Text {
        text: icon
        color: "white"
        font.pixelSize: 24
        anchors.centerIn: parent
    }

    states: State {
        name: "hovered"
        when: mouseArea.containsMouse
        PropertyChanges {
            target: controlButton
            scale: 1.1
        }
    }

    transitions: [
        Transition {
            NumberAnimation { properties: "scale"; duration: 100 }
        },
        Transition {
            from: "*"; to: "*"
            NumberAnimation { 
                properties: "opacity"
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }
    ]

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: controlButton.clicked()
    }

    Behavior on opacity {
        NumberAnimation {
            duration: 300
            easing.type: Easing.InOutQuad
        }
    }
} 