#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

class Memory {
public:
    static const int memorySize = 256;
    unsigned char mem[memorySize] = {0};

    void inputProgram(const vector<string>& program) {
        for (size_t i = 0; i < program.size() && i < memorySize; ++i) {
            mem[i] = static_cast<unsigned char>(stoi(program[i], nullptr, 16));
        }
    }

    unsigned char get(int address) const {
        return mem[address];
    }

    void set(int address, unsigned char value) {
        mem[address] = value;
    }

    void display() const {
        cout << "Memory: ";
        for (int i = 0; i < memorySize; ++i) {
            cout << hex << setw(2) << setfill('0') << static_cast<int>(mem[i]) << " ";
        }
        cout << dec << endl;
    }
};

class Register {
public:
    static const int registerSize = 16;
    unsigned char reg[registerSize] = {0};

    void set(int index, unsigned char value) {
        reg[index] = value;
    }

    unsigned char get(int index) const {
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

class ALU {
public:
    unsigned char add(unsigned char a, unsigned char b) {
        return a + b;
    }

    unsigned char sub(unsigned char a, unsigned char b) {
        return a - b;
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

public:
    CPU(Memory* mem) : memory(mem) {}

    void fetch() {
        unsigned char instruction = memory->get(cu.getProgramCounter());
        cu.incrementProgramCounter();
        execute(instruction);
    }

    void execute(unsigned char instruction) {
        unsigned char opcode = (instruction & 0xF0) >> 4;   // Extract opcode
        unsigned char operand = instruction & 0x0F;          // Extract operand

        switch (opcode) {
            case 0x1: // LOAD: Load value from memory to register
                reg.set(operand, memory->get(cu.getProgramCounter()));
                cu.incrementProgramCounter();
                break;
            case 0x2: // ADD: Add two registers and store in a register
                {
                    unsigned char regValue = memory->get(cu.getProgramCounter());
                    cu.incrementProgramCounter();
                    reg.set(operand, alu.add(reg.get(operand), reg.get(regValue)));
                }
                break;
            case 0x3: // SUB: Subtract two registers and store in a register
                {
                    unsigned char regValue = memory->get(cu.getProgramCounter());
                    cu.incrementProgramCounter();
                    reg.set(operand, alu.sub(reg.get(operand), reg.get(regValue)));
                }
                break;
            case 0xF: // HALT: Stop the CPU
                cout << "Halting execution." << endl;
                throw runtime_error("Execution halted by HALT instruction");
            default:
                cout << "Unknown instruction: " << static_cast<int>(opcode) << endl;
                break;
        }
    }

    void displayState() const {
        reg.display();
        memory->display();
    }
};

class Machine {
private:
    Memory memory;
    CPU cpu;

public:
    Machine() : cpu(&memory) {}

    void loadProgram(const vector<string>& program) {
        memory.inputProgram(program);
    }

    void run() {
        cout << "Starting program execution..." << endl;
        try {
            while (true) {
                cpu.fetch();
                cpu.displayState();
            }
        } catch (const runtime_error& e) {
            cout << "Program halted: " << e.what() << endl;
        }
    }
};


int main() {

    vector<string> program = {
        "10", "02", // LOAD 2 into R0
        "20", "01", // ADD R0 + R1 and store in R0
        "F0"       // HALT
    };

    Machine machine;
    machine.loadProgram(program);
    machine.run();

    return 0;
}
