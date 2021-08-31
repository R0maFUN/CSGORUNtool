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
    property double balance: 0

    property int updateBalanceCounter: 0
    property int roundsCounter: 0

    signal gotNewRound(int roundId, real koef, bool preparing)
    signal gotLatestRounds(string html)

    property string latestRoundId

    Connections {
        target: mainViewModel
        function onBetRequested(koef, percentageOfBalanceToBet) {
            console.log("[bet] I SHOULD BET ")
        }
    }

    function findLatestRound() {
        webengine.runJavaScript("document.getElementsByClassName(\"graph-labels__inner\")[0].innerHTML", function(result) { gotLatestRounds(result) })
    }

    function checkIsAuthorized() {
        webengine.runJavaScript("document.getElementsByClassName(\"header-user__balance\").length", function(result) { mainViewModel.authorized = result > 0 })
    }

    function updateBalance() {
        webengine.runJavaScript("document.getElementsByClassName('cur-u-drops-selected-2__total')[0].children[1].innerText.split(' ')[0]", function(result) {
            balance = parseFloat(result)
        })

        mainViewModel.updateInventory()
    }

    function buySkin(price) {

    }

    onGotLatestRounds: {
        //updateBalanceCounter++
        //if (updateBalanceCounter % 3 === 0)
        //    updateBalance()
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

    Timer {
        id: reloadPageTimer
        interval: 200000
        repeat: true
        onTriggered: webengine.reload()
    }

    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            spacing: 10
            Base.PrimaryButton {
                Layout.topMargin: 5
                Layout.preferredHeight: 40
                text: isAuthorized ? "Authorized" : "Authorize"
                clickable: !isAuthorized

                onClicked: authorizeAction.trigger()
            }

            Rectangle {
                Layout.topMargin: 5
                Layout.preferredWidth: 150
                Layout.preferredHeight: 40
                //border.width: 2
                //border.color: "#ffffff"
                radius: 4
                color: Base.Constants.primaryColor

                Base.Switcher {
                    id: runningSwitcher
                    anchors.centerIn: parent
                    text: checked ? qsTr("Running") : qsTr("Paused")
                    font.pixelSize: Base.Constants.h2pixelSize
                    enabled: isAuthorized

                    checked: mainViewModel.running
                    onCheckedChanged: mainViewModel.running = checked
                }
            }

            Base.PrimaryButton {
                Layout.topMargin: 5
                Layout.preferredHeight: 40
                text: qsTr("Clear inventory")
                clickable: isAuthorized

                onClicked: {
                    mainViewModel.updateInventory()
                    mainViewModel.clearInventory()
                }
            }

            Base.PrimaryButton {
                Layout.topMargin: 5
                Layout.preferredHeight: 40
                text: qsTr("Buy some skins")
                clickable: isAuthorized

                onClicked: mainViewModel.prepareSkinsForBet(0.2)
            }
        }

        WebEngineView {
            id: webengine
            Layout.fillWidth: true
            Layout.fillHeight: true
            url: "https://csgorun.pro"

            onLoadProgressChanged: {
                console.log("Progress: " + loadProgress)
                console.log("url = " + url + " indexof = " + url.toString().indexOf("csgorun"))
                if (loadProgress === 100 && url.toString().indexOf("csgorun") !== -1) {
                    findLatestRound()
                    checkIsAuthorized()
                    //webengine.runJavaScript("document.getElementsByClassName(\"graph-labels__inner\")[0].innerHTML", function(result) { gotLatestRounds(result) })
                    console.log("Page loaded")
                }
            }
        }
    }
}
