#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to calculate the FCFS disk scheduling
void calculateFCFS(vector<int>& requests, int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;

    cout << "\nDisk Scheduling using FCFS Algorithm:\n";
    cout << "------------------------------------------------------\n";
    cout << "| Request No. |  Request   |  Seek Time      |\n";
    cout << "------------------------------------------------------\n";

    // Process each request in the order they are received
    for (int i = 0; i < n; i++) {
        int seek_time = abs(requests[i] - current_head);
        total_seek_time += seek_time;
        current_head = requests[i];

        cout << "|      " << i + 1 << "      |    " << requests[i] 
             << "     |     " << seek_time << "        |\n";
    }

    cout << "------------------------------------------------------\n";
    cout << "Total Seek Time: " << total_seek_time << endl; // Display total seek time
}

int main() {
    int n, initial_head;

    // Accept number of requests and initial head position
    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the initial head position: ";
    cin >> initial_head;

    cout << "Enter the disk requests: \n";
    for (int i = 0; i < n; i++) {
        cout << "Request " << i + 1 << ": ";
        cin >> requests[i];
    }

    // Calculate and display the FCFS scheduling
    calculateFCFS(requests, n, initial_head);

    return 0;
}


/*
5
50
70 
20
90 
40 
60
*/