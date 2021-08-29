#pragma once

#include <string>
#include <vector>

#include <QPointer>

struct InventoryItem
{
    std::string name;
    float cost;
    std::string imageUrl;
    std::string html;
};

class Inventory : QObject
{
    Q_OBJECT
public:
    Inventory();

private:
    std::vector<InventoryItem> items;
    float balance;
};

class MainModel
{
public:
    MainModel();

private:
    QPointer<Inventory> inventory;
};
