#include "Fleet.hpp"
#include <cmath>

void Fleet::add(unique_ptr<InventoryItem> item) {
    if (!item) {
        throw InvalidArgument("Нельзя добавить пустую позицию");
    }
    if (find_index(item->inventory_id()) != -1) {
        throw InvalidArgument("Позиция с таким инвентарным номером уже существует");
    }
    const Transport* if_transport = dynamic_cast<const Transport*>(item.get());
    if (if_transport) {
        service_.inspect(*if_transport);
    }
    shared_ptr<InventoryItem> accepted(std::move(item));
    items_.add(accepted);
}

int Fleet::find_index(const string& id) const {
    for (int i = 0; i < (int)items_.size(); ++i) {
        if (items_[i]->inventory_id() == id) {
            return i;
        }
    }
    return -1;
}

void Fleet::remove(const string& id) {
    int index = find_index(id);
    if (index == -1) {
        throw InvalidArgument("Позиция с таким номером не найдена");
    }
    items_.remove(index);
}

size_t Fleet::size() const {
    return items_.size();
}

void Fleet::focus(const string& id) {
    int index = find_index(id);
    if (index == -1) {
        throw InvalidArgument("Позиция с таким номером не найдена");
    }
    focus_ = items_[index];
}

void Fleet::show_focus() const {
    auto item = focus_.lock();
    if (item) {
        cout << *item << '\n';
    } else {
        cout << "expired" << '\n';
    }
}

void Fleet::list() const {
    cout << items_;
}

double Fleet::total_energy() const {
    double ans = 0;
    for (size_t i = 0; i < items_.size(); ++i) {
        auto is_energy = dynamic_cast<const EnergyConsumer*>(items_[i].get());
        if (is_energy) {
            ans += is_energy->daily_energy();
        }
    }
    return ans;
}

void Fleet::novice() const {
    for (size_t i = 0; i < items_.size(); ++i) {
        auto is_transport = dynamic_cast<const Transport*>(items_[i].get());
        if (is_transport && is_transport->novice_score() >= novice_minimum_) {
            cout << *is_transport << '\n';
        }
    }
}

void Fleet::can_carry(double weight) const {
    if (!isfinite(weight) || weight <= 0) {
        throw InvalidArgument("Вес груза должен быть положительным конечным числом");
    }
    for (size_t i = 0; i < items_.size(); ++i) {
        auto is_transport = dynamic_cast<const Transport*>(items_[i].get());
        if (is_transport && is_transport->cargo_capacity() >= weight) {
            cout << *is_transport << '\n';
        }
    }
}

void Fleet::set_novice_minimum(int minimum) {
    if (minimum < 1 || minimum > 10) {
        throw InvalidArgument("Порог простоты должен быть от 1 до 10");
    }
    novice_minimum_ = minimum;
}