#include "CU.h"
#include "Memory.h"


int CU::getProgramCounter() const {
    return programCounter;
}

void CU::incrementProgramCounter() {
    ++programCounter;
}

void CU::jumpTo(int address) {
    if (address < 0 || address >= Memory::memorySize) {
        throw runtime_error("Jump address out of range: " + to_string(address));
    }
    programCounter = address;
}