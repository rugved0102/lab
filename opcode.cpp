#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int TTL;  // Total Time Limit
int TI = 0;  // Time Interrupt
int PI = 0;  // Program Interrupt

vector<string> instructions;  // Vector to store instructions

// Function to parse the job and initialize TTL
void parseJob(const string& jobLine) {
    // Parse TTL from the job line (characters 9-12, zero-indexed)
    TTL = stoi(jobLine.substr(8, 4));
    cout << "TTL (Total Time Limit) = " << TTL << endl;
}

// Function to check opcodes and set PI if there are errors
void checkOpcodesAndSetPI() {
    for (const auto& instruction : instructions) {
        // Check if opcode is valid (GD, PD, LR, SR, etc.)
        string opcode = instruction.substr(0, 2);
        if (opcode != "GD" && opcode != "PD" && opcode != "LR" &&
            opcode != "SR" && opcode != "CR" && opcode != "BT" && opcode != "H") {
            PI = 1;  // Invalid opcode found
            break;
        }
    }
}

// Function to calculate TI based on TTL and number of instructions
void calculateTI() {
    if (instructions.size() > TTL) {
        TI = 2;  // Exceeded TTL
    } else {
        TI = 0;
    }
}

// Mock function for MOS to print error message based on TI and PI
void MOS() {
    if (PI == 1) {
        cout << "Program Interrupt: Invalid Opcode" << endl;
    }
    if (TI == 2) {
        cout << "Time Interrupt: Exceeded TTL" << endl;
    }
    if (TI == 0 && PI == 0) {
        cout << "Program executed successfully within TTL and with valid opcodes." << endl;
    }
}

// Main program to simulate the execution
int main() {
    string jobLine;
    
    // Get the job line input from the user
    cout << "Enter the job line: ";
    getline(cin, jobLine);

    // Parse the job to extract TTL
    parseJob(jobLine);

    // Get instructions input from the user
    string instructionLine;
    cout << "Enter instructions (separate each by space): ";
    getline(cin, instructionLine);

    // Split the instruction line into individual instructions and store them
    stringstream ss(instructionLine);
    string instruction;
    while (ss >> instruction) {
        instructions.push_back(instruction);
    }

    // Check opcodes for validity and set PI if needed
    checkOpcodesAndSetPI();

    // Calculate TI based on TTL and the number of instructions
    calculateTI();

    // Call MOS to print appropriate message based on TI and PI values
    MOS();

    return 0;
}


// input
// $AMJ040300040002
// GD30 PD30 LR30 SR40 PS40 H
// $DTA
// SHE SELLS   SEA SHELLS ON
// SHORE
// $END0403

