#include <iostream>
#include <memory>
#include "UI.h"
#include "Controller.h"
#include "Repository.h"
#include "Tests.h"
using namespace std;
int main() {
    testAll();
    cout << "Tests over!" << endl << endl;
    // Create a repository and controller
    std::unique_ptr<Repository> repository = std::make_unique<InMemoryRepository>();
    std::unique_ptr<ElectricScooterController> controller = std::make_unique<ElectricScooterController>(std::move(repository));


    // Create the user interface with the controller
    UserInterface ui(std::move(controller));

    // Start the user interface
    ui.start();

    return 0;
}
