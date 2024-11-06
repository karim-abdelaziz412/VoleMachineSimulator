#include "CPU.h"

CPU::CPU(Memory* mem) : memory(mem), instructionRegister(0) {}

void CPU::fetch() {
    instructionRegister = memory->get(cu.getProgramCounter());
    cu.incrementProgramCounter();
}

void CPU::execute() {
    if (cu.getProgramCounter() >= Memory::memorySize) {
        throw std::runtime_error("Program counter out of range: " + std::to_string(cu.getProgramCounter()));
    }

    unsigned char operationcode = (instructionRegister & 0xF0) >> 4;
    unsigned char operand1 = (instructionRegister & 0x0F);

    if (cu.getProgramCounter() >= Memory::memorySize) {
        throw std::runtime_error("Memory address out of range during operand fetch: " + std::to_string(cu.getProgramCounter()));
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
                std::cout << "Writing to screen: " << reg.get(operand1) << std::endl;
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
            std::cout << "Halting execution" << std::endl;
            throw std::runtime_error("Execution halted by HALT instruction");
        default:
            std::cout << "Invalid opcode: " << static_cast<int>(operationcode) << std::endl;
            break;
    }
}

void CPU::displayState() const {
    reg.display();
    memory->display();
    std::cout << "Program Counter: " << cu.getProgramCounter() << std::endl;
    std::cout << "Instruction Register: " << std::hex << static_cast<int>(instructionRegister) << std::dec << std::endl;
}

void CPU::displayScreen() const {
    memory->displayScreen();
}
