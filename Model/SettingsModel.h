#pragma once

#include <QList>
#include <QAbstractListModel>
#include <QObject>




//struct Pattern {
//    //int m_patternId;
//    QList<bool> m_pattern; // false - crush , true - good
//    bool m_isActive;
//    double m_betKoef;
//};

//class PatternModel : public QAbstractListModel
//{
//    Q_OBJECT

//public:
//    enum PatternRoles {
//        PatternList = Qt::UserRole + 1,
//        IsActiveRole,
//        BetKoefRole
//    };

//    PatternModel(QObject* parent = nullptr);

//    void appendPattern(const Pattern& pattern);
//    int rowCount(const QModelIndex& parent = QModelIndex()) const;
//    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

//protected:
//    QHash<int, QByteArray> roleNames() const;
//private:
//    QList<Pattern> m_patterns;
//};

class Pattern : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList pattern READ pattern)
    Q_PROPERTY(bool isActive READ isActive WRITE setIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(double betKoef READ betKoef WRITE setBetKoef NOTIFY betKoefChanged)

public:
    Pattern(const QVariantList &pattern, const bool isActive = true, const double betKoef = 1.2);

public slots:
    QVariantList pattern();

    bool isActive() const;
    void setIsActive(const bool value);

    double betKoef() const;
    void setBetKoef(const double &value);

signals:
    void isActiveChanged();
    void betKoefChanged();


private:
    QVariantList m_pattern; // false - crush , true - good
    bool m_isActive;
    double m_betKoef;
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
