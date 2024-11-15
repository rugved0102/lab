#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& allocation, vector<vector<int>>& max, vector<int>& available, int num_processes, int num_resources) {
    vector<int> work = available;
    vector<bool> finish(num_processes, false);
    vector<int> safe_sequence(num_processes); 
    int count = 0;

    while (count < num_processes) {
        bool found_process = false;

        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;

                for (int j = 0; j < num_resources; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    safe_sequence[count++] = i;
                    finish[i] = true; 
                    found_process = true;
                }
            }
        }

        if (!found_process) {
            cout << "The system is not in a safe state." << endl;
            return false;
        }
    }

    cout << "The system is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < num_processes; i++) {
        cout << "P" << safe_sequence[i];
        if (i != num_processes - 1) cout << " -> ";
    }
    cout << endl;

    return true;
}

int main() {
    int num_processes, num_resources;

    cout << "Enter the number of processes: ";
    cin >> num_processes;

    cout << "Enter the number of resource types: ";
    cin >> num_resources;

    vector<vector<int>> allocation(num_processes, vector<int>(num_resources));
    vector<vector<int>> max(num_processes, vector<int>(num_resources));
    vector<int> available(num_resources);

    cout << "\n--- Allocation Matrix ---\n";
    cout << "Enter the allocation matrix (resource allocated to each process):\n";
    for (int i = 0; i < num_processes; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "\n--- Max Matrix ---\n";
    cout << "Enter the maximum resource demand for each process:\n";
    for (int i = 0; i < num_processes; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> max[i][j];
        }
    }

    cout << "\n--- Available Resources ---\n";
    cout << "Enter the number of available instances for each resource:\n";
    for (int i = 0; i < num_resources; i++) {
        cout << "Resource R" << i << ": ";
        cin >> available[i];
    }

    cout << "\nChecking if the system is in a safe state...\n";
    isSafe(allocation, max, available, num_processes, num_resources);

    return 0;
}


// input
/*
not safe
3
3
4 1 2
3 2 2
9 0 2
0 1 0
2 0 0
3 0 2
3 3 2
*/