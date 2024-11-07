#include "Memory.h"

void Outofrange(const string& context, int index) {
    throw runtime_error(context + " out of range: " + to_string(index));
}

void Memory::loadProgram(const vector<string>& program) {
    size_t memIndex = 0;

    for (size_t i = 0; i < program.size(); ++i) {
        if (memIndex >= memorySize - 1) {
            throw runtime_error("no more capacity");
        }

        try {
            int instruction = stoi(program[i], nullptr, 16);
            mem[memIndex++] = static_cast<unsigned char>((instruction >> 8) & 0xFF);
            mem[memIndex++] = static_cast<unsigned char>(instruction & 0xFF);

        } catch (const invalid_argument&) {
            throw runtime_error("invalid instruction" + to_string(i) + ": Not a valid hexadecimal number.");
        } catch (const out_of_range&) {
            throw runtime_error("Program instruction at line " + to_string(i) + " exceeds memory range");
        }
    }
    programLoaded = true;
}

bool Memory::isProgramLoaded() const {
    return programLoaded;
}

unsigned char Memory::get(int address) const {
    if (address < 0 || address >= memorySize) {
        Outofrange("Memory address", address);
    }
    return mem[address];
}

void Memory::display() const {
    cout << "Memory (in hex, 16x16 matrix):" << endl;
    for (int i = 0; i < memorySize; i += 16) {
        cout << "0x" << uppercase << hex << setw(2) << setfill('0') << i << ": ";
        for (int j = 0; j < 16; ++j) {
            cout << setw(2) << setfill('0') << static_cast<int>(mem[i + j]) << " ";
        }
        cout << dec << endl;
    }
}

void Memory::displayScreen() const {
    cout << "Memory (16x16 matrix):" << endl;
    for (int i = 0; i < memorySize; i += 16) {
        cout << "0x" << uppercase << hex << setw(2) << setfill('0') << i << ": ";
        for (int j = 0; j < 16; ++j) {
            cout << setw(2) << setfill('0') << static_cast<int>(mem[i + j]) << " ";
        }
        cout << dec << endl;
    }
}

void Memory::setFloat(int address, float value) {
    if (address < 0 || address >= memorySize) {
        Outofrange("Memory address", address);
    }
    memcpy(&mem[address], &value, sizeof(float));
}

float Memory::getFloat(int address) const {
    if (address < 0 || address >= memorySize) {
        Outofrange("Memory address", address);
    }
    float value;
    memcpy(&value, &mem[address], sizeof(float));
    return value;
}