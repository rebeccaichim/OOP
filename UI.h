#ifndef UI_H
#define UI_H

#include "Controller.h"
#include "Repository.h"
#include <map>
enum class UserRole {
    Unknown,
    Manager,
    Customer
};

class UserInterface {
public:
    UserInterface(unique_ptr<ElectricScooterController> controller);
    std::string storageMode_;

    void start();
    UserInterface() {
        repository_ = std::make_unique<CsvFileRepository>("C:\\Users\\Utilizator\\CLionProjects\\Lab5OOP\\data.csv");

    }

    void setStorageMode();
private:
    std::unique_ptr<CsvFileRepository> repository_;
    std::map<string, vector<ElectricScooter*>> reservedScootersByClient;

    std::string fileName_;
    unique_ptr<ElectricScooterController> controller_;
    UserRole role_;
    void loadDataFromFile();
    void saveDataToFile();
    ScooterStatus mapToScooterStatus(const std::string& statusString);
    void listReservedElectricScooters(const std::string& clientName);
    void displayAvailableElectricScooters();
    void reserveElectricScooter(const std::string& clientName);
    void displayRoleSelection();
    void displayManagerMenu();
    void displayCustomerMenu();
    std::string mapToString(const ScooterStatus& status);

    void handleManagerInput();
    void handleCustomerInput();

    void addElectricScooter();
    void deleteElectricScooter();
    void editElectricScooter();
    void searchElectricScootersByLocation();
    void filterElectricScootersByAge();
    void filterElectricScootersByMileage();
    void getAllElectricScootersSortedByAge();
    void modifyElectricScooterStatus();
};

#endif // UI_H
