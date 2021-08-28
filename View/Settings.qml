import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "../Base" as Base

Flickable {
    id: settingsView

    required property var settingsViewModel

    flickableDirection: Flickable.VerticalFlick
    interactive: contentItem.implicitHeight > height
    clip: true

    ColumnLayout {
        id: settingsLayout
        anchors.fill: parent
        spacing: 15
        //anchors.margins: 30

        Label {
            id: header
            Layout.fillWidth: true
            Layout.preferredHeight: 50

            font.family: Base.Constants.fontFamily
            font.pixelSize: Base.Constants.headerPixelSize
            font.bold: true
            color: "white"

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            text: qsTr("Settings")
        }

        Label {
            id: patternsLabel
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            font.family: Base.Constants.fontFamily
            font.pixelSize: Base.Constants.h1pixelSize
            color: "white"

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            text: qsTr("Patterns")
        }

        Repeater {
            id: patternsRepeater
            model: settingsViewModel.patterns

            delegate: RowLayout {
                Layout.preferredHeight: 50
                Layout.fillWidth: true
                spacing: 10

                Rectangle {
                    width: 100
                    height: 50

                    radius: 3
                    color: "black"

                    Label {
                        anchors.fill: parent
                        anchors.topMargin: 5
                        text: "Bet"
                        font.pixelSize: Base.Constants.h2pixelSize
                        font.family: "Segoe UI"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                        color: "white"
                    }

                    Label {
                        anchors.fill: parent
                        anchors.bottomMargin: 5
                        text: "Koef = " + modelData.betKoef.toFixed(2) + "x"
                        font.pixelSize: Base.Constants.h2pixelSize
                        font.family: "Segoe UI"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        color: "white"
                    }
                }

                Repeater {
                    id: patternRepeater
                    model: modelData.pattern

                    delegate: Rectangle {
                        width: 90
                        height: 50
                        radius: 3

                        color: Base.Constants.lightPrimaryColor
                        border.width: 3
                        border.color: modelData ? "#4a3afc" : "#fc3a3a"

                        Label {
                            anchors.fill: parent
                            text: modelData ? "Good" : "Crash"
                            font.pixelSize: Base.Constants.h2pixelSize
                            font.family: "Segoe UI"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "white"
                        }

                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor

                            onClicked: modelData = !modelData
                        }
                    }

                    Component.onCompleted: {
                        console.log("patternList: " + modelData.pattern)
                        console.log("model[1]: " + model[1])
                    }
                }
            }
        }

        Item { Layout.fillHeight: true }

    }
}
