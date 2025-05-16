import QtQuick
import QtQuick.Window
import QtMultimedia
import VideoPlayer 1.0
import Qt.labs.platform
import "qrc:/qml/components"
import BackgroundManager 1.0

Window {
    id: rootWindow
    width: 800
    height: 600
    visible: true
    title: "Video Player"
    flags: Qt.Window

    // Property to track fullscreen state
    property bool isFullscreen: false
    property bool isMenuVisible: false
    property bool isIdle: true

    // Timer to handle idle state
    Timer {
        id: idleTimer
        interval: 5000  // 5 seconds
        onTriggered: isIdle = true
    }

    VideoPlayer {
        id: videoPlayer
        videoSink: videoOutput.videoSink
        source: "file:///D:/SideProjects/CanvasExperiment/assets/backgrounds/wicked-grace.3840x2160.mp4"
        Component.onCompleted: play()
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }

    // Loading overlay
    LoadingOverlay {
        isLoading: videoPlayer.isLoading
    }

    // Error overlay
    ErrorOverlay {
        errorMessage: videoPlayer.error
    }

    // Mouse area to detect hover over the window
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            isIdle = false
            idleTimer.restart()
        }
    }

    // Controls container
    Column {
        id: controlsContainer
        anchors {
            top: parent.top
            right: parent.right
            margins: 10
        }
        spacing: 10

        // Gear icon
        ControlButton {
            icon: "⚙"
            isIdle: rootWindow.isIdle
            onClicked: {
                // Add gear button functionality here
            }
        }

        // Fullscreen button
        ControlButton {
            icon: "⛶"
            isIdle: rootWindow.isIdle
            onClicked: {
                if (isFullscreen) {
                    rootWindow.flags = Qt.Window
                    rootWindow.showNormal()
                    isFullscreen = false
                } else {
                    rootWindow.flags = Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
                    var currentScreen = rootWindow.screen
                    rootWindow.width = currentScreen.width
                    rootWindow.height = currentScreen.height
                    rootWindow.x = currentScreen.virtualX
                    rootWindow.y = currentScreen.virtualY
                    isFullscreen = true
                }
            }
        }

        // Edit button
        ControlButton {
            icon: "✎"
            isIdle: rootWindow.isIdle
            onClicked: {
                console.log("Edit button clicked, backgroundManager:", backgroundManager)
                isMenuVisible = !isMenuVisible
            }
        }
    }

    // Customization Menu
    CustomizationMenu {
        id: customizationMenu
        isVisible: isMenuVisible
        onBackgroundSelected: function(path) {
            console.log("Background selected:", path)
            videoPlayer.source = path
            isMenuVisible = false  // Close the menu after selection
        }
        Component.onCompleted: {
            setBackgroundManager(backgroundManager)
        }
    }
} 