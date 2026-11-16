#pragma once

#include "Transport.hpp"

using namespace std;

class ServiceCenter {
public:
    void inspect(const Transport& transport) const;
};
