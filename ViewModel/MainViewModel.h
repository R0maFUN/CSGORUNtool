#pragma once

#include "LocalHistoryViewModel.h"
#include "SettingsViewModel.h"
#include "Model/MainModel.h"

#include <QObject>
#include <QPointer>
#include <QNetworkAccessManager>
#include <QGuiApplication>

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LocalHistoryViewModel* localHistoryViewModel READ localHistoryViewModel CONSTANT)
    Q_PROPERTY(SettingsViewModel* settingsViewModel READ settingsViewModel CONSTANT)
    Q_PROPERTY(bool authorized READ authorized WRITE setAuthorized NOTIFY authorizedChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    MainViewModel(QGuiApplication* app, QObject *parent = nullptr);
    LocalHistoryViewModel* localHistoryViewModel();
    SettingsViewModel* settingsViewModel();

public:
    static std::vector<int> itemIds1dollar;

signals:
    void authorizedChanged();
    void runningChanged();
    void betRequested(double koef, double percentageOfBalanceToBet);

public slots:
    void onGotLatestsRounds(QString html);

    bool authorized();
    void setAuthorized(bool value);

    bool running();
    void setRunning(const bool &value);

    void makeBet(double koef, double percentageOfBalanceToBet, bool retry = false);

    Q_INVOKABLE void updateInventory();
    Q_INVOKABLE void clearInventory();
    Q_INVOKABLE void prepareSkinsForBet(double percentageOfBalanceToBet, bool retry = false);


    //void onPatternFound(double koef);

private:
    void processNewRound();

private:
    QPointer<LocalHistoryViewModel> m_localHistoryViewModel;
    QPointer<SettingsViewModel> m_settingsViewModel;
    std::unique_ptr<MainModel> m_model;

    QNetworkAccessManager *m_manager;

    bool m_isAuthorized;
    bool m_isRunning = false;

    bool m_inventoryUpdated = false;
    bool m_inventoryCleared = false;
    bool m_preparedForBet = false;

    QGuiApplication* app;
};
