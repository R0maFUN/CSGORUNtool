#include "MainViewModel.h"
#include "LocalHistoryViewModel.h"
#include "Model/MainModel.h"

#include <QDebug>

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QRandomGenerator>
#include <QThread>
#include <QTimer>

std::vector<int> MainViewModel::itemIds1dollar {
    178,
    2779,
    3149,
    4304,
    4590,
    5647,
    5690,
    8770,
    9272
};

std::vector<int> MainViewModel::itemIds2dollar {
    347,
    361,
    264,
    313
};

std::atomic<bool> inventoryUpdated { false };
std::atomic<bool> inventoryCleared { false };
std::atomic<bool> preparedForBet { false };

int maxRetryCount = 7;

MainViewModel::MainViewModel(QGuiApplication* app, QObject *parent) : QObject(parent)
{
    this->app = app;
    m_localHistoryViewModel = new LocalHistoryViewModel();
    m_settingsViewModel = new SettingsViewModel();
    m_model = std::make_unique<MainModel>();

    m_manager = new QNetworkAccessManager(this);

    connect(m_localHistoryViewModel, &LocalHistoryViewModel::gotNewRound, this, &MainViewModel::processNewRound);
    connect(m_localHistoryViewModel, &LocalHistoryViewModel::patternFound, this, &MainViewModel::onBetRequested);
    connect(m_localHistoryViewModel, &LocalHistoryViewModel::patternFound, this, &MainViewModel::makeBet);
}

LocalHistoryViewModel* MainViewModel::localHistoryViewModel()
{
    return m_localHistoryViewModel;
}

SettingsViewModel *MainViewModel::settingsViewModel()
{
    return m_settingsViewModel;
}

void MainViewModel::onGotLatestsRounds(QString html)
{
    m_localHistoryViewModel->onGotLatestsRounds(html);
}

bool MainViewModel::authorized()
{
    return m_isAuthorized;
}

void MainViewModel::setAuthorized(bool value)
{
    if (m_isAuthorized == value)
        return;

    m_isAuthorized = value;
    emit authorizedChanged();
}

bool MainViewModel::running()
{
    return m_isRunning;
}

void MainViewModel::setRunning(const bool &value)
{
    qDebug() << "MainViewModel set running to " << value;
    if (m_isRunning == value)
        return;

    m_isRunning = value;
    emit runningChanged();
}

void MainViewModel::makeBet(double koef, int retryCounter)
{
    if (!m_isRunning || retryCounter >= maxRetryCount)
        return;
    qDebug() << "MainViewModel::makeBet";

    QJsonArray userItemIds;
    for (const auto& item : m_model->inventory()->items()) {
        userItemIds << QJsonValue::fromVariant(item->id);
    }

    if (userItemIds.isEmpty()) {
        qDebug() << "Skipping bet, because inventory is empty";
        return;
    }


    QJsonObject obj;
    obj["userItemIds"] = userItemIds;
    obj["auto"] = koef;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    qDebug() << "Sending data: " << data;

    //QThread::sleep(2);
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.csgorun.pro/make-bet"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Mobile Safari/537.36");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Authorization", m_settingsViewModel->authKey().toUtf8());
    request.setRawHeader("Content-Type", "application/json");

    qDebug() << "Making bet request...";
    QNetworkReply *reply = m_manager->post(request, data);

    connect(reply, &QNetworkReply::finished, [=]() mutable {
        if(reply->error() == QNetworkReply::NoError)
            qDebug() << "Made bet";
        else {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            retryCounter++;
            if (reply->error() == QNetworkReply::ServiceUnavailableError) {
                qDebug() << "Round already started, skipping...";
                return;
            }
            qDebug() << "Retrying...";
            QTimer::singleShot(2000, [=]() { makeBet(koef, retryCounter); });
        }

        reply->deleteLater();
    });
}

void MainViewModel::onBetRequested(double koef, double percentageOfBalanceToBet)
{
    updateInventory();
    if (!m_model->inventory()->isEmpty()) {
        clearInventory();
        updateInventory();
    }
    prepareSkinsForBet(percentageOfBalanceToBet);
    updateInventory();
    QTimer::singleShot(5000, [=]() { makeBet(koef); });
}

void MainViewModel::updateInventory()
{
    inventoryUpdated = false;
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.csgorun.pro/current-state"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Mobile Safari/537.36");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Authorization", m_settingsViewModel->authKey().toUtf8());

    qDebug() << "Making updateInventory request...";
    QNetworkReply *reply = m_manager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {

        if(reply->error() == QNetworkReply::NoError)
        {
            QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonObject rootObj = document.object();
            QJsonObject data = rootObj.value("data").toObject();
            QJsonObject user = data.value("user").toObject();

            if (user.isEmpty())
                return;

            m_model->inventory()->clearItems();

            double balance = user.value("balance").toDouble();

            QJsonArray items = user.value("items").toArray();

            for (const auto& itemJV : items) {
                QJsonObject item = itemJV.toObject();
                QPointer<InventoryItem> inventoryItem = new InventoryItem();
                inventoryItem->id = item.value("id").toInt();
                inventoryItem->name = item.value("name").toString().toStdString();
                inventoryItem->price = item.value("price").toDouble();

                qDebug() << "Found item: " << inventoryItem->id << " : " << QString(inventoryItem->name.c_str()) << " : " << inventoryItem->price;

                m_model->inventory()->appendItem(inventoryItem);

                balance += inventoryItem->price;
            }

            m_model->inventory()->setBalance(balance);
            qDebug() << "Updated inventory";
            inventoryUpdated = true;
        }
        else // handle error
        {
            qDebug() << reply->errorString();
            qDebug() << "Retrying...";
            QTimer::singleShot(1000, [=]() { updateInventory(); });
        }

        reply->deleteLater();
    });

    // ToDo: multi-threading
    while (!inventoryUpdated)
        app->processEvents();
}

void MainViewModel::clearInventory()
{
    inventoryCleared = false;
    //QString userItemIds;
    QJsonArray userItemIds;
    for (const auto& item : m_model->inventory()->items()) {
        userItemIds << QJsonValue::fromVariant(item->id);
    }

    QJsonObject obj;
    obj["userItemIds"] = userItemIds;
    obj["wishItemIds"] = QJsonArray();
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.csgorun.pro/marketplace/exchange-items"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Mobile Safari/537.36");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Authorization", m_settingsViewModel->authKey().toUtf8());
    request.setRawHeader("Content-Type", "application/json");

    qDebug() << "Making clear inventory request...";
    QNetworkReply *reply = m_manager->post(request, data);

    connect(reply, &QNetworkReply::finished, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            qDebug() << "Cleared inventory";
            inventoryCleared = true;
        }
        else {
            qDebug() << reply->errorString();
            qDebug() << "Retrying...";
            QTimer::singleShot(1000, [=]() { clearInventory(); });
        }

        reply->deleteLater();
    });

    while (!inventoryCleared)
        app->processEvents();
}

void MainViewModel::prepareSkinsForBet(double percentageOfBalanceToBet, bool retry)
{
    preparedForBet = false;

    int amountOfSkins = m_model->inventory()->getBalance() * percentageOfBalanceToBet / 2;

    QJsonArray wishItemIds;

    QString userItemIds;
    for (int i = 0; i < amountOfSkins; ++i) {
        int randIndex = QRandomGenerator::global()->generate() % itemIds2dollar.size();
        wishItemIds << itemIds2dollar.at(randIndex);
    }

    QJsonObject obj;
    obj["userItemIds"] = QJsonArray();
    obj["wishItemIds"] = wishItemIds;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    qDebug() << "Sending data: " << data;

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.csgorun.pro/marketplace/exchange-items"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Mobile Safari/537.36");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Authorization", m_settingsViewModel->authKey().toUtf8());
    request.setRawHeader("Content-Type", "application/json");

    qDebug() << "Making buy skins for bet request...";

    QNetworkReply *reply = m_manager->post(request, data);

    connect(reply, &QNetworkReply::finished, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            qDebug() << "Bought skins for bet";
            preparedForBet = true;
        }
        else {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            qDebug() << "Retrying...";
            QTimer::singleShot(1000, [=]() { prepareSkinsForBet(percentageOfBalanceToBet, true); });
        }
        reply->deleteLater();
    });

    while (!preparedForBet)
        app->processEvents();
}

void MainViewModel::processNewRound()
{
    qDebug() << "MainViewModel::processNewRound()";
    if (!m_isRunning)
        return;
    m_localHistoryViewModel->checkPatterns(m_settingsViewModel->patterns());
}
