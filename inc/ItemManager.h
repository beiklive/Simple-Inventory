// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-25
#ifndef INC_ITEMMANAGER_HPP_
#define INC_ITEMMANAGER_HPP_
#include <iostream>
#include <string>
#include <vector>

struct Item {
    int id;
    std::string name;
    int value;
    int weight;
    int quantity;
    std::string type;
};
#define ITEM_TYPES_COUNT   6


class ItemManager {
public:
    ItemManager() = default;
    ~ItemManager() = default;

    ItemManager(std::vector<Item>& items);
    ItemManager(const ItemManager& other) = delete;
    ItemManager& operator=(const ItemManager& other) = delete;


    bool isEmpty() const;
    int size() const;

    void InitItems(std::vector<Item>& items);
    void addItem(Item& item);
    void removeItem(int id);
    void updateItem(int id, Item& item);
    Item getItem(int id);
    std::vector<Item> getItems();

    void printAllItems();
    void printItem(std::string itemName);



private:
    std::vector<Item> m_items;


};




#endif  // INC_ITEMMANAGER_HPP_
