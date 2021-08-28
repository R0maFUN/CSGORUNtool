#pragma once

#include "LocalHistoryViewModel.h"
#include "SettingsViewModel.h"

#include <QObject>
#include <QPointer>

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LocalHistoryViewModel* localHistoryViewModel READ localHistoryViewModel CONSTANT)
    Q_PROPERTY(SettingsViewModel* settingsViewModel READ settingsViewModel CONSTANT)
    Q_PROPERTY(bool authorized READ authorized WRITE setAuthorized NOTIFY authorizedChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    MainViewModel(QObject *parent = nullptr);
    LocalHistoryViewModel* localHistoryViewModel();
    SettingsViewModel* settingsViewModel();

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

    //void onPatternFound(double koef);

private:
    void processNewRound();

private:
    QPointer<LocalHistoryViewModel> m_localHistoryViewModel;
    QPointer<SettingsViewModel> m_settingsViewModel;

    bool m_isAuthorized;
    bool m_isRunning = false;
};
