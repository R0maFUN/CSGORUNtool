#pragma once

#include <QList>
#include <QAbstractListModel>
#include <QObject>

class PatternRound : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isCrash READ isCrash WRITE setIsCrash NOTIFY isCrashChanged)

public:
    PatternRound(const bool isCrash);

signals:
    void isCrashChanged();

public slots:
    bool isCrash() const;
    void setIsCrash(const bool value);

private:
    bool m_isCrash;
};

class Pattern : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> pattern READ pattern)
    Q_PROPERTY(bool isActive READ isActive WRITE setIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(double betKoef READ betKoef WRITE setBetKoef NOTIFY betKoefChanged)
    Q_PROPERTY(double percentageOfBalanceToBet READ percentageOfBalanceToBet WRITE setPercentageOfBalanceToBet NOTIFY percentageOfBalanceToBetChanged)

public:
    Pattern(const QList<QObject*> &pattern, const bool isActive = true, const double betKoef = 1.2, const double percentageOfBalanceToBet = 0.25);

public slots:
    QList<QObject*> pattern();

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
    QList<QObject*> m_pattern; // false - crush , true - good
    bool m_isActive;
    double m_betKoef;
    double m_percentageOfBalanceToBet;
};

class SettingsModel : public QObject
{
    Q_OBJECT
public:
    SettingsModel();
    QList<QObject*> getPatterns();

    QString authKey() const;
    void setAuthKey(const QString &value);

signals:
    void authKeyChanged();

private:
    QList<QObject*> m_patterns;
    QString m_authKey;
    //PatternModel m_patternModel;
};
