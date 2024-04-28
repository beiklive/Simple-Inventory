#include "InventorySystem.h"


InventorySystem::InventorySystem()
{
    set_bag_capacity(16);
    set_max_weight(2000);
}

InventorySystem::~InventorySystem()
{
}

InventorySystem::InventorySystem(int capacity, int weight)
{
    set_bag_capacity(capacity);
    set_max_weight(weight);
}
void InventorySystem::set_bag_capacity(int capacity)
{
    _max_capacity = capacity;
    if (nullptr != items)
    {
        delete[] items;
    }
    //std::vector<Item>* items;
    items = new std::vector<Item>;
    for(int i = 0; i < capacity; ++i)
    {
        (*items).push_back(get_empty_item());
    }
}

Item InventorySystem::get_empty_item()
{
    return ItemManager::createEmptyItem();
}

int InventorySystem::get_total_value()
{
    int total_value = 0;
    for (auto it = items->begin(); it != items->end(); ++it)
    {
        total_value += (*it).quantity * (*it).value;
    }
    return total_value;
}

void InventorySystem::set_max_weight(int weight)
{
    _max_weight = weight;
}
int InventorySystem::get_max_weight()
{
    return _max_weight;
}
int InventorySystem::get_max_capacity()
{
    return _max_capacity;
}
int InventorySystem::get_current_weight()
{
    return _current_weight;
}
int InventorySystem::get_current_capacity()
{
    return _current_capacity;
}
Item InventorySystem::get_item_in_bag_by_pos(int pos)
{
    if (pos >= 0 && pos < _max_capacity)
    {
        return (*items)[pos];
    }
    else
    {
        return get_empty_item();
    }
}


int InventorySystem::add_item_to_bag(Item item)
{
    if (!is_bag_full())
    {
        if (is_item_in_bag(item))
        {
            int index = 0;
            for (auto it = items->begin(); it != items->end(); ++it)
            {   
                if ((*it).name == item.name && (*it).id == item.id)
                {
                    (*it).quantity += item.quantity;
                    _current_weight += item.weight * item.quantity;
                    return index;
                }
                index ++;
            }
        }
        else
        {
            if (_current_capacity < _max_capacity)
            {
                int pos = get_first_empty_pos_in_bag();
                add_item_to_bag(item, pos);
                return pos;
            }
        }

    }
    return -1;
}

bool InventorySystem::add_item_to_bag(Item item, int pos)
{
    if (!is_bag_full() && _current_capacity < _max_capacity && pos >= 0 && pos < _max_capacity)
    {
        (*items)[pos] = item;
        _current_capacity++;
        _current_weight += item.weight * item.quantity;
        return true;
    }
    return false;
}

bool InventorySystem::remove_item_from_bag(Item item, int count, int pos)
{
    if (!is_bag_empty() && pos >= 0 && pos < _max_capacity)
    {
        if (is_bag_pos_item_same(pos, item))
        {
            if (count > (*items)[pos].quantity)
            {
                count = (*items)[pos].quantity;
            }
            (*items)[pos].quantity -= count;
            _current_weight -= item.weight * count;
            if ((*items)[pos].quantity == 0)
            {
                reset_pos_from_bag(pos);
            }
            return true;
        }
    }
    return false;
}

bool InventorySystem::remove_item_from_bag(Item item)
{
    if (!is_bag_empty())
    {
        for (int i = 0; i < _max_capacity; ++i)
        {
            if (is_bag_pos_item_same(i, item))
            {
                remove_item_from_bag(item, (*items)[i].quantity, i);
            }
        }
        return true;
    }
    return false;
}

bool InventorySystem::reset_pos_from_bag(int pos)
{
    if (pos >= 0 && pos < _max_capacity)
    {
        (*items)[pos] = get_empty_item();
        _current_capacity--;
        return true;
    }
    return false;
}

bool InventorySystem::is_bag_full()
{
    return _current_weight >= _max_weight || _current_capacity >= _max_capacity;
}


bool InventorySystem::is_bag_empty()
{
    return _max_weight == 0;
}


bool InventorySystem::is_item_in_bag(Item item)
{
    bool found = false;
    for (auto it = items->begin(); it != items->end(); ++it)
    {
        if ((*it).name == item.name && (*it).id == item.id)
        {
            found = true;
            break;
        }
    }

    return found;
}


int InventorySystem::get_item_count_in_bag(Item item)
{
    int total_count = 0;
    bool found = false;
    for (auto it = items->begin(); it != items->end(); ++it)
    {
        if ((*it).name == item.name && (*it).id == item.id)
        {
            found = true;
            total_count += (*it).quantity;
        }
    }
    return found ? total_count : -1;
}

int InventorySystem::get_item_pos_in_bag(Item item)
{
    int pos = -1;
    for (int i = 0; i < _max_capacity; ++i)
    {
        if (is_bag_pos_item_same(i, item))
        {
            pos = i;
            break;
        }
    }
    return pos;
}


bool InventorySystem::is_bag_pos_empty(int pos)
{
    return (*items)[pos].id == 0;
}

bool InventorySystem::is_bag_pos_item_same(int pos, Item item)
{
    return (*items)[pos].name == item.name && (*items)[pos].id == item.id;
}

int InventorySystem::get_first_empty_pos_in_bag()
{
    if (_current_capacity < _max_capacity)
    {
        for (int i = 0; i < _max_capacity; ++i)
        {
            if (is_bag_pos_empty(i))
            {
                return i;
            }
        }
    }
    return -1;
}