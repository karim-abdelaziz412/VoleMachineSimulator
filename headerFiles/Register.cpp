#include "Register.h"

void Register::set(int index, float value) {
    if (index < 0 || index >= registerSize) {
        Outofrange("Register index", index);
    }
    reg[index] = value;
}

float Register::get(int index) const {
    if (index < 0 || index >= registerSize) {
        Outofrange("Register index", index);
    }
    return reg[index];
}

void Register::display() const {
    cout << "Registers: ";
    for (int i = 0; i < registerSize; ++i) {
        cout << "R" << i << ": " << toHex(static_cast<int>(reg[i])) << " ";
    }
    cout << endl;
}