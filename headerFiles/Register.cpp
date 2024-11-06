#include "Register.h"

void Register::set(int index, float value) {
    if (index < 0 || index >= registerSize) {
        throw std::runtime_error("Register index out of range: " + std::to_string(index));
    }
    reg[index] = value;
}

float Register::get(int index) const {
    if (index < 0 || index >= registerSize) {
        throw std::runtime_error("Register index out of range: " + std::to_string(index));
    }
    return reg[index];
}

void Register::display() const {
    std::cout << "Registers: ";
    for (int i = 0; i < registerSize; ++i) {
        std::cout << "R" << i << ": " << std::fixed << std::setprecision(2) << reg[i] << " ";
    }
    std::cout << std::endl;
}
