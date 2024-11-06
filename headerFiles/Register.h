#ifndef REGISTER_H
#define REGISTER_H

#include <array>
#include <iostream>
#include <iomanip>

class Register {
public:
    static const int registerSize = 16;
    std::array<float, registerSize> reg{0.0f};

    void set(int index, float value);
    float get(int index) const;
    void display() const;
};

#endif // REGISTER_H
