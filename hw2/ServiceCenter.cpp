#include "ServiceCenter.hpp"
#include "Errors.hpp"

using namespace std;

void ServiceCenter::inspect(const Transport& transport) const {
    string nm = transport.name();
    for (auto &i : nm) {
        if ('A' <= i && i <= 'Z') {
            i = i - 'A' + 'a';
        }
    }
    if (nm.find("broken") != string::npos) {
        throw InspectionRejected("Транспорт не прошёл техосмотр");
    }
}
