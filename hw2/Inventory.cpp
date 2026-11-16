#include "Inventory.hpp"

ostream& operator<<(ostream& out, const InventoryItem& item) {
    out << item.inventory_id() << " " << item.name();
    return out;
}

bool operator<(const InventoryItem& a, const InventoryItem& b) {
    return a.inventory_id() < b.inventory_id();
}

bool operator==(const InventoryItem& a, const InventoryItem& b) {
    return a.inventory_id() == b.inventory_id();
}
