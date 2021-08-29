#pragma once

#include <QObject>
#include <QSharedPointer>

#include "../Model/SettingsModel.h"

class SettingsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> patterns READ patterns)
    Q_PROPERTY(QString authKey READ authKey WRITE setAuthKey NOTIFY authKeyChanged)

public:
    explicit SettingsViewModel(QObject *parent = nullptr);

public:
    QList<QObject*> patterns();

public slots:
    QString authKey() const;
    void setAuthKey(const QString &value);

signals:
    void authKeyChanged();

private:
    QSharedPointer<SettingsModel> settingsModel;
};
