#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void calculateSCAN(vector<int>& requests, int n, int initial_head, int disk_size, int direction) {
    int total_seek_time = 0;
    int current_head = initial_head;

    // Sort the requests in ascending order
    sort(requests.begin(), requests.end());

    // Find the starting point where the head should start servicing requests
    int start_index = 0;
    while (start_index < n && requests[start_index] < initial_head) {
        start_index++;
    }

    cout << "\nDisk Scheduling using SCAN Algorithm:\n";
    cout << "------------------------------------------------\n";
    cout << "| Request No. |  Request   |  Seek Time      |\n";
    cout << "------------------------------------------------\n";

    // Move in the selected direction
    if (direction == 1) {  // Moving right towards higher values
        // Service requests to the right of the initial head position
        for (int i = start_index; i < n; i++) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            cout << "|      " << i - start_index + 1 << "      |    " << requests[i] << "     |     " << seek_time << "        |\n";
            current_head = requests[i];
        }

        // Move to the end of the disk
        int end_seek_time = abs(disk_size - 1 - current_head);
        total_seek_time += end_seek_time;
        cout << "|      -       |   " << disk_size - 1 << "     |     " << end_seek_time << "        |\n";
        current_head = disk_size - 1;

        // Reverse direction and service the remaining requests to the left
        for (int i = start_index - 1; i >= 0; i--) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            cout << "|      " << start_index - i + n - 1 << "      |    " << requests[i] << "     |     " << seek_time << "        |\n";
            current_head = requests[i];
        }
    } else {  // Moving left towards lower values
        // Service requests to the left of the initial head position
        for (int i = start_index - 1; i >= 0; i--) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            cout << "|      " << start_index - i << "      |    " << requests[i] << "     |     " << seek_time << "        |\n";
            current_head = requests[i];
        }

        // Move to the start of the disk
        int end_seek_time = abs(current_head - 0);
        total_seek_time += end_seek_time;
        cout << "|      -       |    0      |     " << end_seek_time << "        |\n";
        current_head = 0;

        // Reverse direction and service the remaining requests to the right
        for (int i = start_index; i < n; i++) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            cout << "|      " << i + 1 << "      |    " << requests[i] << "     |     " << seek_time << "        |\n";
            current_head = requests[i];
        }
    }

    cout << "------------------------------------------------\n";
    cout << "Total Seek Time: " << total_seek_time << endl; // Display total seek time
}

int main() {
    int n, initial_head, disk_size, direction;

    // Accept number of requests and initial head position
    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the disk size: ";
    cin >> disk_size;

    cout << "Enter the initial head position: ";
    cin >> initial_head;

    cout << "Enter the direction (1 for right, 0 for left): ";
    cin >> direction;

    cout << "Enter the disk requests: \n";
    for (int i = 0; i < n; i++) {
        cout << "Request " << i + 1 << ": ";
        cin >> requests[i];
    }

    // Calculate and display the SCAN scheduling
    calculateSCAN(requests, n, initial_head, disk_size, direction);

    return 0;
}


/*
8
200
50
1
176
79
34
60
92
11
14
114
*/