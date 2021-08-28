#include "SettingsModel.h"

#include <QPointer>

SettingsModel::SettingsModel()
{
    auto patternRound1 = QPointer<PatternRound>(new PatternRound(false));
    auto patternRound2 = QPointer<PatternRound>(new PatternRound(true));
    auto patternRound3 = QPointer<PatternRound>(new PatternRound(false));

    auto patternRound4 = QPointer<PatternRound>(new PatternRound(false));
    auto patternRound5 = QPointer<PatternRound>(new PatternRound(false));

    auto patternRound6 = QPointer<PatternRound>(new PatternRound(false));
    auto patternRound7 = QPointer<PatternRound>(new PatternRound(true));
    auto patternRound8 = QPointer<PatternRound>(new PatternRound(true));
    auto patternRound9 = QPointer<PatternRound>(new PatternRound(false));

    m_patterns << QPointer<Pattern>(new Pattern{QList<QObject*>{patternRound1, patternRound2, patternRound3}, false, 1.2});
    m_patterns << QPointer<Pattern>(new Pattern{QList<QObject*>{patternRound4, patternRound5}, false, 1.2});
    m_patterns << QPointer<Pattern>(new Pattern{QList<QObject*>{patternRound6, patternRound7, patternRound8, patternRound9}, false, 1.2});
}

QList<QObject *> SettingsModel::getPatterns()
{
    return m_patterns;
}

Pattern::Pattern(const QList<QObject*> &pattern, const bool isActive, const double betKoef, const double percentageOfBalanceToBet) : m_pattern(pattern)
    , m_isActive(isActive)
    , m_betKoef(betKoef)
    , m_percentageOfBalanceToBet(percentageOfBalanceToBet)
{
}

QList<QObject*> Pattern::pattern()
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

double Pattern::percentageOfBalanceToBet() const
{
    return m_percentageOfBalanceToBet;
}

void Pattern::setPercentageOfBalanceToBet(const double &value)
{
    if (value == m_percentageOfBalanceToBet)
        return;

    m_percentageOfBalanceToBet = value;
    emit percentageOfBalanceToBetChanged();
}

PatternRound::PatternRound(const bool isCrash) : m_isCrash(isCrash)
{
}

bool PatternRound::isCrash() const
{
    return m_isCrash;
}

void PatternRound::setIsCrash(const bool value)
{
    if (m_isCrash == value)
        return;

    m_isCrash = value;
    emit isCrashChanged();
}
