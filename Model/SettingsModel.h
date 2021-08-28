#pragma once

#include <QList>
#include <QAbstractListModel>
#include <QObject>

class Pattern : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList pattern READ pattern)
    Q_PROPERTY(bool isActive READ isActive WRITE setIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(double betKoef READ betKoef WRITE setBetKoef NOTIFY betKoefChanged)
    Q_PROPERTY(double percentageOfBalanceToBet READ percentageOfBalanceToBet WRITE setPercentageOfBalanceToBet NOTIFY percentageOfBalanceToBetChanged)

public:
    Pattern(const QVariantList &pattern, const bool isActive = true, const double betKoef = 1.2, const double percentageOfBalanceToBet = 0.2);

public slots:
    QVariantList pattern();

    bool isActive() const;
    void setIsActive(const bool value);

    double betKoef() const;
    void setBetKoef(const double &value);

    double percentageOfBalanceToBet() const;
    void setPercentageOfBalanceToBet(const double &value);

signals:
    void isActiveChanged();
    void betKoefChanged();
    void percentageOfBalanceToBetChanged();

private:
    QVariantList m_pattern; // false - crush , true - good
    bool m_isActive;
    double m_betKoef;
    double m_percentageOfBalanceToBet;
};

class SettingsModel
{
public:
    SettingsModel();
    QList<QObject*> getPatterns();

private:
    QList<QObject*> m_patterns;
    //PatternModel m_patternModel;
};
