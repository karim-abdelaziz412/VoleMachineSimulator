#include "CPU.h"
#include <iostream>
#include <stdexcept>

CPU::CPU(Memory* mem) : memory(mem), instructionRegister(0) {}

void CPU::fetch() {
    instructionRegister = memory->get(cu.getProgramCounter());
    cu.incrementProgramCounter();
}

void CPU::execute() {
    if (!memory->isProgramLoaded()) {
        cout << "No program loaded. Halting execution." << endl;
        throw runtime_error("Execution halted due to lack of program.");
    }

    if (cu.getProgramCounter() >= Memory::memorySize) {
        throw runtime_error("Program counter out of range: " + to_string(cu.getProgramCounter()));
    }

    unsigned char operationcode = (instructionRegister & 0xF0) >> 4;
    unsigned char operand1 = (instructionRegister & 0x0F);

    if (cu.getProgramCounter() >= Memory::memorySize) {
        throw runtime_error("Memory address out of range during operand fetch: " + to_string(cu.getProgramCounter()));
    }

    unsigned char operand2 = memory->get(cu.getProgramCounter());
    cu.incrementProgramCounter();

    switch (operationcode) {
        case 0x1:
            reg.set(operand1, memory->getFloat(operand2));
            break;
        case 0x2:
            reg.set(operand1, static_cast<float>(operand2));
            break;
        case 0x3:
            if (operand1 == 0) {
                cout << "Writing to screen: " << reg.get(operand1) << endl;
            } else {
                memory->setFloat(operand2, reg.get(operand1));
            }
            break;
        case 0x4:
            reg.set(operand2, reg.get(operand1));
            break;
        case 0x5:
            reg.set(operand1, alu.addFloat(reg.get(operand1), reg.get(operand2)));
            break;
        case 0x6:
            reg.set(operand1, alu.addFloat(reg.get(operand1), reg.get(operand2)));
            break;
        case 0xB:
            if (reg.get(operand1) == 0) {
                cu.jumpTo(operand2);
            }
            break;
        case 0xC:
            cout << "Halting execution" << endl;
            throw runtime_error("Execution halted by HALT instruction");
        default:
            cout << "Invalid opcode: " << uppercase << static_cast<int>(operationcode) << endl;
            break;
    }
}

void CPU::displayState() const {
    reg.display();
    memory->display();
    cout << "Program Counter: " << cu.getProgramCounter() << endl;
    cout << "Instruction Register: " << uppercase << hex << static_cast<int>(instructionRegister) << dec << endl;
}

void CPU::displayScreen() const {
    memory->displayScreen();
}