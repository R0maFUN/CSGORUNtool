#pragma once

#include <QObject>
#include <QSharedPointer>

#include "../Model/LocalHistoryModel.h"
#include "../Model/SettingsModel.h"

class LocalHistoryViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant roundsModel READ roundsModel NOTIFY gotNewRound)

public:
    explicit LocalHistoryViewModel(QObject *parent = nullptr);
    void checkPatterns(QList<QObject*> patterns);

signals:
    void gotNewRound();
    void patternFound(double koef, double percentageOfBalanceToBet, bool retry);

public slots:
    void onGotLatestsRounds(QString latestRoundsHtml);
    void prependRound(QString roundHtml);
    void prependRound(int id, float koef);

    int getLatestRoundId();
    QVariant roundsModel();

private:
    QSharedPointer<LocalHistoryModel> localHistoryModel;

};
