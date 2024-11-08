#ifndef MACHINE_H
#define MACHINE_H

#include "CPU.h"
#include "Memory.h"
#include <memory>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <limits>
#include <array>
#include <memory>
#include <sstream>
#include <fstream>
#include <cstring>

class Machine {
private:
    Memory memory;
    unique_ptr<CPU> cpu;

public:
    Machine();
    void loadProgramFromFile();
    void runWhole();
    void step();
    void displayMenu();
    void menu();
};

#endif