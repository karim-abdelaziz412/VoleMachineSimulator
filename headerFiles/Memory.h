#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>
#include <iostream>

class Memory {
public:
    static const int memorySize = 256;
    std::array<unsigned char, memorySize> mem{0};

    void loadProgram(const std::vector<std::string>& program);
    unsigned char get(int address) const;
    void set(int address, unsigned char value);
    void display() const;
    void displayScreen() const;
    void setFloat(int address, float value);
    float getFloat(int address) const;
};

#endif // MEMORY_H
