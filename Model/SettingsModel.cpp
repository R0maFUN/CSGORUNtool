#include "SettingsModel.h"

SettingsModel::SettingsModel()
{
    m_patterns << new Pattern{QVariantList{false, true, false}, false, 1.2};
    m_patterns << new Pattern{QVariantList{false, false}, false, 1.2};
    m_patterns << new Pattern{QVariantList{false, true, true, false}, false, 1.2};
}

QList<QObject *> SettingsModel::getPatterns()
{
    return m_patterns;
}

Pattern::Pattern(const QVariantList &pattern, const bool isActive, const double betKoef, const double percentageOfBalanceToBet) : m_pattern(pattern)
    , m_isActive(isActive)
    , m_betKoef(betKoef)
    , m_percentageOfBalanceToBet(percentageOfBalanceToBet)
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
