#include <cassert>
#include <memory>
#include <vector>
#include "ElectricScooter.h"
#include "Repository.h"

void testElectricScooter() {
    // Create an ElectricScooter object
    domain::ElectricScooter scooter("ES001", "Model1", "2022-01-01", 100.0, "Location1", domain::ScooterStatus::Parked);

    // Test getters
    assert(scooter.getIdentifier() == "ES001");
    assert(scooter.getModel() == "Model1");
    assert(scooter.getCommissioningDate() == "2022-01-01");
    assert(scooter.getKilometers() == 100.0);
    assert(scooter.getLastLocation() == "Location1");
    assert(scooter.getStatus() == domain::ScooterStatus::Parked);

    // Test setter
    scooter.setStatus(domain::ScooterStatus::Reserved);
    assert(scooter.getStatus() == domain::ScooterStatus::Reserved);
}

void testInMemoryRepository() {
    // Create an InMemoryRepository object
    std::unique_ptr<Repository> repository = std::make_unique<InMemoryRepository>();

    // Create ElectricScooter objects
    std::unique_ptr<domain::ElectricScooter> scooter1 =
            std::make_unique<domain::ElectricScooter>("ES001", "Model1", "2022-01-01", 100.0, "Location1", domain::ScooterStatus::Parked);
    std::unique_ptr<domain::ElectricScooter> scooter2 =
            std::make_unique<domain::ElectricScooter>("ES002", "Model2", "2022-02-01", 200.0, "Location2", domain::ScooterStatus::Reserved);

    // Add ElectricScooter objects to the repository
    repository->addElectricScooter(std::move(scooter1));
    repository->addElectricScooter(std::move(scooter2));

    // Test searchElectricScootersByLocation method
    std::vector<domain::ElectricScooter*> searchResult = repository->searchElectricScootersByLocation("Location1");
    assert(searchResult.size() == 1);
    assert(searchResult[0]->getIdentifier() == "ES001");

    // Test filterElectricScootersByAge method
    std::vector<domain::ElectricScooter*> filterResult = repository->filterElectricScootersByAge(1);
    assert(filterResult.size() == 2);

    // Test getAllElectricScootersSortedByAge method
    std::vector<domain::ElectricScooter*> sortedResult = repository->getAllElectricScootersSortedByAge();
    assert(sortedResult.size() == 2);
    assert(sortedResult[0]->getIdentifier() == "ES001");
    assert(sortedResult[1]->getIdentifier() == "ES002");
}



void testAll() {
    testElectricScooter();
    testInMemoryRepository();
}
