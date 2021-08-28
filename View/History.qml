import QtQuick 2.15
import QtQuick.Window 2.15
import QtWebEngine 1.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "../Base" as Base

Item {
    id: root

    required property var historyViewModel

    property int currentTabIndex: 1
    property color color: Base.Constants.primaryColor

    ColumnLayout {
        anchors.fill: root
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            spacing: 0

            Item {
                Layout.fillWidth: true
            }

            Repeater {
                id: tabs

                model: ["Global", "Local", "Bet history"]

                delegate: Base.TabButton {
                    backgroundColor: currentTabIndex === index ? Base.Constants.lightPrimaryColor : Base.Constants.darkPrimaryColor
                    buttonPressedColor: Base.Constants.darkPrimaryColor
                    clickable: currentTabIndex !== index

                    text: modelData
                    onClicked: currentTabIndex = index
                }
            }

            Item {
                Layout.fillWidth: true
            }
        }

        Rectangle {
            id: pages
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: Base.Constants.lightPrimaryColor
            radius: 5

            StackLayout {
                id: content

                anchors.fill: parent
                anchors.leftMargin: 30
                anchors.rightMargin: 30
                anchors.bottomMargin: 30

                property Item currentItem: currentTabIndex > -1 ? children[currentTabIndex] : null
                currentIndex: currentTabIndex
                children: [
                    Item {

                    },
                    RoundsHistory {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        localHistoryViewModel: root.historyViewModel
                        //roundsModel: ["1.15", "1.19", "1.5", "2.3", "4.5", "9.0", "3.0", "2.2", "1.3", "1.15", "1.19", "1.5", "2.3", "4.5", "9.0", "3.0", "2.2", "1.3"]
                    },
                    Item {

                    }

                ]
            }
        }
    }
}
