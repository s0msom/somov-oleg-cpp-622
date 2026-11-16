#pragma once

#include "Inventory.hpp"

class Transport : public InventoryItem {
private:
    string id_;
    string name_;
    int score_;

public:
    Transport(const string& id_, const string& name_, int score_);
    string inventory_id() const override;
    string name() const override;
    void describe() const override;
    virtual int novice_score() const;
    virtual double cargo_capacity() const;
};

class CargoBike : public Transport {
private:
    double capacity_;

public:
    CargoBike(const string& id, const string& name, int score, double capacity);
    double cargo_capacity() const override;
    void describe() const override;
};

class Bike : public Transport {
public:
    Bike(const string& id, const string& name, int score);
};

class Scooter : public Transport, public EnergyConsumer {
private:
    double energy_;

public:
    Scooter(const string& id, const string& name, double energy, int score);
    double daily_energy() const override;
};

class ElectricBike : public Transport, public EnergyConsumer {
private:
    double energy_;

public:
    ElectricBike(const string& id, const string& name, double energy, int score);
    double daily_energy() const override;
};
