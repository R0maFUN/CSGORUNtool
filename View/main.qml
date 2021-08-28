import QtQuick 2.12
import QtQuick.Window 2.12
import QtWebEngine 1.0
import QtQuick.Layouts 1.12
import "../Base" as Base

Window {
    id: view

    visible: true
    title: qsTr("Hello World")
    minimumHeight: 800
    minimumWidth: 1500

    RowLayout {
        spacing: 0
        anchors.fill: parent
        Menu {
            id: menu
            Layout.fillHeight: true
            Layout.preferredWidth: 200
            tabsModel: ["Home", "Settings", "History"]
        }

        Rectangle {
            id: pages
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: Base.Constants.primaryColor

            StackLayout {
                id: content

                anchors.fill: parent
                anchors.leftMargin: 30
                anchors.rightMargin: 30
                anchors.bottomMargin: 30

                property Item currentItem: currentIndex > -1 ? children[currentIndex] : null
                currentIndex: menu.selectedIndex
                children: [
                    Browser {
                        mainViewModel: viewModel
                    },
                    Settings {
                        settingsViewModel: viewModel.settingsViewModel
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    },
                    History {
                        historyViewModel: viewModel.localHistoryViewModel
                    }

                ]
            }
        }
    }

//    WebEngineView {
//        anchors.fill: parent
//        url: "https://www.qt.io"
//    }
}
