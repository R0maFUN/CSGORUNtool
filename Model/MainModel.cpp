#include "MainModel.h"

MainModel::MainModel()
{
    m_inventory = new Inventory();
}

QPointer<Inventory> MainModel::inventory()
{
    return m_inventory;
}

Inventory::Inventory()
{

}

std::vector<QPointer<InventoryItem> > &Inventory::items()
{
    return m_items;
}

void Inventory::setItems(const std::vector<QPointer<InventoryItem> > &value)
{
    m_items = value;
}

void Inventory::appendItem(QPointer<InventoryItem> &item)
{
    m_items.push_back(item);
}

void Inventory::clearItems()
{
    m_items.clear();
}

bool Inventory::isEmpty()
{
    return m_items.size() == 0;
}

double Inventory::getBalance() const
{
    return m_balance;
}

void Inventory::setBalance(const double &value)
{
    if (m_balance == value)
        return;

    m_balance = value;
}
