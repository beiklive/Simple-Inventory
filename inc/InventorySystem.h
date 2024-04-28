// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-26
#ifndef INC_INVENTORYSYSTEM_H_
#define INC_INVENTORYSYSTEM_H_
#include <iostream>
#include <string>
#include <vector>
#include "ItemManager.h"
/*
Function:
1. set bag capacity
2. add item to bag
3. remove item from bag
4. check if bag is full
5. check if bag is empty
6. check if item is in bag
7. get item count in bag by name
8. get item count in bag by id

*/
class InventorySystem
{
private:
    /* data */
    int _max_weight;
    int _max_capacity;

    int _current_weight;
    int _current_capacity;

    int _total_value;

    std::vector<Item>* items{ nullptr };
public:
    InventorySystem();
    ~InventorySystem();
    InventorySystem(int capacity, int weight);

    void set_bag_capacity(int capacity);
    void set_max_weight(int weight);

    int get_total_value();
    Item get_empty_item();
    int get_max_weight();
    int get_current_weight();
    int get_max_capacity();
    int get_current_capacity();
    int get_item_count_in_bag(Item item);
    int get_item_pos_in_bag(Item item);
    Item get_item_in_bag_by_pos(int pos);
    int get_first_empty_pos_in_bag();

    int add_item_to_bag(Item item);
    bool add_item_to_bag(Item item, int pos);
    bool remove_item_from_bag(Item item, int count, int pos);
    bool remove_item_from_bag(Item item);
    bool reset_pos_from_bag(int pos);

    bool is_bag_full();
    bool is_bag_empty();
    bool is_item_in_bag(Item item);
    bool is_bag_pos_empty(int pos);
    bool is_bag_pos_item_same(int pos, Item item);
};






#endif  // INC_INVENTORYSYSTEM_H_
