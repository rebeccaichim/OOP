#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <unordered_map>
#include "ElectricScooter.h"
#include <vector>
#include <memory>
#include <iostream>
using namespace domain;
class Repository {
public:
    virtual void addElectricScooter(std::unique_ptr<ElectricScooter> electricScooter) = 0;
    virtual void deleteElectricScooter(const std::string& identifier) = 0;
    virtual void editElectricScooter(const std::string& identifier, const ElectricScooter& updatedScooter) = 0;
    virtual std::vector<ElectricScooter*> searchElectricScootersByLocation(const std::string& location) = 0;
    virtual std::vector<ElectricScooter*> filterElectricScootersByAge(int maxAge) = 0;
    virtual std::vector<ElectricScooter*> filterElectricScootersByMileage(double maxMileage) = 0;
    virtual std::vector<ElectricScooter*> getAllElectricScootersSortedByAge() = 0;
    virtual ElectricScooter* findElectricScooterByIdentifier(const std::string& identifier) = 0;

protected:
    std::vector<std::unique_ptr<ElectricScooter>> items_;


};

class InMemoryRepository : public Repository {
private:
    std::unordered_map<std::string, std::vector<ElectricScooter*>> reservedScootersByClient;

public:

    void addElectricScooter(std::unique_ptr<ElectricScooter> electricScooter) override;
    void deleteElectricScooter(const std::string& identifier) override;
    void editElectricScooter(const std::string& identifier, const ElectricScooter& updatedScooter) override;
    std::vector<ElectricScooter*> searchElectricScootersByLocation(const std::string& location) override;
    std::vector<ElectricScooter*> filterElectricScootersByAge(int maxAge) override;
    std::vector<ElectricScooter*> filterElectricScootersByMileage(double maxMileage) override;
    std::vector<ElectricScooter*> getAllElectricScootersSortedByAge() override;
    ElectricScooter* findElectricScooterByIdentifier(const std::string& identifier) override;
};

class CsvFileRepository : public Repository {
private:
    std::string filename_;


public:

    CsvFileRepository(const std::string& filename) : filename_(filename) {}
    void saveToFile(const std::string& filename = "C:\\Users\\User\\Lab6OOP\\data.csv");
    void addElectricScooter(std::unique_ptr<ElectricScooter> electricScooter) override;
    void deleteElectricScooter(const std::string& identifier) override;
    void editElectricScooter(const std::string& identifier, const ElectricScooter& updatedScooter) override;
    std::vector<ElectricScooter*> searchElectricScootersByLocation(const std::string& location) override;
    std::vector<ElectricScooter*> filterElectricScootersByAge(int maxAge) override;
    std::vector<ElectricScooter*> filterElectricScootersByMileage(double maxMileage) override;
    std::vector<ElectricScooter*> getAllElectricScootersSortedByAge() override;
    ElectricScooter* findElectricScooterByIdentifier(const std::string& identifier) override;
    void loadFromFile(const std::string& filename = "C:\\Users\\User\\Lab6OOP\\data.csv");
};

#endif // REPOSITORY_H