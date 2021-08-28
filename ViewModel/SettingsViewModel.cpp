#include "SettingsViewModel.h"

SettingsViewModel::SettingsViewModel(QObject *parent) : QObject(parent)
{
    settingsModel = QSharedPointer<SettingsModel>(new SettingsModel);
}

QList<QObject *> SettingsViewModel::patterns()
{
    return settingsModel->getPatterns();
}

//QVariant SettingsViewModel::patternModel()
//{
//    return settingsModel->getPatternModel();
//}
