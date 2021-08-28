#pragma once

#include <QObject>
#include <QSharedPointer>

#include "../Model/SettingsModel.h"

class SettingsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> patterns READ patterns)

public:
    explicit SettingsViewModel(QObject *parent = nullptr);

public:
    QList<QObject*> patterns();

private:
    QSharedPointer<SettingsModel> settingsModel;
};
