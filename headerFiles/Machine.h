#ifndef MACHINE_H
#define MACHINE_H

#include "Memory.h"
#include "CPU.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

class Machine {
private:
    Memory memory;
    std::unique_ptr<CPU> cpu;

public:
    Machine();
    void loadProgramFromFile();
    void runWhole();
    void step();
    void displayMenu();
    void menu();
};

#endif // MACHINE_H
