#ifndef MEMORY_H
#define MEMORY_H

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

using namespace std;

void Outofrange(const string& context, int index);
string toHex(int value);

class Memory {
public:
    static const int memorySize = 256;
    array<unsigned char, memorySize> mem{0};
    bool programLoaded = false;

    void loadProgram(const vector<string>& program);
    bool isProgramLoaded() const;
    unsigned char get(int address) const;
    void display() const;
    void displayScreen() const;
    void setFloat(int address, float value);
    float getFloat(int address) const;
};

#endif