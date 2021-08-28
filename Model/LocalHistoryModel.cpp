#include "./LocalHistoryModel.h"

#include <QRegExp>
#include <QDebug>

LocalHistoryModel::LocalHistoryModel() : latestRoundId(-1)
{
}

void LocalHistoryModel::initialize(QString lastRoundsHtml)
{
    QRegExp rx("(/games/\\d+)[^>]+>(<span>[^<]+)");

    int pos = 0;

    while ((pos = rx.indexIn(lastRoundsHtml, pos)) != -1) {
        QString round = rx.cap(1);
        round.remove("/games/");
        QString koef = rx.cap(2);
        koef.remove("<span>").remove("x");
        Round r {round.toInt(), koef.toFloat()};

        rounds.push_back(r);
        //roundObjects.append(new RoundObject(r.id, r.koef));
        roundsModel.appendRound(r);

        qDebug() << "Round #" << round.toInt() << " koef = " << koef.toDouble();
        pos += rx.matchedLength();
    }

    latestRoundId = rounds.front().id;
}

bool LocalHistoryModel::processLatestRounds(QString latestRoundsHtml)
{
    if (rounds.size() == 0)
        initialize(latestRoundsHtml);
    else
        return prependRound(latestRoundsHtml);
    return false;
}

bool LocalHistoryModel::prependRound(QString roundHtml)
{
    QRegExp rx("(/games/\\d+)[^>]+>(<span>[^<]+)");

    int pos = 0;

    if ((pos = rx.indexIn(roundHtml, pos)) != -1) {
        QString round = rx.cap(1);
        round.remove("/games/");
        QString koef = rx.cap(2);
        koef.remove("<span>").remove("x");
        Round r {round.toInt(), koef.toFloat()};

        if (r.id <= rounds.front().id)
            return false;

        rounds.push_front(r);
        //roundObjects.prepend(new RoundObject(r.id, r.koef));
        roundsModel.prependRound(r);

        qDebug() << "Round #" << round.toInt() << " koef = " << koef.toDouble();
        pos += rx.matchedLength();
        latestRoundId = rounds.front().id;
        return true;
    }

    return false;
}

bool LocalHistoryModel::prependRound(int id, float koef)
{
    if (id <= rounds.front().id)
        return false;

    rounds.push_front(Round {id, koef});
    //roundObjects.prepend(new RoundObject(id, koef));
    roundsModel.prependRound(Round {id, koef});
    latestRoundId = id;
    return true;
}

int LocalHistoryModel::getLatestRoundId()
{
    return latestRoundId;
}

QVariant LocalHistoryModel::getRoundsModel()
{
    return QVariant::fromValue(&roundsModel);
}

//QList<QObject *> LocalHistoryModel::getRoundObjects()
//{
//    return roundObjects;
//}

//RoundObject::RoundObject(int roundId, double koef, QObject *parent) : QObject(parent)
//{
//    m_roundId = roundId;
//    m_koef = koef;
//}

//int RoundObject::getRoundId()
//{
//    return m_roundId;
//}

//void RoundObject::setRoundId(int value)
//{
//    if (m_roundId == value)
//        return;

//    m_roundId = value;
//    emit roundIdChanged();
//}

//double RoundObject::getKoef()
//{
//    return m_koef;
//}

//void RoundObject::setKoef(double value)
//{
//    if (m_koef == value)
//        return;

//    m_koef = value;
//    emit koefChanged();
//}

RoundModel::RoundModel(QObject *parent) : QAbstractListModel(parent)
{
}

void RoundModel::prependRound(const Round &round)
{
    qDebug() << "Model prepend #" << round.id;
    beginInsertRows(QModelIndex(), 0, 0);
    m_rounds.prepend(round);
    endInsertRows();
}

void RoundModel::appendRound(const Round &round)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_rounds << round;
    endInsertRows();
}

int RoundModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_rounds.count();
}

QVariant RoundModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_rounds.count())
            return QVariant();

    const Round &round = m_rounds[index.row()];
    if (role == RoundIdRole)
        return round.id;
    else if (role == KoefRole)
        return round.koef;
    return QVariant();
}

QHash<int, QByteArray> RoundModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RoundIdRole] = "roundId";
    roles[KoefRole] = "koef";
    return roles;
}
