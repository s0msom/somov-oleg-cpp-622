#include "Transport.hpp"

#include <cmath>
#include "Errors.hpp"

using namespace std;

Transport::Transport(const string& id, const string& name, int score) : id_(id), name_(name), score_(score) {
    if (id.empty()) {
        throw InvalidArgument("Инвентарный номер не должен быть пустым");
    }
    if (name.empty()) {
        throw InvalidArgument("Название не может быть пустым");
    }
    if (score < 1 || score > 10) {
        throw InvalidArgument("Оценка простоты управления должна быть от 1 до 10");
    }
}

string Transport::inventory_id() const {
    return id_;
}

string Transport::name() const {
    return name_;
}

int Transport::novice_score() const {
    return score_;
}

void Transport::describe() const {
    cout << id_ << ' ' << name_;
}

double Transport::cargo_capacity() const {
    return 0.0;
}

CargoBike::CargoBike(const string& id, const string& name, int score, double capacity): Transport(id, name, score), capacity_(capacity) {
    if (!isfinite(capacity) || capacity <= 0) {
        throw InvalidArgument("Грузоподъёмность должна быть положительным конечным числом");
    }
}

double CargoBike::cargo_capacity() const {
    return capacity_;
}

void CargoBike::describe() const {
    Transport::describe();
    cout << " грузоподъёмность = " << capacity_ << "кг";
}

Bike::Bike(const string& id, const string& name, int score) : Transport(id, name, score) {
}

Scooter::Scooter(const string& id, const string& name, double energy, int score) : Transport(id, name, score), energy_(energy) {
    if (!isfinite(energy) || energy < 0) {
        throw InvalidArgument("Расход энергии должен быть неотрицательным конечным числом");
    }
}

double Scooter::daily_energy() const {
    return energy_;
}

ElectricBike::ElectricBike(const string& id, const string& name, double energy, int score) : Transport(id, name, score), energy_(energy) {
    if (!isfinite(energy) || energy < 0) {
        throw InvalidArgument("Расход энергии должен быть неотрицательным конечным числом");
    }
}

double ElectricBike::daily_energy() const {
    return energy_;
}
