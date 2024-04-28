// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-25
#include "ItemManager.h"

ItemManager::ItemManager(std::vector<Item>& items): 
    m_items(items) 
{
}

//    void InitItems(std::vector<Item>& items);
void ItemManager::InitItems(std::vector<Item>& items)
{
    m_items = items;
}

void ItemManager::addItem(Item& item)
{
    m_items.push_back(item);
}


void ItemManager::removeItem(int id)
{    
    for (auto it = m_items.begin(); it!= m_items.end(); ++it) {
        if ((*it).id == id) {
            m_items.erase(it);
            break;
        }
    }
}


void ItemManager::updateItem(int id, Item& item)
{
    for (auto it = m_items.begin(); it!= m_items.end(); ++it) {
        if ((*it).id == id) {
            *it = item;
            break;
        }
    }
}


Item ItemManager::getItem(int id)
{
    for (auto it = m_items.begin(); it!= m_items.end(); ++it) {
        if ((*it).id == id) {
            return *it;
        }
    }
    return Item();
}

Item ItemManager::getItem(std::string name)
{
    for (auto it = m_items.begin(); it!= m_items.end(); ++it) {
        if ((*it).name == name) {
            return *it;
        }
    }
    return Item();
}

std::vector<Item> ItemManager::getItems()
{
    return m_items;
}


void ItemManager::printAllItems()
{
    for (auto it = m_items.begin(); it!= m_items.end(); ++it) {
        std::cout << "Item ID: " << (*it).id << std::endl;
        std::cout << "Item Name: " << (*it).name << std::endl;
        std::cout << "Item Value: " << (*it).value << std::endl;
        std::cout << "Item Weight: " << (*it).weight << std::endl;
        std::cout << "Item Quantity: " << (*it).quantity << std::endl;
        std::cout << "Item Type: " << (*it).type << std::endl;
        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    }
}

void ItemManager::printItem(std::string itemName)
{
    for (auto it = m_items.begin(); it != m_items.end(); ++it) {
        if ((*it).name == itemName) {
            std::cout << "Item ID: " << (*it).id << std::endl;
            std::cout << "Item Name: " << (*it).name << std::endl;
            std::cout << "Item Value: " << (*it).value << std::endl;
            std::cout << "Item Weight: " << (*it).weight << std::endl;
            std::cout << "Item Quantity: " << (*it).quantity << std::endl;
            std::cout << "Item Type: " << (*it).type << std::endl;
            std::cout << "<<" << std::endl;
            break;
        }
    }
}

bool ItemManager::isEmpty() const
{
    return m_items.empty();
}


int ItemManager::size() const
{
    return m_items.size();
}


Item ItemManager::createEmptyItem()
{
    Item empty_item;
    empty_item.id = 0;
    empty_item.name = "NULL";
    empty_item.quantity = 0;
    empty_item.weight = 0;
    empty_item.type = "NULL";
    return empty_item;
}