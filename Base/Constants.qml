pragma Singleton
import QtQuick 2.0

QtObject {
    readonly property color primaryColor: "#3b3b3b"
    readonly property color darkPrimaryColor: "#2e2e2e"
    readonly property color lightPrimaryColor: "#525252"
    readonly property color lightPrimaryColorWithAlpha: "#5c5c5c"

    readonly property color buttonPrimaryColor: "#ffa91f"
    readonly property color buttonLightPrimaryColor: "#ffc05c"
    readonly property color buttonDarkPrimaryColor: "#ff9c00"

    property color buttonPressedColor: buttonDarkPrimaryColor
    property color buttonHoveredColor: buttonLightPrimaryColor
    property real textDisabledOpacity: 0.8
    property real disabledLightOpacity: 0.8

    readonly property int headerPixelSize: 24
    readonly property int h1pixelSize: 18
    readonly property int h2pixelSize: 14

    readonly property string fontFamily: "Segoe UI"
}
