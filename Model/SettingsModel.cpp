#include "SettingsModel.h"

SettingsModel::SettingsModel()
{
    m_patterns << new Pattern{QVariantList{false, true, false}, false, 1.2};
    m_patterns << new Pattern{QVariantList{false, false}, false, 1.2};
    m_patterns << new Pattern{QVariantList{false, true, true, false}, false, 1.2};

    //m_patternModel.appendPattern(Pattern{QList<bool>{false, true, false}, false, 1.2});
    //m_patternModel.appendPattern(Pattern{QList<bool>{false, false}, false, 1.2});
    //m_patternModel.appendPattern(Pattern{QList<bool>{false, true, true, false}, false, 1.2});
}

QList<QObject *> SettingsModel::getPatterns()
{
    return m_patterns;
}

//QVariant SettingsModel::getPatternModel()
//{
//    return QVariant::fromValue(&m_patternModel);
//}

//PatternModel::PatternModel(QObject *parent) : QAbstractListModel(parent)
//{
//}

//void PatternModel::appendPattern(const Pattern &pattern)
//{
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    m_patterns << pattern;
//    endInsertRows();
//}

//int PatternModel::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent);
//    return m_patterns.count();
//}

//QVariant PatternModel::data(const QModelIndex &index, int role) const
//{
//    if (index.row() < 0 || index.row() >= m_patterns.count())
//            return QVariant();

//    const Pattern &pattern = m_patterns[index.row()];

//    if (role == PatternList)
//        return QVariant::fromValue(pattern.m_pattern);
//    else if (role == IsActiveRole)
//        return pattern.m_isActive;
//    else if (role == BetKoefRole)
//        return pattern.m_betKoef;
//    return QVariant();
//}

//QHash<int, QByteArray> PatternModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    roles[PatternList] = "patternList";
//    roles[IsActiveRole] = "isActive";
//    roles[BetKoefRole] = "betKoef";
//    return roles;
//}

//Pattern::Pattern(QList<bool> pattern, bool isActive, double betKoef) : m_pattern(pattern)
//  , m_isActive(isActive)
//  , m_betKoef(betKoef)
//{

//}

Pattern::Pattern(const QVariantList &pattern, const bool isActive, const double betKoef) : m_pattern(pattern)
    , m_isActive(isActive)
    , m_betKoef(betKoef)
{
}

QVariantList Pattern::pattern()
{
    return m_pattern;
}

bool Pattern::isActive() const
{
    return m_isActive;
}

void Pattern::setIsActive(const bool value)
{
    if (value == m_isActive)
        return;

    m_isActive = value;
    emit isActiveChanged();
}

double Pattern::betKoef() const
{
    return m_betKoef;
}

void Pattern::setBetKoef(const double &value)
{
    if (value == m_betKoef)
        return;

    m_betKoef = value;
    emit betKoefChanged();
}
