#include "Machine.h"
#include <limits>

Machine::Machine() : cpu(std::make_unique<CPU>(&memory)) {}

void Machine::loadProgramFromFile() {
    std::cout << "Enter file name to load program from: ";
    std::string filename;
    std::cin >> filename;
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::vector<std::string> program;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string code;
        while (ss >> code) {
            program.push_back(code);
        }
    }

    memory.loadProgram(program);
}

void Machine::runWhole() {
    std::cout << "Running program as a whole" << std::endl;
    try {
        while (true) {
            cpu->fetch();
            cpu->execute();
            cpu->displayScreen();
        }
    } catch (const std::runtime_error& e) {
        cpu->displayState();
        std::cout << "Program halted: " << e.what() << std::endl;
    }
}

void Machine::step() {
    std::cout << "Running step-by-step" << std::endl;
    try {
        while (true) {
            cpu->fetch();
            cpu->execute();
            cpu->displayScreen();
            cpu->displayState();
            std::cout << "Press Enter to continue to next step" << std::endl;
            std::cin.get();
        }
    } catch (const std::runtime_error& e) {
        cpu->displayState();
        std::cout << "Program halted: " << e.what() << std::endl;
    }
}

void Machine::displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Load Program from File\n";
    std::cout << "2. Run Program as Whole\n";
    std::cout << "3. Step through Program\n";
    std::cout << "4. Display State\n";
    std::cout << "5. Exit\n";
}

void Machine::menu() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                loadProgramFromFile();
                break;
            case 2:
                runWhole();
                break;
            case 3:
                step();
                break;
            case 4:
                cpu->displayState();
                break;
            case 5:
                std::cout << "Exiting the program" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again" << std::endl;
        }
    } while (choice != 5);
}
