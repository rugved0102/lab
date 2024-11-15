#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

// Function to calculate the SSTF disk scheduling
void calculateSSTF(vector<int>& requests, int n, int initial_head, int disk_size) {
    int total_seek_time = 0;
    int current_head = initial_head;
    vector<bool> visited(n, false);

    cout << "\nDisk Scheduling using SSTF Algorithm:\n";
    cout << "------------------------------------------------------\n";
    cout << "| Request No. |  Request   |  Seek Time      |\n";
    cout << "------------------------------------------------------\n";

    // Process each request
    for (int count = 0; count < n; count++) {
        int min_seek_time = INT_MAX;
        int closest_request = -1;
        int seek_time = 0;

        // Find the closest unvisited request
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                seek_time = abs(requests[i] - current_head);
                if (seek_time < min_seek_time) {
                    min_seek_time = seek_time;
                    closest_request = i;
                }
            }
        }

        // Update the total seek time and mark the request as visited
        visited[closest_request] = true;
        total_seek_time += min_seek_time;
        current_head = requests[closest_request];

        cout << "|      " << closest_request + 1 << "      |    " << requests[closest_request] 
             << "     |     " << min_seek_time << "        |\n";
    }

    cout << "------------------------------------------------------\n";
    cout << "Total Seek Time: " << total_seek_time << endl; // Display total seek time
}

int main() {
    int n, initial_head, disk_size;

    // Accept number of requests and initial head position
    cout << "Enter the number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the disk size: ";
    cin >> disk_size;

    cout << "Enter the initial head position: ";
    cin >> initial_head;

    cout << "Enter the disk requests: \n";
    for (int i = 0; i < n; i++) {
        cout << "Request " << i + 1 << ": ";
        cin >> requests[i];
    }

    // Calculate and display the SSTF scheduling
    calculateSSTF(requests, n, initial_head, disk_size);

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