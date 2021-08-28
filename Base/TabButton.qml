import QtQuick 2.0
import QtQuick.Templates 2.0 as T
import QtQuick.Controls 2.0

T.Button {
    id: root

//    Constants {
//        id: constants
//    }

    property bool clickable: true
    property color buttonPressedColor: Constants.primaryColor
    property color buttonHoveredColor: Constants.lightPrimaryColorWithAlpha
    property real textDisabledOpacity: 1
    property real textPressedOpacity: 1

    property alias backgroundColor: background.color

    font.pixelSize: Constants.h2pixelSize
    font.family: "Segoe UI"
    width: 140
    height: 50

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        hoverEnabled: true
        cursorShape: root.clickable ? Qt.PointingHandCursor : Qt.ArrowCursor
    }

    contentItem: Label {
        anchors.fill: root
        text: root.text
        font: root.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
    }

    background: Rectangle {
        id: background
        color: Constants.lightPrimaryColor
        //radius: 2
    }

    states: [
        State {
            name: "DisabledState"
            when: !root.enabled
            PropertyChanges { target: label; opacity: textDisabledOpacity }
        },
        State {
            name: "PressedState"
            when: root.clickable && root.pressed
            PropertyChanges { target: background; color: buttonPressedColor }
        },
        State {
            name: "HoveredState"
            when: root.clickable && root.hovered
            PropertyChanges { target: background; color: buttonHoveredColor }
        }
    ]
}
