#include "LocalHistoryViewModel.h"
#include "Model/SettingsModel.h"

#include <QDebug>

LocalHistoryViewModel::LocalHistoryViewModel(QObject *parent) : QObject(parent)
{
    localHistoryModel = QSharedPointer<LocalHistoryModel>(new LocalHistoryModel);
}

void LocalHistoryViewModel::checkPatterns(QList<QObject *> patterns)
{
    qDebug() << "LocalHistoryViewModel::checkPatterns()";
    auto& roundsDeque = localHistoryModel->getRoundsDeque();
    int i = 0;
    for (const auto& qPattern : patterns) {
        auto pattern = qobject_cast<Pattern*>(qPattern);
        if (!pattern->isActive()) {
            qDebug() << "Skipping inactive pattern";
            continue;
        }

        bool goodPattern = true;
        qDebug() << "Checking pattern: ";
        for (const auto& patternValue : pattern->pattern()) {
            qDebug() << patternValue.toBool();
            if ((!patternValue.toBool() && roundsDeque[i].koef >= 1.2)
                || (patternValue.toBool() && roundsDeque[i].koef < 1.2)) {
                goodPattern = false;
                //break;
            }
            ++i;
        }
        if (goodPattern) {
            emit patternFound(pattern->betKoef(), pattern->percentageOfBalanceToBet());
        }
    }
}

void LocalHistoryViewModel::onGotLatestsRounds(QString latestRoundsHtml)
{
    if (localHistoryModel->processLatestRounds(latestRoundsHtml))
        emit gotNewRound();
}

void LocalHistoryViewModel::prependRound(QString roundHtml)
{
    localHistoryModel->prependRound(roundHtml);
}

void LocalHistoryViewModel::prependRound(int id, float koef)
{
    localHistoryModel->prependRound(id, koef);
}

int LocalHistoryViewModel::getLatestRoundId()
{
    return localHistoryModel->getLatestRoundId();
}

QVariant LocalHistoryViewModel::roundsModel()
{
    //return QList<QObject*>();
    qDebug() << "Trying to get roundsModel";
    //return localHistoryModel->getRoundObjects();
    return localHistoryModel->getRoundsModel();
}
