#include "Operator.h"
#include "ElectricScooter.h"
using namespace domain;
std::ostream& operator<<(std::ostream& os, const domain::ElectricScooter& scooter) {
    os << scooter.getIdentifier() << ' '
       << scooter.getModel() << ' '
       << scooter.getCommissioningDate() << ' '
       << scooter.getKilometers() << ' '
       << scooter.getLastLocation() << ' '
       << static_cast<int>(scooter.getStatus());
    return os;
}
