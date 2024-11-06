#include "Memory.h"
#include <iomanip>

void Memory::loadProgram(const std::vector<std::string>& program) {
    for (size_t i = 0; i < program.size() && i < memorySize; ++i) {
        mem[i] = static_cast<unsigned char>(stoi(program[i], nullptr, 16));
    }
}

unsigned char Memory::get(int address) const {
    if (address < 0 || address >= memorySize) {
        throw std::runtime_error("Memory address out of range: " + std::to_string(address));
    }
    return mem[address];
}

void Memory::set(int address, unsigned char value) {
    if (address < 0 || address >= memorySize) {
        throw std::runtime_error("Memory address out of range: " + std::to_string(address));
    }
    mem[address] = value;
}

void Memory::display() const {
    std::cout << "Memory: ";
    for (const auto& byte : mem) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
}

void Memory::displayScreen() const {
    for (int i = 0; i < memorySize; i++) {
        unsigned char value = mem[i];
        if (value >= 32 && value <= 126) {
            std::cout << static_cast<char>(value);
        } else {
            std::cout << '.';
        }
    }
    std::cout << std::endl;
}

void Memory::setFloat(int address, float value) {
    if (address < 0 || address >= memorySize) {
        throw std::runtime_error("Memory address out of range: " + std::to_string(address));
    }
    std::memcpy(&mem[address], &value, sizeof(float));
}

float Memory::getFloat(int address) const {
    if (address < 0 || address >= memorySize) {
        throw std::runtime_error("Memory address out of range: " + std::to_string(address));
    }
    float value;
    std::memcpy(&value, &mem[address], sizeof(float));
    return value;
}
