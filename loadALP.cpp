#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Memory {
public:
    // Load instructions into main memory
    void loadInstructions(const vector<string>& instructions) {
        mainMemory = instructions;
    }

    // Display the contents of main memory
    void displayMemory() const {
        cout << "Contents of Main Memory:" << endl;
        for (int i = 0; i < mainMemory.size(); ++i) {
            cout << "Address " << i << ": " << mainMemory[i] << endl;
        }
    }

private:
    vector<string> mainMemory; // Simulated main memory
};

class Loader {
public:
    // Load ALP program from file into memory
    bool loadProgram(const string& filename, Memory& memory) {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        vector<string> instructions;
        string line;
        
        // Read each line from the file and store it in the instructions vector
        while (getline(inputFile, line)) {
            instructions.push_back(line);
        }

        // Load instructions into memory
        memory.loadInstructions(instructions);
        inputFile.close();
        return true;
    }
};

int main() {
    Memory memory;
    Loader loader;
    string filename = "program.alp"; // Name of the ALP file

    // Load the program
    if (loader.loadProgram(filename, memory)) {
        // Display the contents of memory after loading
        memory.displayMemory();
    } else {
        cerr << "Failed to load program." << endl;
    }

    return 0;
}


// program.alp
// MOV R1, 5
// ADD R1, R2
// SUB R3, R1
