#include "LocalHistoryViewModel.h"

#include <QDebug>

LocalHistoryViewModel::LocalHistoryViewModel(QObject *parent) : QObject(parent)
{
    localHistoryModel = QSharedPointer<LocalHistoryModel>(new LocalHistoryModel);
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
