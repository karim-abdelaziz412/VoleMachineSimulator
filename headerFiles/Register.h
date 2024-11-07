#ifndef REGISTER_H
#define REGISTER_H

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

class Register {
public:
    static const int registerSize = 16;
    array<float, registerSize> reg{0.0f};

    void set(int index, float value);
    float get(int index) const;
    void display() const;
};

#endif // REGISTER_H