import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "../Base" as Base

Flickable {

    required property var localHistoryViewModel
    property var roundsModel: localHistoryViewModel.roundsModel

    flickableDirection: Flickable.VerticalFlick
    interactive: contentItem.implicitHeight > height
    clip: true

    GridView {
        anchors.fill: parent
        anchors.topMargin: 30
        model: roundsModel
        clip: true

        delegate: Rectangle {
            width: 90
            height: 60
            radius: 10

            color: Base.Constants.lightPrimaryColor
            border.width: 4
            border.color: getColor(koef);

            Label {
                anchors.fill: parent
                anchors.topMargin: 10
                text: koef.toFixed(2) + "x"
                font.pixelSize: Base.Constants.h2pixelSize
                font.family: "Segoe UI"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                color: "white"
            }

            Label {
                anchors.fill: parent
                anchors.bottomMargin: 10
                text: "#" + roundId
                font.pixelSize: Base.Constants.h2pixelSize
                font.family: "Segoe UI"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                color: "white"
            }

            function getColor(koefP) {
                if (koefP < 1.2)
                    return "#fc3a3a"
                if (koefP < 2)
                    return "#4a3afc"
                if (koefP < 4)
                    return "#f93afc"
                if (koefP < 8)
                    return "#3afc5a"
                return "#ffe357"
            }
        }
    }
}
