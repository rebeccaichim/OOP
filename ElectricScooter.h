#ifndef ELECTRICSCOOTER_H
#define ELECTRICSCOOTER_H

#include <string>
using std::string;

namespace domain{

// Statuses
    enum class ScooterStatus {
        Parked,
        Reserved,
        InUse,
        InMaintenance,
        OutOfService
    };

// Constructor
    class ElectricScooter {
    public:
        ElectricScooter(const string &identifier, const string &model, const string &commissioningDate,
                        double kilometers, const string &lastLocation, ScooterStatus status);

        // Getters and setters
        const string &getIdentifier() const;

        const string &getModel() const;

        const string &getCommissioningDate() const;

        double getKilometers() const;

        const string &getLastLocation() const;

        ScooterStatus getStatus() const;
        bool isReserved() const;

        void setStatus(ScooterStatus);
    private:
        string identifier_;
        string model_;
        string commissioningDate_;
        double kilometers_;
        string lastLocation_;
        ScooterStatus status_;
        string clientName_;
        bool reserved_;

    };

};
#endif // ELECTRICSCOOTER_H
