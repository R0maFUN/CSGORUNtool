import QtQuick 2.15
import QtQuick.Controls 2.15

Switch {
    id: control

    indicator: Rectangle {
        implicitWidth: 48
        implicitHeight: 23
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#17a81a" : Constants.lightPrimaryColor
        border.color: control.checked ? "#17a81a" : Constants.lightPrimaryColor

        Rectangle {
            x: control.checked ? parent.width - width : 0
            width: height
            height: parent.height
            radius: width / 2
            color: control.down ? "#cccccc" : "#ffffff"
            border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: "#ffffff"//control.down ? "#17a81a" : "#21be2b"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
    }
}
