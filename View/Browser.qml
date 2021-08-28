import QtQuick 2.15
import QtQuick.Window 2.15
import QtWebEngine 1.1
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "../Base" as Base

Item {
    id: browser
    required property var mainViewModel
    property int lastRoundId: -1
    property int lastRoundKoef: -1
    property bool pageLoaded: false
    property bool isAuthorized: mainViewModel && mainViewModel.authorized

    signal gotNewRound(int roundId, real koef, bool preparing)
    signal gotLatestRounds(string html)

    property string latestRoundId
//    property string getLatestsRoundsScript: "var checkExist = setInterval(function() { \
//       if (document.querySelectorAll(\"a[href='/games/" + browser.latestRoundId +"']\").length) { \
//          console.log('[ROUND]' + ); \
//          clearInterval(checkExist); \
//       } \
//    }, 100); // check every 100ms"

    function findLatestRound() {
        webengine.runJavaScript("document.getElementsByClassName(\"graph-labels__inner\")[0].innerHTML", function(result) { gotLatestRounds(result) })
    }

    function checkIsAuthorized() {
        webengine.runJavaScript("document.getElementsByClassName(\"header-user__balance\").length", function(result) { mainViewModel.authorized = result > 0 })
    }

    onGotLatestRounds: {
        browser.mainViewModel.onGotLatestsRounds(html)
        pageLoaded = true
    }

    Action {
        id: authorizeAction
        enabled: !isAuthorized
        onTriggered: {
            webengine.runJavaScript("document.getElementsByClassName('btn btn--green steam-login')[0].click()")
        }
    }

    Timer {
        id: checkLatestsRoundsTimer
        interval: 500
        repeat: true
        running: pageLoaded// && isAuthorized
        onTriggered: findLatestRound()
    }

    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            Base.PrimaryButton {
                Layout.topMargin: 5
                Layout.preferredHeight: 40
                text: isAuthorized ? "Authorized" : "Authorize"
                clickable: !isAuthorized

                onClicked: authorizeAction.trigger()
            }
        }

        WebEngineView {
            id: webengine
            Layout.fillWidth: true
            Layout.fillHeight: true
            url: "https://csgorun.ru"

            onLoadProgressChanged: {
                console.log("Progress: " + loadProgress)
                console.log("url = " + url + " indexof = " + url.toString().indexOf("csgorun.ru"))
                if (loadProgress === 100 && url.toString().indexOf("csgorun.ru") !== -1) {
                    findLatestRound()
                    checkIsAuthorized()
                    //webengine.runJavaScript("document.getElementsByClassName(\"graph-labels__inner\")[0].innerHTML", function(result) { gotLatestRounds(result) })
                    console.log("Page loaded")
                }
            }
        }
    }
}
