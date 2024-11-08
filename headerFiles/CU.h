#ifndef CU_H
#define CU_H

#include "Memory.h"
#include <stdexcept>
#include <string>

class CU {
private:
    int programCounter = 0;

public:
    int getProgramCounter() const;
    void incrementProgramCounter();
    void jumpTo(int address);
};

#endif