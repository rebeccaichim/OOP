#include "Repository.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "ElectricScooter.h"
using namespace domain;


// Implementarea metodelor clasei InMemoryRepository

void InMemoryRepository::addElectricScooter(std::unique_ptr<ElectricScooter> electricScooter) {
    items_.push_back(std::move(electricScooter));
}

void InMemoryRepository::deleteElectricScooter(const std::string& identifier) {
    items_.erase(
            std::remove_if(items_.begin(), items_.end(), [&](const std::unique_ptr<ElectricScooter>& scooter) {
                return scooter->getIdentifier() == identifier;
            }),
            items_.end());
}

void InMemoryRepository::editElectricScooter(const std::string& identifier, const ElectricScooter& updatedScooter) {
    for (const auto& scooter : items_) {
        if (scooter->getIdentifier() == identifier) {
            *scooter = updatedScooter;
            break;
        }
    }
}

std::vector<ElectricScooter*> InMemoryRepository::searchElectricScootersByLocation(const std::string& location) {
    std::vector<ElectricScooter*> result;
    for (const auto& scooter : items_) {
        if (scooter->getLastLocation() == location) {
            result.push_back(scooter.get());
        }
    }
    return result;
}

std::vector<ElectricScooter*> InMemoryRepository::filterElectricScootersByAge(int maxAge) {
    std::vector<ElectricScooter*> result;

    // Get the current time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Iterate over electric scooters
    for (const auto& scooter : items_) {
        // Parse the commissioning date string
        std::istringstream iss(scooter->getCommissioningDate());
        std::tm commissioningDate{};
        iss >> std::get_time(&commissioningDate, "%Y-%m-%d");

        // Check if the parsing was successful
        if (!iss.fail()) {
            // Convert the commissioning date to std::time_t
            std::time_t commissioningTime = std::mktime(&commissioningDate);

            // Calculate age in seconds
            std::time_t ageSeconds = currentTime - commissioningTime;

            // Calculate age in years
            const int secondsPerYear = 60 * 60 * 24 * 365;  // Assuming a year has 365 days
            int ageYears = static_cast<int>(ageSeconds) / secondsPerYear;

            // Add scooter to result if age is less than or equal to maxAge
            if (ageYears <= maxAge) {
                result.push_back(scooter.get());
            }
        }
    }

    return result;
}

std::vector<ElectricScooter*> InMemoryRepository::filterElectricScootersByMileage(double maxMileage) {
    std::vector<ElectricScooter*> result;
    for (const auto& scooter : items_) {
        if (scooter->getKilometers() <= maxMileage) {
            result.push_back(scooter.get());
        }
    }
    return result;
}

std::vector<ElectricScooter*> InMemoryRepository::getAllElectricScootersSortedByAge() {
    std::vector<ElectricScooter*> result;

    // Sort electric scooters by age in ascending order
    sort(items_.begin(), items_.end(),
         [](const std::unique_ptr<ElectricScooter>& a, const std::unique_ptr<ElectricScooter>& b) {
             return a->getCommissioningDate() < b->getCommissioningDate();
         });

    // Add each scooter to the result vector
    for (const auto& scooter : items_) {
        result.push_back(scooter.get());
    }

    return result;
}


ElectricScooter* InMemoryRepository::findElectricScooterByIdentifier(const std::string& identifier) {
    for (const auto& scooter : items_) {
        if (scooter->getIdentifier() == identifier) {
            return scooter.get();
        }
    }
    return nullptr;
}


// Implementarea metodelor clasei CsvFileRepository

void CsvFileRepository::addElectricScooter(std::unique_ptr<ElectricScooter> electricScooter) {
    items_.push_back(std::move(electricScooter));
    saveToFile(filename_);
}

void CsvFileRepository::deleteElectricScooter(const std::string& identifier) {
    items_.erase(
            std::remove_if(items_.begin(), items_.end(), [&](const std::unique_ptr<ElectricScooter>& scooter) {
                return scooter->getIdentifier() == identifier;
            }),
            items_.end());
    saveToFile(filename_);
}

void CsvFileRepository::editElectricScooter(const std::string& identifier, const ElectricScooter& updatedScooter) {
    for (const auto &scooter: items_) {
        if (scooter->getIdentifier() == identifier) {
            *scooter = updatedScooter;
            break;
        }
    }
}
std::vector<ElectricScooter*> CsvFileRepository::searchElectricScootersByLocation(const std::string& location) {
    std::vector<ElectricScooter*> result;
    for (const auto& scooter : items_) {
        if (scooter->getLastLocation() == location) {
            result.push_back(scooter.get());
        }
    }
    return result;
}
std::vector<ElectricScooter*> CsvFileRepository::filterElectricScootersByAge(int maxAge) {
    std::vector<ElectricScooter*> result;

    // Get the current time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Iterate over electric scooters
    for (const auto& scooter : items_) {
        // Parse the commissioning date string
        std::istringstream iss(scooter->getCommissioningDate());
        std::tm commissioningDate{};
        iss >> std::get_time(&commissioningDate, "%Y-%m-%d");

        // Check if the parsing was successful
        if (!iss.fail()) {
            // Convert the commissioning date to std::time_t
            std::time_t commissioningTime = std::mktime(&commissioningDate);

            // Calculate age in seconds
            std::time_t ageSeconds = currentTime - commissioningTime;

            // Calculate age in years
            const int secondsPerYear = 60 * 60 * 24 * 365;  // Assuming a year has 365 days
            int ageYears = static_cast<int>(ageSeconds) / secondsPerYear;

            // Add scooter to result if age is less than or equal to maxAge
            if (ageYears <= maxAge) {
                result.push_back(scooter.get());
            }
        }
    }

    return result;
}

std::vector<ElectricScooter*> CsvFileRepository::filterElectricScootersByMileage(double maxMileage) {
    std::vector<ElectricScooter*> result;
    for (const auto& scooter : items_) {
        if (scooter->getKilometers() <= maxMileage) {
            result.push_back(scooter.get());
        }
    }
    return result;
}

std::vector<ElectricScooter*> CsvFileRepository::getAllElectricScootersSortedByAge() {
    std::vector<ElectricScooter*> result;

    // Sort electric scooters by age in ascending order
    sort(items_.begin(), items_.end(),
         [](const std::unique_ptr<ElectricScooter>& a, const std::unique_ptr<ElectricScooter>& b) {
             return a->getCommissioningDate() < b->getCommissioningDate();
         });

    // Add each scooter to the result vector
    for (const auto& scooter : items_) {
        result.push_back(scooter.get());
    }

    return result;
}
ElectricScooter* CsvFileRepository::findElectricScooterByIdentifier(const std::string& identifier) {
    for (const auto& scooter : items_) {
        if (scooter->getIdentifier() == identifier) {
            return scooter.get();
        }
    }
    return nullptr;
}
void CsvFileRepository::saveToFile(const std::string& filename)
{
    std::ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        throw std::runtime_error("Failed to open file : " + filename);
    }

    if (items_.empty())
    {
        throw std::runtime_error("No items to save in the CSV file.");
    }

    for (const auto& item : items_)
    {
        const domain::ElectricScooter& scooter = *item;

        outputFile << scooter.getIdentifier() << ","
                   << scooter.getModel() << ","
                   << scooter.getCommissioningDate() << ","
                   << scooter.getKilometers() << ","
                   << scooter.getLastLocation() << ","
                   << static_cast<int>(scooter.getStatus()) << std::endl;

        if (!outputFile)
        {
            throw std::runtime_error("Failed to write data to the CSV file: " + filename);
        }
    }

    outputFile.close();

    if (outputFile.fail())
    {
        throw std::runtime_error("Failed to close the CSV file properly: " + filename);
    }
}

void CsvFileRepository::loadFromFile(const std::string& filename)
{
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::string identifier;
        std::string model;
        std::string commissioningDate;
        double kilometers;
        std::string lastLocation;
        std::string statusStr;

        if (std::getline(ss, identifier, ',') &&
            std::getline(ss, model, ',') &&
            std::getline(ss, commissioningDate, ',') &&
            ss >> kilometers && ss.ignore() &&
            std::getline(ss, lastLocation, ',') &&
            std::getline(ss, statusStr))
        {
            ScooterStatus status;
            if (statusStr == "Parked") {
                status = ScooterStatus::Parked;
            } else if (statusStr == "InUse") {
                status = ScooterStatus::InUse;
            } else if (statusStr == "InMaintenance") {
                status = ScooterStatus::InMaintenance;
            } else if (statusStr == "OutOfService") {
                status = ScooterStatus::OutOfService;
            } else if (statusStr == "Reserved") {
                status = ScooterStatus::Reserved;
            } else {
                throw std::runtime_error("Invalid scooter status: " + statusStr);
            }
            domain::ElectricScooter scooter(identifier, model, commissioningDate, kilometers, lastLocation, status);

            items_.push_back(std::make_unique<domain::ElectricScooter>(std::move(scooter)));
        }
        else
        {
            throw std::runtime_error("Invalid line in file: " + line);
        }
    }

    inputFile.close();
}