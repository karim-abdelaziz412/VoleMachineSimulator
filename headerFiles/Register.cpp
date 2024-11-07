#include "Register.h"

void OutofrangeR(const string& context, int index) {
    throw runtime_error(context + " out of range: " + to_string(index));
}

string Register::toHex(int value) const {
    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << value;
    return ss.str();
}

void Register::set(int index, float value) {
    if (index < 0 || index >= registerSize) {
        OutofrangeR("Register index", index);
    }
    reg[index] = value;
}

float Register::get(int index) const {
    if (index < 0 || index >= registerSize) {
        OutofrangeR("Register index", index);
    }
    return reg[index];
}

void Register::display() const {
    cout << "Registers: ";
    for (int i = 0; i < registerSize; ++i) {
        cout << "R" << i << ": " << toHex(static_cast<int>(reg[i])) << " "; // Use the private toHex function
    }
    cout << endl;
}