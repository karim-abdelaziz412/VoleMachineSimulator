#include "CU.h"
#include "Memory.h"
int CU::getProgramCounter() const {
    return programCounter;
}

void CU::setProgramCounter(int pc) {
    programCounter = pc;
}

void CU::incrementProgramCounter() {
    ++programCounter;
}

void CU::jumpTo(int address) {
    if (address < 0 || address >= Memory::memorySize) {
        throw std::runtime_error("Jump address out of range: " + std::to_string(address));
    }
    programCounter = address;
}
