import QtQuick
import BackgroundManager 1.0

Rectangle {
    id: customizationMenu
    width: 200
    height: menuColumn.height + 20
    color: "#80000000"
    radius: 10
    visible: isVisible
    opacity: isVisible ? 1 : 0
    anchors.centerIn: parent

    property bool isVisible: false
    property var _backgroundManager: null
    signal backgroundSelected(string path)

    // Function to set the background manager
    function setBackgroundManager(manager) {
        _backgroundManager = manager
    }

    // Debug output for background files
    onVisibleChanged: {
        if (visible && _backgroundManager) {
            console.log("CustomizationMenu: Background files:", _backgroundManager.backgroundFiles)
        }
    }

    Column {
        id: menuColumn
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }
        spacing: 5

        Text {
            text: "Background Options"
            color: "white"
            font.pixelSize: 16
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Debug text to show if backgroundManager is null
        Text {
            visible: !_backgroundManager
            text: "No background manager available"
            color: "red"
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Debug text to show if no files are available
        Text {
            visible: _backgroundManager && _backgroundManager.backgroundFiles.length === 0
            text: "No background files found"
            color: "yellow"
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Repeater {
            model: _backgroundManager ? _backgroundManager.backgroundFiles : []

            Rectangle {
                width: parent.width
                height: 30
                color: mouseArea.containsMouse ? "#40ffffff" : "transparent"
                radius: 5

                Text {
                    text: modelData
                    color: "white"
                    anchors {
                        left: parent.left
                        verticalCenter: parent.verticalCenter
                        leftMargin: 10
                    }
                    elide: Text.ElideRight
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        console.log("CustomizationMenu: Selected background:", modelData)
                        var path = _backgroundManager.getFullPath(modelData)
                        backgroundSelected(path)
                        // Don't set isVisible here, let the parent handle it
                    }
                }
            }
        }
    }

    Behavior on opacity {
        NumberAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }
} 