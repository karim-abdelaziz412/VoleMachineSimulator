# 🖥️ Vole Machine Simulator  
Welcome to the **Vole Machine Simulator** repository! This project is a C++ implementation of a virtual machine designed for educational purposes. It demonstrates fundamental computer architecture concepts by simulating a custom machine capable of executing programs with support for arithmetic, memory management, register operations, and floating-point processing.

## 📋 Project Objectives  
- Simulate a virtual machine to illustrate low-level programming concepts.  
- Provide hands-on learning with memory management, register operations, and instruction execution.  
- Demonstrate the implementation of arithmetic and floating-point operations.  
- Encourage modular code design and collaboration using GitHub.  

## ⚙️ Features  
- **Program Loading**: Executes programs from files.  
- **Memory Management**: Implements memory allocation and access for instructions.  
- **Register Operations**: Handles register-based computation.  
- **Floating-Point Processing**: Includes operations with floating-point numbers.  
- **Modular Design**: Organized header files and source code for extensibility.  

## 📂 Project Structure  
The repository is organized into the following files and directories:  
- **`headerFiles/`**: Contains the implementation and header files for various components:  
  - **`ALU.cpp` / `ALU.h`**: Implements the Arithmetic Logic Unit, responsible for performing arithmetic and logic operations.  
  - **`CPU.cpp` / `CPU.h`**: Handles the central processing unit operations, including instruction execution.  
  - **`CU.cpp` / `CU.h`**: Implements the Control Unit, managing the flow of instructions and data within the simulator.  
  - **`Machine.cpp` / `Machine.h`**: Defines the main virtual machine, integrating all components.  
  - **`Memory.cpp` / `Memory.h`**: Manages memory allocation and access for the simulator.  
  - **`Register.cpp` / `Register.h`**: Implements register operations, used for intermediate computations.  
- **`main.cpp`**: The entry point of the program, which initializes and runs the simulator.  

## 🛠️ Development Team  
This project was developed by the following team members:

### **Omar Tarek Mostafa**  
- **ID**: 20230258  
- **Email**: Tarekomar480@gmail.com  
- **Role**: Contributed to implementing arithmetic operations and memory management.  

### **Karim Mohamed Abdelaziz**  
- **ID**: 20231124  
- **Email**: zezokarim002@gmail.com  
- **Role**: Designed the instruction execution pipeline and register handling.  

### **Mahmoud Khairy Morsy**  
- **ID**: 20230371  
- **Email**: mahmoud9356w@gmail.com  
- **Role**: Developed floating-point operations and handled program loading mechanisms.  

### **Collaborative Effort**  
The entire team collaborated on:  
- Overall architecture and design of the simulator.  
- Debugging and testing.  
- Documentation and project reporting.  
