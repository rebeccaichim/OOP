#ifndef ELECTRICSCOOTERCONTROLLER_H
#define ELECTRICSCOOTERCONTROLLER_H
#include "Repository.h"
#include <memory>
#include <string>
using std::unique_ptr;
using std::vector;
class ElectricScooterController {
public:
    ElectricScooterController(unique_ptr<Repository> repository);

    void addElectricScooter(const string& identifier, const string& model,
                            const string& commissioningDate, double kilometers,
                            const string& lastLocation, ScooterStatus status);

    void deleteElectricScooter(const string& identifier);
    void editElectricScooter(const string& identifier, const string& lastLocation, const string& commissioningDate, double kilometers, const string& model);
    vector<ElectricScooter*> searchElectricScootersByLocation(const string& location);
    vector<ElectricScooter*> filterElectricScootersByAge(int maxAge);
    vector<ElectricScooter*> filterElectricScootersByMileage(double maxMileage);
    std::vector<ElectricScooter*> getAllElectricScootersSortedByAge();
    void modifyElectricScooterStatus(const string& identifier, const ScooterStatus& status);
    ElectricScooter* findElectricScooterByIdentifier(const string& identifier);

    vector<ElectricScooter*> getAvailableElectricScooters() const;

private:
    unique_ptr<Repository> repository_;
    vector<ElectricScooter*> scooters_;

    vector<unique_ptr<ElectricScooter>> electricScooters_;

};

#endif // ELECTRICSCOOTERCONTROLLER_H
