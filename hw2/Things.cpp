#include "Things.hpp"
#include "Errors.hpp"
#include <cmath>

Helmet::Helmet(const string& id, const string& name) : id_(id), name_(name) {
    if (id.empty()) {
        throw InvalidArgument("Инвентарный номер не должен быть пустым");
    }
    if (name.empty()) {
        throw InvalidArgument("Название не должно быть пустым");
    }
}

void Helmet::describe() const {
    cout << id_ << ' ' << name_;
}

string Helmet::inventory_id() const {
    return id_;
}

string Helmet::name() const {
    return name_;
}

void Dock::describe() const {
    cout << id_ << ' ' << name_;
}

string Dock::inventory_id() const {
    return id_;
}

string Dock::name() const {
    return name_;
}

double Dock::daily_energy() const {
    return energy_;
}

Dock::Dock(const string& id, const string& name, double energy) : id_(id), name_(name), energy_(energy) {
    if (id.empty()) {
        throw InvalidArgument("Инвентарный номер не должен быть пустым");
    }
    if (name.empty()) {
        throw InvalidArgument("Название не должно быть пустым");
    }
    if (!isfinite(energy) || energy < 0) {
        throw InvalidArgument("Расход энергии должен быть неотрицательным конечным числом");
    }
}

