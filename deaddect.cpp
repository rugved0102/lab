#include <iostream>
#include <vector>
using namespace std;

// Function to check if the system is in a safe state (i.e., no deadlock)
bool is_safe(const vector<int>& available, const vector<vector<int>>& allocation, 
             const vector<vector<int>>& request, vector<bool>& finish, int n, int r) {
    vector<int> work = available;  // Initialize work as available resources
    finish.assign(n, false);  // Initially no processes are finished

    while (true) {
        bool progress_made = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_execute = true;

                // Check if all requested resources are less than or equal to available resources
                for (int j = 0; j < r; j++) {
                    if (request[i][j] > work[j]) {
                        can_execute = false;
                        break;
                    }
                }

                // If the process can be executed
                if (can_execute) {
                    for (int j = 0; j < r; j++) {
                        work[j] += allocation[i][j];  // Simulate resource release by adding allocated resources back to work
                    }
                    finish[i] = true;  // Mark process as finished
                    progress_made = true;
                    break;
                }
            }
        }

        if (!progress_made) {
            break;  // No progress was made, so break out of the loop
        }
    }

    // If any process is not finished, return false (deadlock detected)
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            return false;
        }
    }

    return true;  // All processes finished, no deadlock
}

int main() {
    int n, r;
    
    // Input the number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> r;

    vector<vector<int>> allocation(n, vector<int>(r)), request(n, vector<int>(r));
    vector<int> available(r);

    // Input the allocation matrix
    cout << "\nEnter the Allocation Matrix (" << n << " x " << r << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input the request matrix
    cout << "\nEnter the Request Matrix (" << n << " x " << r << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            cin >> request[i][j];
        }
    }

    // Input available resources
    cout << "\nEnter the Available Resources (" << r << " values):\n";
    for (int i = 0; i < r; i++) {
        cin >> available[i];
    }

    // Call the deadlock detection function
    vector<bool> finish(n);
    if (is_safe(available, allocation, request, finish, n, r)) {
        cout << "\nNo deadlock detected.\n";
    } else {
        cout << "\nDeadlock detected.\n";
    }

    return 0;
}


/*
5
3
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
0 0 0
1 0 2
1 1 0
0 2 2
1 1 1
3 3 2
*/