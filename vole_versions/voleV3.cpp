#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <limits>
#include <array>
#include <memory>

using namespace std;

void Outofrange(const string& context, int index) {
    throw runtime_error(context + " out of range: " + to_string(index));
}

//#########################################################################

class Memory {
public:
    static const int memorySize = 256;
    array<unsigned char, memorySize> mem{0};

    bool programLoaded = false;


    void loadProgram(const vector<string>& program) {
        for (size_t i = 0; i < program.size() && i < memorySize; ++i) {
            mem[i] = static_cast<unsigned char>(stoi(program[i], nullptr, 16));
        }
        programLoaded = true;

    }

    bool isProgramLoaded() const {
        return programLoaded;
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
        cout << "Memory:" << endl;
        for (int i = 0; i < memorySize; i++) {
            if (i % 16 == 0) {
                cout << endl;
            }
            cout << hex << setw(2) << setfill('0') << static_cast<int>(mem[i]) << " ";
        }
        cout << dec << endl;
    }
};


class Register {
public:
    static const int registerSize = 16;
    array<unsigned char, registerSize> reg{0};

    void set(int index, unsigned char value) {
        if (index < 0 || index >= registerSize) {
            Outofrange("Register index", index);
        }
        reg[index] = value;
    }

    unsigned char get(int index) const {
        if (index < 0 || index >= registerSize) {
            Outofrange("Register index", index);
        }
        return reg[index];
    }

    void display() const {
        cout << "Registers: ";
        for (int i = 0; i < registerSize; ++i) {
            cout << "R" << i << ": " << hex << setw(2) << setfill('0') << static_cast<int>(reg[i]) << " ";
        }
        cout << dec << endl;
    }
};

//#########################################################

class ALU {
public:
    unsigned char add(unsigned char a, unsigned char b) {
        return a + b;
    }

    unsigned int addfloat(unsigned int a, unsigned int b) {
        // Interpret `unsigned int` values as IEEE 754 floating-point numbers
        float val1 = *reinterpret_cast<float*>(&a);
        float val2 = *reinterpret_cast<float*>(&b);

        // Perform floating-point addition
        float result = val1 + val2;

        // Reinterpret the result back to `unsigned int` to store as a bit pattern
        return *reinterpret_cast<unsigned int*>(&result);
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

        
        if (!memory->isProgramLoaded()) {
            cout << "No program loaded. Halting execution." << endl;
            throw runtime_error("Execution halted due to lack of program.");
        }

//#########################################################################

        if (cu.getProgramCounter() >= Memory::memorySize) {
            throw runtime_error("Memory address out of range: " + to_string(cu.getProgramCounter()));
        }

        // instructionRegister = memory->get(cu.getProgramCounter());
        // cu.incrementProgramCounter();

        unsigned char operationcode = (instructionRegister >> 12) & 0xF; //shift right 12 bits to isolate the first 4 bits for op-code
        unsigned char operand1 = (instructionRegister >> 8) & 0xF;//shift right 8 bits to isolate the second 4 bits for operand 1

        // if (cu.getProgramCounter() >= Memory::memorySize) {
        //     throw runtime_error("Memory address out of range during operand fetch: " + to_string(cu.getProgramCounter()));
        // }

        unsigned char operand2 = instructionRegister & 0xFF;//just make and operation with 0xFF which is 11111111 to isolate the last 8 bits which is operand2
        cu.incrementProgramCounter();

        switch (operationcode) {
            case 0x1:
                reg.set(operand1, memory->get(operand2));
                break;
            case 0x2:
                reg.set(operand1, operand2);
                break;
            case 0x3:
                if (operand1 == 0) {
                    cout << "Writing to screen: " << static_cast<int>(reg.get(operand1)) << endl;
                } else {
                    memory->set(operand2, reg.get(operand1));
                }
                break;
            case 0x4:
                reg.set(operand2, reg.get(operand1));
                break;
            case 0x5:
                reg.set(operand1, alu.add(reg.get(operand1), reg.get(operand2)));
                break;
            case 0x6:
                reg.set(operand1, alu.addfloat(reg.get(operand1), reg.get(operand2)));
                break;
            case 0xB:
                if (reg.get(operand1) == reg.get(0)) {
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
};

class Machine {
private:
    Memory memory;
    unique_ptr<CPU> cpu;

public:
    Machine() : cpu(make_unique<CPU>(&memory)) {}

    void loadProgramFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile) {
            throw runtime_error("Could not open file: " + filename);
        }

//#########################################################################

    if (infile.peek() == ifstream::traits_type::eof()) {
        cout << "Error: File is empty. No program to load.\n";
        return;
    }


        vector<string> program;
        string line;
        while (infile >> line) {
            program.push_back(line);
        }
        memory.loadProgram(program);

//###################################################

        cout << "Loaded program instructions: ";
        for (const auto& inst : program) {
            cout << inst << " ";
        }
        cout << endl;

    }

    void run() {
        cout << "Starting the program" << endl;
        try {
            while (true) {
                cpu->fetch();
                cpu->execute();
                cpu->displayState();
            }
        } catch (const runtime_error& e) {
            cout << "Program halted: " << e.what() << endl;
        }
    }

    void step() {
        try {
            cpu->fetch();
            cpu->execute();
            cpu->displayState();
        } catch (const runtime_error& e) {
            cout << "Program halted: " << e.what() << endl;
        }
    }

    void displayMenu() {
        cout << "\nMenu:\n";
        cout << "1. Load Program from File\n";
        cout << "2. Run Program\n";
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

            switch (choice) {
                case 1: {
                    string filename;
                    cout << "Enter filename (with extenstions): ";
                    cin >> filename;
                    try {
                        loadProgramFromFile(filename);
                    } catch (const runtime_error& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                case 2:
                    run();
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
                    cout << "Invalid. Please try again" << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    Machine machine;
    machine.menu();
    return 0;
}