#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <stdexcept>
#include "Memory.h"
#include "Register.h"
#include "ALU.h"
#include "CU.h"

class CPU {
private:
    Register reg;
    ALU alu;
    CU cu;
    Memory* memory;
    unsigned char instructionRegister;

public:
    CPU(Memory* mem);
    void fetch();
    void execute();
    void displayState() const;
    void displayScreen() const;
};

#endif