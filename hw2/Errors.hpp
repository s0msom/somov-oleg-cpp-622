#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class FleetError : public runtime_error {
public:
    FleetError(const string& message) : runtime_error(message) {}
};

class InvalidArgument : public FleetError {
public:
    InvalidArgument(const string& message) : FleetError(message) {}
};

class InspectionRejected : public FleetError {
public:
    InspectionRejected(const string& message) : FleetError(message) {}
};

class RegistryFull : public FleetError {
public:
    RegistryFull(const string& message) : FleetError(message) {}
};
