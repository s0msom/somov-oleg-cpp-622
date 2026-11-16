#pragma once

#include <memory>
#include <string>

#include "Inventory.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"

using namespace std;

class Fleet {
private:
    Registry<shared_ptr<InventoryItem>, 100> items_;
    ServiceCenter service_;
    weak_ptr<InventoryItem> focus_;
    int find_index(const string& id) const;
    int novice_minimum_ = 6;
public:
    void add(unique_ptr<InventoryItem> item);
    void remove(const string& id);
    size_t size() const;
    void focus(const string& id);
    void show_focus() const;
    void list() const;
    double total_energy() const;
    void novice() const;
    void set_novice_minimum(int minimum);
    void can_carry(double weight) const;
};