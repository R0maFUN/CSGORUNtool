#pragma once

#include <string>
#include <vector>

#include <QPointer>

struct Round
{
    int id;
    float koef;
};

struct InventoryItem
{
    std::string name;
    float cost;
    std::string imageUrl;
    std::string html;
};

class Inventory
{
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
