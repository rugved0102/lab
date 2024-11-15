#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

void calculateCSCAN(std::vector<int>& requests, int n, int initial_head, int disk_size, int direction) {
    int total_seek_time = 0;
    int current_head = initial_head;

    // Sort the requests in ascending order
    std::sort(requests.begin(), requests.end());

    // Find the starting index where the head should start servicing requests
    int start_index = 0;
    while (start_index < n && requests[start_index] < initial_head) {
        start_index++;
    }

    std::cout << "\nDisk Scheduling using C-SCAN Algorithm:\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "| Request No. |  Request   |  Seek Time      |\n";
    std::cout << "------------------------------------------------\n";

    // Move in the selected direction
    if (direction == 1) {  // Moving right towards higher values
        // Service requests to the right of the initial head position
        for (int i = start_index; i < n; i++) {
            int seek_time = std::abs(requests[i] - current_head);
            total_seek_time += seek_time;
            std::cout << "|      " << std::setw(2) << i - start_index + 1 << "      |    " << std::setw(3) << requests[i] << "     |     " << std::setw(3) << seek_time << "        |\n";
            current_head = requests[i];
        }

        // Move to the end of the disk and then jump to the start
        if (current_head < disk_size - 1) {
            int end_seek_time = std::abs(disk_size - 1 - current_head);
            total_seek_time += end_seek_time;
            std::cout << "|      -       |   " << std::setw(3) << disk_size - 1 << "     |     " << std::setw(3) << end_seek_time << "        |\n";
        }
        int reset_seek_time = disk_size - 1;  // Jump from end to start
        total_seek_time += reset_seek_time;
        std::cout << "|      -       |     0     |     " << std::setw(3) << reset_seek_time << "        |\n";
        current_head = 0;

        // Continue servicing the remaining requests from the start
        for (int i = 0; i < start_index; i++) {
            int seek_time = std::abs(requests[i] - current_head);
            total_seek_time += seek_time;
            std::cout << "|      " << std::setw(2) << i + n - start_index + 1 << "      |    " << std::setw(3) << requests[i] << "     |     " << std::setw(3) << seek_time << "        |\n";
            current_head = requests[i];
        }
    } else {  // Moving left towards lower values
        // Service requests to the left of the initial head position
        for (int i = start_index - 1; i >= 0; i--) {
            int seek_time = std::abs(requests[i] - current_head);
            total_seek_time += seek_time;
            std::cout << "|      " << std::setw(2) << start_index - i << "      |    " << std::setw(3) << requests[i] << "     |     " << std::setw(3) << seek_time << "        |\n";
            current_head = requests[i];
        }

        // Move to the start of the disk and then jump to the end
        if (current_head > 0) {
            int start_seek_time = std::abs(current_head - 0);
            total_seek_time += start_seek_time;
            std::cout << "|      -       |     0     |     " << std::setw(3) << start_seek_time << "        |\n";
        }
        int reset_seek_time = disk_size - 1;  // Jump from start to end
        total_seek_time += reset_seek_time;
        std::cout << "|      -       |   " << std::setw(3) << disk_size - 1 << "     |     " << std::setw(3) << reset_seek_time << "        |\n";
        current_head = disk_size - 1;

        // Continue servicing the remaining requests from the end
        for (int i = n - 1; i >= start_index; i--) {
            int seek_time = std::abs(requests[i] - current_head);
            total_seek_time += seek_time;
            std::cout << "|      " << std::setw(2) << n - i << "      |    " << std::setw(3) << requests[i] << "     |     " << std::setw(3) << seek_time << "        |\n";
            current_head = requests[i];
        }
    }

    std::cout << "------------------------------------------------\n";
    std::cout << "Total Seek Time: " << total_seek_time << "\n"; // Display total seek time
}

int main() {
    int n, initial_head, disk_size, direction;

    // Accept number of requests and initial head position
    std::cout << "Enter the number of disk requests: ";
    std::cin >> n;

    std::vector<int> requests(n);
    std::cout << "Enter the disk size: ";
    std::cin >> disk_size;

    std::cout << "Enter the initial head position: ";
    std::cin >> initial_head;

    std::cout << "Enter the direction (1 for right, 0 for left): ";
    std::cin >> direction;

    std::cout << "Enter the disk requests: \n";
    for (int i = 0; i < n; i++) {
        std::cout << "Request " << i + 1 << ": ";
        std::cin >> requests[i];
    }

    // Calculate and display the C-SCAN scheduling
    calculateCSCAN(requests, n, initial_head, disk_size, direction);

    return 0;
}


/*
6
200
50
1
176
79
34
60
92
11
*/