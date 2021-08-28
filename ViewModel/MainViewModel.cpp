#include "MainViewModel.h"

#include <QDebug>

MainViewModel::MainViewModel(QObject *parent) : QObject(parent)
{
    m_localHistoryViewModel = new LocalHistoryViewModel();
    m_settingsViewModel = new SettingsViewModel();
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
    if (m_isRunning == value)
        return;

    m_isRunning = value;
    emit runningChanged();
}
