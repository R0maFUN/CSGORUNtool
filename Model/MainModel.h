#pragma once

#include <string>
#include <vector>

#include <QPointer>

struct InventoryItem : public QObject
{
    Q_OBJECT
public:
    unsigned int id;
    std::string name;
    double price;
    //std::string imageUrl;
};

class Inventory : public QObject
{
    Q_OBJECT
public:
    Inventory();

    std::vector<QPointer<InventoryItem>>& items();
    void setItems(const std::vector<QPointer<InventoryItem>>& value);
    void appendItem(QPointer<InventoryItem>& item);
    void clearItems();
    bool isEmpty();

    double getBalance() const;
    void setBalance(const double &value);

private:
    std::vector<QPointer<InventoryItem>> m_items;
    double m_balance;
};

class MainModel
{
public:
    MainModel();

    QPointer<Inventory> inventory();

private:
    QPointer<Inventory> m_inventory;
};
