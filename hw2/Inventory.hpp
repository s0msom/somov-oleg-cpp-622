#pragma once

#include <iostream>
#include <string>

using namespace std;

class InventoryItem {
public:
    virtual string inventory_id() const = 0;
    virtual string name() const = 0;
    virtual void describe() const = 0;
    virtual ~InventoryItem() = default;
};

class EnergyConsumer {
public:
    virtual double daily_energy() const = 0;
    virtual ~EnergyConsumer() = default;
};

ostream& operator<<(ostream& out, const InventoryItem& item);

bool operator<(const InventoryItem& a, const InventoryItem& b);

bool operator==(const InventoryItem& a, const InventoryItem& b);