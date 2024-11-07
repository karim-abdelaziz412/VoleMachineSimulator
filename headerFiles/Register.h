#ifndef REGISTER_H
#define REGISTER_H

#include <array>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

using namespace std;

void OutofrangeR(const string& context, int index);

class Register {
public:
    static const int registerSize = 16;
    array<float, registerSize> reg{0.0f};

    void set(int index, float value);
    float get(int index) const;
    void display() const;

private:
    string toHex(int value) const; // Declare toHex as a private member function
};

#endif // REGISTER_H