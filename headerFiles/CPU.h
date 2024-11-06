#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include "Register.h"
#include "ALU.h"
#include "CU.h"
#include <iostream>

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

#endif // CPU_H
