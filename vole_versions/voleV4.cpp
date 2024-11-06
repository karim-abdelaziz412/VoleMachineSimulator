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

void Outofrange(const string& context, int index) {
    throw runtime_error(context + " out of range: " + to_string(index));
}

class Memory {
public:
    static const int memorySize = 256;
    array<unsigned char, memorySize> mem{0};

    void loadProgram(const vector<string>& program) {
        for (size_t i = 0; i < program.size() && i < memorySize; ++i) {
            mem[i] = static_cast<unsigned char>(stoi(program[i], nullptr, 16));
        }
    }

    unsigned char get(int address) const {
        if (address < 0 || address >= memorySize) {
            Outofrange("Memory address", address);
        }
        return mem[address];
    }

    void set(int address, unsigned char value) {
        if (address < 0 || address >= memorySize) {
            Outofrange("Memory address", address);
        }
        mem[address] = value;
    }

    void display() const {
        cout << "Memory: ";
        for (const auto& byte : mem) {
            cout << hex << setw(2) << setfill('0') << static_cast<int>(byte) << " ";
        }
        cout << dec << endl;
    }

    void displayScreen() const {
        for (int i = 0; i < memorySize; i++) {
            unsigned char value = mem[i];
            if (value >= 32 && value <= 126) {
                cout << static_cast<char>(value);
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }

    void setFloat(int address, float value) {
        if (address < 0 || address >= memorySize) {
            Outofrange("Memory address", address);
        }
        memcpy(&mem[address], &value, sizeof(float));
    }

    float getFloat(int address) const {
        if (address < 0 || address >= memorySize) {
            Outofrange("Memory address", address);
        }
        float value;
        memcpy(&value, &mem[address], sizeof(float));
        return value;
    }
};

class Register {
public:
    static const int registerSize = 16;
    array<float, registerSize> reg{0.0f};

    void set(int index, float value) {
        if (index < 0 || index >= registerSize) {
            Outofrange("Register index", index);
        }
        reg[index] = value;
    }

    float get(int index) const {
        if (index < 0 || index >= registerSize) {
            Outofrange("Register index", index);
        }
        return reg[index];
    }

    void display() const {
        cout << "Registers: ";
        for (int i = 0; i < registerSize; ++i) {
            cout << "R" << i << ": " << fixed << setprecision(2) << reg[i] << " ";
        }
        cout << endl;
    }
};

class ALU {
public:
    float addFloat(float a, float b) {
        return a + b;
    }
};

class CU {
private:
    int programCounter = 0;

public:
    int getProgramCounter() const {
        return programCounter;
    }

    void setProgramCounter(int pc) {
        programCounter = pc;
    }

    void incrementProgramCounter() {
        ++programCounter;
    }

    void jumpTo(int address) {
        if (address < 0 || address >= Memory::memorySize) {
            throw runtime_error("Jump address out of range: " + to_string(address));
        }
        programCounter = address;
    }
};

class CPU {
private:
    Register reg;
    ALU alu;
    CU cu;
    Memory* memory;
    unsigned char instructionRegister;

public:
    CPU(Memory* mem) : memory(mem), instructionRegister(0) {}

    void fetch() {
        instructionRegister = memory->get(cu.getProgramCounter());
        cu.incrementProgramCounter();
    }

    void execute() {
        if (cu.getProgramCounter() >= Memory::memorySize) {
            throw runtime_error("Program counter out of range: " + to_string(cu.getProgramCounter()));
        }

        unsigned char operationcode = (instructionRegister & 0xF0) >> 4;
        unsigned char operand1 = (instructionRegister & 0x0F);

        if (cu.getProgramCounter() >= Memory::memorySize) {
            throw runtime_error("Memory address out of range during operand fetch: " + to_string(cu.getProgramCounter()));
        }

        unsigned char operand2 = memory->get(cu.getProgramCounter());
        cu.incrementProgramCounter();

        switch (operationcode) {
            case 0x1:
                reg.set(operand1, memory->getFloat(operand2));
                break;
            case 0x2:
                reg.set(operand1, static_cast<float>(operand2));
                break;
            case 0x3:
                if (operand1 == 0) {
                    cout << "Writing to screen: " << reg.get(operand1) << endl;
                } else {
                    memory->setFloat(operand2, reg.get(operand1));
                }
                break;
            case 0x4:
                reg.set(operand2, reg.get(operand1));
                break;
            case 0x5:
                reg.set(operand1, alu.addFloat(reg.get(operand1), reg.get(operand2)));
                break;
            case 0x6:
                reg.set(operand1, alu.addFloat(reg.get(operand1), reg.get(operand2)));
                break;
            case 0xB:
                if (reg.get(operand1) == 0) {
                    cu.jumpTo(operand2);
                }
                break;
            case 0xC:
                cout << "Halting execution" << endl;
                throw runtime_error("Execution halted by HALT instruction");
            default:
                cout << "Invalid opcode: " << static_cast<int>(operationcode) << endl;
                break;
        }
    }

    void displayState() const {
        reg.display();
        memory->display();
        cout << "Program Counter: " << cu.getProgramCounter() << endl;
        cout << "Instruction Register: " << hex << static_cast<int>(instructionRegister) << dec << endl;
    }

    void displayScreen() const {
        memory->displayScreen();
    }
};

class Machine {
private:
    Memory memory;
    unique_ptr<CPU> cpu;

public:
    Machine() : cpu(make_unique<CPU>(&memory)) {}

    void loadProgramFromFile() {
        cout << "Enter file name to load program from: ";
        string filename;
        cin >> filename;
        ifstream file(filename);
        if (!file) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        vector<string> program;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string code;
            while (ss >> code) {
                program.push_back(code);
            }
        }

        memory.loadProgram(program);
    }

    void runWhole() {
        cout << "Running program as a whole" << endl;
        try {
            while (true) {
                cpu->fetch();
                cpu->execute();
                cpu->displayScreen();
            }
        } catch (const runtime_error& e) {
            cpu->displayState();
            cout << "Program halted: " << e.what() << endl;
        }
    }

    void step() {
        cout << "Running step-by-step" << endl;
        try {
            while (true) {
                cpu->fetch();
                cpu->execute();
                cpu->displayScreen();
                cpu->displayState();
                cout << "Press Enter to continue to next step" << endl;
                cin.get();
            }
        } catch (const runtime_error& e) {
            cpu->displayState();
            cout << "Program halted: " << e.what() << endl;
        }
    }

    void displayMenu() {
        cout << "\nMenu:\n";
        cout << "1. Load Program from File\n";
        cout << "2. Run Program as Whole\n";
        cout << "3. Step through Program\n";
        cout << "4. Display State\n";
        cout << "5. Exit\n";
    }

    void menu() {
        int choice;
        do {
            displayMenu();
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: {
                    loadProgramFromFile();
                    break;
                }
                case 2:
                    runWhole();
                    break;
                case 3:
                    step();
                    break;
                case 4:
                    cpu->displayState();
                    break;
                case 5:
                    cout << "Exiting the program" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again" << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    Machine machine;
    machine.menu();
    return 0;
}