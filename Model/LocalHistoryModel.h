#pragma once

#include <deque>
#include <string>

#include <QString>
#include <QList>
#include <QObject>
#include <QAbstractListModel>

struct Round
{
    int id;
    float koef;
};

class RoundModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RoundRoles {
        RoundIdRole = Qt::UserRole + 1,
        KoefRole
    };

    RoundModel(QObject* parent = nullptr);

    void appendRound(const Round& round);
    void prependRound(const Round& round);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Round> m_rounds;
};

class LocalHistoryModel
{
public:
    LocalHistoryModel();
    void initialize(QString lastRoundsHtml);
    bool processLatestRounds(QString latestRoundsHtml);
    bool prependRound(QString roundHtml);
    bool prependRound(int id, float koef);

    int getLatestRoundId();
    //QList<QObject*> getRoundObjects();
    QVariant getRoundsModel();
    std::deque<Round>& getRoundsDeque();

private:
    std::deque<Round> rounds;
    //QList<QObject *> roundObjects;
    RoundModel roundsModel;

    int latestRoundId;
};
