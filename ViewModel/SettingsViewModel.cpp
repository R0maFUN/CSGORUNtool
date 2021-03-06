#include "SettingsViewModel.h"

#include "Model/SettingsModel.h"

#include <QDebug>

SettingsViewModel::SettingsViewModel(QObject *parent) : QObject(parent)
{
    settingsModel = QSharedPointer<SettingsModel>(new SettingsModel);

    connect(settingsModel.data(), &SettingsModel::authKeyChanged, this, &SettingsViewModel::authKeyChanged);
}

QList<QObject *> SettingsViewModel::patterns()
{
    return settingsModel->getPatterns();
}

QString SettingsViewModel::authKey() const
{
    return settingsModel->authKey();
}

void SettingsViewModel::setAuthKey(const QString &value)
{
    qDebug() << "SettingsViewModel::setAuthKey to " << value;
    settingsModel->setAuthKey(value);
}
