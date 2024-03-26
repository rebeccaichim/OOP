#include "Controller.h"

ElectricScooterController::ElectricScooterController(std::unique_ptr<Repository> repository)
        : repository_(std::move(repository)) {}

void ElectricScooterController::addElectricScooter(const std::string& identifier, const std::string& model,
                                                   const std::string& commissioningDate, double kilometers,
                                                   const std::string& lastLocation, ScooterStatus status) {
    std::unique_ptr<ElectricScooter> newScooter =
            std::make_unique<ElectricScooter>(identifier, model, commissioningDate, kilometers, lastLocation, status);

    repository_->addElectricScooter(std::move(newScooter));
}

void ElectricScooterController::deleteElectricScooter(const std::string& identifier) {
    repository_->deleteElectricScooter(identifier);
}

void ElectricScooterController::editElectricScooter(const std::string& identifier, const std::string& lastLocation,
                                                    const std::string& commissioningDate, double kilometers,
                                                    const std::string& model) {
    ElectricScooter updatedScooter(identifier, model, commissioningDate, kilometers, lastLocation, ScooterStatus::Parked);

    repository_->editElectricScooter(identifier, updatedScooter);
}

std::vector<ElectricScooter*> ElectricScooterController::searchElectricScootersByLocation(const std::string& location) {
    return repository_->searchElectricScootersByLocation(location);
}

std::vector<ElectricScooter*> ElectricScooterController::filterElectricScootersByAge(int maxAge) {
    return repository_->filterElectricScootersByAge(maxAge);
}

std::vector<ElectricScooter*> ElectricScooterController::filterElectricScootersByMileage(double maxMileage) {
    return repository_->filterElectricScootersByMileage(maxMileage);
}

std::vector<ElectricScooter*> ElectricScooterController::getAllElectricScootersSortedByAge() {
    return repository_->getAllElectricScootersSortedByAge();
}

void ElectricScooterController::modifyElectricScooterStatus(const std::string& identifier, const ScooterStatus& status) {
    ElectricScooter* scooter = repository_->findElectricScooterByIdentifier(identifier);
    if (scooter) {
        scooter->setStatus(status);
    } else {
        throw std::runtime_error("Electric scooter not found.");
    }
}

ElectricScooter* ElectricScooterController::findElectricScooterByIdentifier(const std::string& identifier) {
    return repository_->findElectricScooterByIdentifier(identifier);
}


