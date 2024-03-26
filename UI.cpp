#include "UI.h"
#include "Operator.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using std::exception;
using namespace domain;


void UserInterface::listReservedElectricScooters(const string& clientName) {
    if (reservedScootersByClient.find(clientName) == reservedScootersByClient.end()) {
        cout << "No electric scooters reserved for client: " << clientName << endl;
    } else {
        cout << "Reserved electric scooters for client: " << clientName << endl;
        for (const auto& scooter : reservedScootersByClient[clientName]) {
            cout << *scooter << endl;
        }
    }
}

void UserInterface::setStorageMode() {
    cout << "Select storage mode:\n";
    cout << "1. Volatile (in-memory)\n";
    cout << "2. Persistent (CSV file)\n";
    int selection;
    cout << "Enter your choice: ";
    cin >> selection;

    switch (selection) {
        case 1:
            storageMode_ = "volatile";
            break;
        case 2: {
            CsvFileRepository* csvRepository = dynamic_cast<CsvFileRepository*>(repository_.get());
            if (csvRepository != nullptr) {
                cout << "Changes will be saved to the file." << endl;
                csvRepository->saveToFile();
            }
            break;
        }
        default:
            cout << "Invalid storage mode selection. Exiting...\n";
            exit(0);
    }
}

UserInterface::UserInterface(unique_ptr<ElectricScooterController> controller)
        : controller_(std::move(controller)), role_(UserRole::Unknown) {
}

void UserInterface::loadDataFromFile() {
    std::ifstream file("C:\\Users\\Utilizator\\CLionProjects\\Lab5OOP\\data.csv");

    if (!file) {
        cout << "Error: Failed to open data file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 6) {
            string identifier = tokens[0];
            string model = tokens[1];
            string commissioningDate = tokens[2];
            int kilometers = 0;
            try {
                kilometers = stoi(tokens[3]);
            } catch (const std::invalid_argument& e) {
                cout << "Error: Invalid kilometer value for electric scooter with identifier '" << identifier << "'. Skipping this entry." << endl;
                continue;  // Skip to the next entry
            }
            string lastLocation = tokens[4];
            ScooterStatus status;
            try {
                status = mapToScooterStatus(tokens[5]);
            } catch (const std::invalid_argument& e) {
                continue;  // Skip to the next entry
            }

            controller_->addElectricScooter(identifier, model, commissioningDate, kilometers, lastLocation, status);
        }
    }

    file.close();
}
ScooterStatus UserInterface::mapToScooterStatus(const std::string& statusString) {
    if (statusString == "InUse") {
        return ScooterStatus::InUse;
    } else if (statusString == "Parked") {
        return ScooterStatus::Parked;
    } else if (statusString == "Reserved") {
        return ScooterStatus::Reserved;
    } else if (statusString == "OutOfService") {
        return ScooterStatus::OutOfService;
    } else if (statusString == "InMaintenance") {
        return ScooterStatus::InMaintenance;
    } else {
        throw std::invalid_argument("Invalid scooter status: " + statusString);
    }
}

void UserInterface::saveDataToFile() {
    std::ofstream file("C:\\Users\\Utilizator\\CLionProjects\\Lab5OOP\\data.csv");
    if (!file) {
        cout << "Error: Failed to open data file." << endl;
        return;
    }

    const std::vector<ElectricScooter*> scooters = controller_->getAllElectricScootersSortedByAge();

    for (const auto& scooter : scooters) {
        file << scooter->getIdentifier() << ","
             << scooter->getModel() << ","
             << scooter->getCommissioningDate() << ","
             << scooter->getKilometers() << ","
             << scooter->getLastLocation() << ","
             << mapToString(scooter->getStatus()) << "\n";
    }

    file.close();
}

std::string UserInterface::mapToString(const ScooterStatus& status) {
    switch (status) {
        case ScooterStatus::InUse:
            return "InUse";
        case ScooterStatus::Parked:
            return "Parked";
        case ScooterStatus::Reserved:
            return "Reserved";
        case ScooterStatus::OutOfService:
            return "OutOfService";
        case ScooterStatus::InMaintenance:
            return "InMaintenance";
        default:
            throw std::invalid_argument("Invalid scooter status");
    }
}


// Function to start the user interface
void UserInterface::start() {
    loadDataFromFile();
    setStorageMode();
    cout << "Welcome to the Electric ElectricScooter Rental Company!" << endl;

    while (true) {
        displayRoleSelection();
        if (role_ == UserRole::Manager) {
            displayManagerMenu();
            handleManagerInput();
        } else if (role_ == UserRole::Customer) {
            displayCustomerMenu();
            handleCustomerInput();
        } else {
            cout << "Invalid role. Please try again." << endl;
        }
    }
}

// Function to display the role
void UserInterface::displayRoleSelection() {
    cout << "Select your role:" << endl;
    cout << "1. Manager" << endl;
    cout << "2. Customer" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        role_ = UserRole::Manager;
    } else if (choice == 2) {
        role_ = UserRole::Customer;
    } else {
        role_ = UserRole::Unknown;
    }
}

// Function to display manager menu
void UserInterface::displayManagerMenu() {
    cout << "\n----- Manager Menu -----" << endl;
    cout << "1. Add Electric ElectricScooter" << endl;
    cout << "2. Delete Electric ElectricScooter" << endl;
    cout << "3. Edit Electric ElectricScooter" << endl;
    cout << "4. Search Electric Scooters by Location" << endl;
    cout << "5. Filter Electric Scooters by Age" << endl;
    cout << "6. Filter Electric Scooters by Mileage" << endl;
    cout << "7. Get All Electric Scooters Sorted by Age" << endl;
    cout << "8. Modify Electric ElectricScooter Status" << endl;
    cout << "9. Exit" << endl;
}

// Function to display customer menu
void UserInterface::displayCustomerMenu() {
    cout << "\n----- Customer Menu -----" << endl;
    cout << "1. Search Electric Scooters by Location" << endl;
    cout << "2. Filter Electric Scooters by Age" << endl;
    cout << "3. Filter Electric Scooters by Mileage" << endl;
    cout << "4. Reserve Electric ElectricScooter" << endl;
    cout << "5. List Reserved Electric Scooters" << endl;
    cout << "6. Exit" << endl;
}

// Function to handle manager input
void UserInterface::handleManagerInput() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            addElectricScooter();
            break;
        case 2:
            deleteElectricScooter();
            break;
        case 3:
            editElectricScooter();
            break;
        case 4:
            searchElectricScootersByLocation();
            break;
        case 5:
            filterElectricScootersByAge();
            break;
        case 6:
            filterElectricScootersByMileage();
            break;
        case 7:
            getAllElectricScootersSortedByAge();
            break;
        case 8:
            modifyElectricScooterStatus();

            break;
        case 9:
            if (storageMode_ != "volatile") {
                saveDataToFile();
            }
            cout << "Exiting the program. Goodbye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

// Function to handle customer input
void UserInterface::handleCustomerInput() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            searchElectricScootersByLocation();
            break;
        case 2:
            filterElectricScootersByAge();
            break;
        case 3:
            filterElectricScootersByMileage();
            break;
        case 4: {
            string clientName;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, clientName);
            reserveElectricScooter(clientName);
            break;
        }
        case 5: {
            string clientName;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, clientName);
            listReservedElectricScooters(clientName);
            break;
        }
        case 6:
            if (storageMode_ != "volatile") {
                saveDataToFile();
            }
            cout << "Exiting the program. Goodbye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

// Add function
void UserInterface::addElectricScooter() {
    string identifier;
    string lastLocation;
    string commissioningDate;
    int kilometers;
    string model;

    cout << "Enter the electric scooter identifier: ";
    cin >> identifier;

    if (controller_->findElectricScooterByIdentifier(identifier)) {
        cout << "Error: Electric scooter with the same identifier already exists." << endl;
        return;
    }

    cout << "Enter the electric scooter model: ";
    cin >> model;

    cout << "Enter the electric scooter last location: ";
    cin >> lastLocation;

    cout << "Enter the electric scooter commissioning date (YYYY-MM-DD): ";
    cin >> commissioningDate;

    cout << "Enter the electric scooter kilometers: ";
    cin >> kilometers;

    try {
        controller_->addElectricScooter(identifier, model, commissioningDate, kilometers, lastLocation, domain::ScooterStatus::Parked);
        cout << "Electric scooter added successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


// Delete function
void UserInterface::deleteElectricScooter() {
    string identifier;

    cout << "Enter the electric scooter identifier: ";
    cin >> identifier;

    if (!controller_->findElectricScooterByIdentifier(identifier)) {
        cout << "Error: Electric scooter not found." << endl;
        return;
    }

    try {
        controller_->deleteElectricScooter(identifier);
        cout << "Electric scooter deleted successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}



// Edit function
void UserInterface::editElectricScooter() {
    string identifier;
    string lastLocation;
    string commissioningDate;
    int kilometers;
    string model;

    cout << "Enter the electric scooter identifier: ";
    cin >> identifier;

    ElectricScooter* scooter = controller_->findElectricScooterByIdentifier(identifier);
    if (scooter == nullptr) {
        cout << "Electric scooter with identifier '" << identifier << "' does not exist." << endl;
        return; // Exit the function early if the electric scooter doesn't exist
    }

    cout << "Enter the new model: ";
    cin >> model;

    cout << "Enter the new last location: ";
    cin >> lastLocation;

    cout << "Enter the new commissioning date (YYYY-MM-DD): ";
    cin >> commissioningDate;

    cout << "Enter the new kilometers: ";
    cin >> kilometers;

    try {
        controller_->editElectricScooter(identifier, lastLocation, commissioningDate, kilometers, model);
        cout << "Electric scooter updated successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Search by location function
void UserInterface::searchElectricScootersByLocation() {
    string location;

    cout << "Enter the location to search electric scooters: ";
    cin >> location;

    vector<ElectricScooter*> scooters = controller_->searchElectricScootersByLocation(location);

    if (scooters.empty()) {
        cout << "No electric scooters found at the specified location." << endl;
    } else {
        cout << "Electric scooters found at the specified location:" << endl;
        for (const auto& scooter : scooters) {
            cout << *scooter << endl;
        }
    }
}

// Filter by age function
void UserInterface::filterElectricScootersByAge() {
    int maxAge;


    cout << "Enter the maximum age in years: ";
    cin >> maxAge;

    vector<ElectricScooter*> scooters = controller_->filterElectricScootersByAge(maxAge);

    if (scooters.empty()) {
        cout << "No electric scooters found within the specified age limit." << endl;
    } else {
        cout << "Electric scooters found within the specified age limit:" << endl;
        for (const auto& scooter : scooters) {
            cout << *scooter << endl;
        }
    }
}

// Filter by mileage function
void UserInterface::filterElectricScootersByMileage() {
    double maximumMileage;

    cout << "Enter the maximum mileage: ";
    cin >> maximumMileage;

    vector<ElectricScooter*> scooters = controller_->filterElectricScootersByMileage(maximumMileage);

    if (scooters.empty()) {
        cout << "No electric scooters found with the specified mileage." << endl;
    } else {
        cout << "Electric scooters found with the specified mileage:" << endl;
        for (const auto& scooter : scooters) {
            cout << *scooter << endl;
        }
    }
}

// Get all sorted by age function
void UserInterface::getAllElectricScootersSortedByAge() {
    vector<ElectricScooter*> scooters = controller_->getAllElectricScootersSortedByAge();
    cout << "\n----- All Electric Scooters Sorted by Age -----" << endl;

    if (scooters.empty()) {
        cout << "No electric scooters found." << endl;
    } else {
        for (const auto& scooter : scooters) {
            cout << *scooter << endl;
        }
    }
}


// Reserve function
void UserInterface::reserveElectricScooter(const std::string& clientName) {
    cout << "Enter the ID of the scooter you want to reserve: ";
    std::string scooterId;
    std::cin >> scooterId;
    std::cin.ignore();

    ElectricScooter* scooter = controller_->findElectricScooterByIdentifier(scooterId);
    if (scooter == nullptr) {
        std::cout << "Invalid scooter ID. Reservation failed." << std::endl;
        return;
    }

    if (scooter->getStatus() != ScooterStatus::Parked) {
        std::cout << "The scooter is not available for reservation. Reservation failed." << std::endl;
        return;
    }

    scooter->setStatus(ScooterStatus::Reserved);

    reservedScootersByClient[clientName].push_back(scooter);

    std::cout << "Scooter reserved successfully!" << std::endl;
}


// Modify function
void UserInterface::modifyElectricScooterStatus() {
    string identifier;
    int statusChoice;

    cout << "Enter the electric scooter identifier: ";
    cin >> identifier;

    if (!controller_->findElectricScooterByIdentifier(identifier)) {
        cout << "Error: Electric scooter not found." << endl;
        return;
    }

    cout << "Select the new electric scooter status:" << endl;
    cout << "1. Parked" << endl;
    cout << "2. Reserved" << endl;
    cout << "3. In Use" << endl;
    cout << "4. In Maintenance" << endl;
    cout << "5. Out Of Service" << endl;
    cout << "Enter your choice: ";
    cin >> statusChoice;

    try {
        domain::ScooterStatus status;
        switch (statusChoice) {
            case 1:
                status = domain::ScooterStatus::Parked;
                break;
            case 2:
                status = domain::ScooterStatus::Reserved;
                break;
            case 3:
                status = domain::ScooterStatus::InUse;
                break;
            case 4:
                status = domain::ScooterStatus::InMaintenance;
                break;
            case 5:
                status = domain::ScooterStatus::OutOfService;
                break;
            default:
                throw std::invalid_argument("Invalid status choice.");
        }

        controller_->modifyElectricScooterStatus(identifier, status);
        cout << "Electric scooter status modified successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}