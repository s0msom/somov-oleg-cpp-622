#pragma once

#include "Inventory.hpp"

using namespace std;

class Helmet : public InventoryItem {
private:
    string id_;
    string name_;
public:
    Helmet(const string& id, const string& name);
    string inventory_id() const override;
    string name() const override;
    void describe() const override;
};

class Dock : public InventoryItem, public EnergyConsumer {
private:
    string id_;
    string name_;
    double energy_;
public:
    Dock(const string& id, const string& name, double energy);
    string inventory_id() const override;
    string name() const override;
    void describe() const override;
    double daily_energy() const override;
};
