#pragma once

#include <deque>
#include <string>

#include <QString>
#include <QList>
#include <QObject>
#include <QAbstractListModel>

namespace {
struct Round
{
    int id;
    float koef;
};
} // anonymous

//class RoundObject : public QObject {
//    Q_OBJECT

//    Q_PROPERTY(int roundId READ getRoundId WRITE setRoundId NOTIFY roundIdChanged)
//    Q_PROPERTY(double koef READ getKoef WRITE setKoef NOTIFY koefChanged)

//public:
//    RoundObject(int roundId, double koef, QObject* parent = nullptr) : QObject(parent)
//    {
//        m_roundId = roundId;
//        m_koef = koef;
//    }

//    signals:
//    void roundIdChanged();
//    void koefChanged();

//public slots:
//    int getRoundId();
//    void setRoundId(int value);

//    double getKoef();
//    void setKoef(double value);

//private:
//    int m_roundId;
//    double m_koef;
//};

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

private:
    std::deque<Round> rounds;
    //QList<QObject *> roundObjects;
    RoundModel roundsModel;

    int latestRoundId;
};
