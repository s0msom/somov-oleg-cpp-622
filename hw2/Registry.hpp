#pragma once

#include "Errors.hpp"
#include "Inventory.hpp"
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

template<typename T>
void print_registry_value(ostream& out, const T& value) {
    out << value;
}

template<>
inline void print_registry_value<shared_ptr<InventoryItem>>(ostream& out, const shared_ptr<InventoryItem>& value) {
    if (value) {
        out << *value;
    } else {
        out << "Пустая позиция";
    }
}

template<typename T>
bool registry_less(const T& a, const T& b) {
    return a < b;
}

template<>
inline bool registry_less<shared_ptr<InventoryItem>>(const shared_ptr<InventoryItem>& a, const shared_ptr<InventoryItem>& b) {
    return *a < *b;
}

template<typename T, size_t Cap>
class Registry {
private:
    vector<T> items_;
public:
    size_t size() const {
        return items_.size();
    }
    void add(T item) {
        if (items_.size() == Cap) {
            throw RegistryFull("Достигнута максимальная вместимость");
        }
        items_.push_back(std::move(item));
    }
    const T& operator[](int index) const {
        if (index < 0 || (size_t)index >= items_.size()) {
            throw InvalidArgument("Индекс находится за пределами реестра");
        }
        return items_[index];
    }
    void remove(int index) {
        if (index < 0 || (size_t)index >= items_.size()) {
            throw InvalidArgument("Индекс находится за пределами реестра");
        }
        items_.erase(items_.begin() + index);
    }
};

template<typename T, size_t Cap>
ostream& operator<<(ostream& out, const Registry<T, Cap>& registry) {
    vector<T> sorted;
    for (size_t i = 0; i < registry.size(); ++i) {
        sorted.push_back(registry[(int)i]);
    }
    std::sort(sorted.begin(), sorted.end(), registry_less<T>);
    for (auto& value : sorted) {
        print_registry_value(out, value);
        out << '\n';
    }
    return out;
}