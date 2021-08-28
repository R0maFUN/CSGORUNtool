import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "../Base" as Base

Item {
    id: root

    required property var patternModel
    property bool editable: false

    height: 100

    RowLayout {
        id: pattenrRow

        spacing: 20

        Rectangle {
            id: betRect
            width: 90
            height: 50
        }
    }

}
