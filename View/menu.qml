import QtQuick 2.0
import QtQuick.Layouts 1.12
import "../Base" as Base

Rectangle {
    id: root
    required property var tabsModel
    property int selectedIndex: 0
    color: Base.Constants.lightPrimaryColor

    ColumnLayout {
        anchors.fill: root
        spacing: 0
        Repeater {
            model: tabsModel
            delegate: Base.TabButton {
                Layout.fillWidth: true

                backgroundColor: selectedIndex === index ? Base.Constants.primaryColor : root.color
                clickable: selectedIndex !== index

                text: modelData
                onClicked: selectedIndex = index
            }
        }

        Item {
            Layout.fillHeight: true
        }

    }

}
