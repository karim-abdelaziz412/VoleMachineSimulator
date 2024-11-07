#ifndef CU_H
#define CU_H

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

#endif // CU_H