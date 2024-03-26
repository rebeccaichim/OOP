#include "ElectricScooter.h"
using std::string;

namespace domain {
    ElectricScooter::ElectricScooter(const string &identifier, const string &model, const string &commissioningDate,
                                     double kilometers, const string &lastLocation, ScooterStatus status)
            : identifier_(identifier), model_(model), commissioningDate_(commissioningDate), kilometers_(kilometers),
              lastLocation_(lastLocation), status_(status) {
    }

// Getters and setters

    const string &ElectricScooter::getIdentifier() const {
        return identifier_;
    }

    const string &ElectricScooter::getModel() const {
        return model_;
    }

    const string &ElectricScooter::getCommissioningDate() const {
        return commissioningDate_;
    }

    double ElectricScooter::getKilometers() const {
        return kilometers_;
    }

    const string &ElectricScooter::getLastLocation() const {
        return lastLocation_;
    }

    ScooterStatus ElectricScooter::getStatus() const {
        return status_;
    }

    void ElectricScooter::setStatus(ScooterStatus status) {
        status_ = status;
    }
    bool ElectricScooter::isReserved() const {
        return reserved_;
    }


}
