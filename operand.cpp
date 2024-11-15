#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>  //isdigit()

using namespace std;

// Function to check if the operand is valid
bool isValidOperand(const string& operand) {
    // Operand must be 2 digits and between 00 and 99
    if (operand.length() == 2 && isdigit(operand[0]) && isdigit(operand[1])) {
        int num = stoi(operand);  // Convert operand to integer
        return (num >= 0 && num <= 99);
    }
    return false;
}

// Function to check for operand errors in the instructions
void checkOperandErrors(const string& instructionLine) {
    stringstream ss(instructionLine);
    string instruction;
    int programInterrupt = 0;  // Default: No error

    while (ss >> instruction) {
        if (instruction == "H") {
            // Halt instruction should not have any operand
            if (ss >> instruction) {
                // If there's an operand after halt, it's an error
                programInterrupt = 2;
                cout << "Operand error: Operand found for halt instruction 'H'!" << endl;
                break;
            }
        } else {
            // Check if the instruction has a valid operand (should be 2 digits between 00 and 99)
            string operand = instruction.substr(2);  // Get the operand part (after the first 2 characters)
            if (!isValidOperand(operand)) {
                programInterrupt = 2;
                cout << "Operand error: Invalid operand in instruction '" << instruction << "'!" << endl;
                break;
            }
        }
    }

    // If there's no error, print that the job has no operand errors
    if (programInterrupt == 0) {
        cout << "No operand errors detected." << endl;
    }
}

int main() {
    string job;
    cout << "Enter the job instruction line: "<<endl;
    getline(cin, job);  // Read the job input from the user

    checkOperandErrors(job);  // Check for operand errors

    return 0;
}


// input
// GD30 PDxy LR30 SR40 PS40 H