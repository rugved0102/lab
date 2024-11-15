#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

void createZombieProcess() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process
        cout << "Parent process: Zombie process created. PID = " << pid << endl;
        // No sleep here, but we need to wait for a while to allow the child to ex  
        sleep(2);  // Short sleep to simulate time for the zombie process
    } else {  // Child process
        cout << "Child process exiting to become zombie." << endl;
        exit(0);  // Child exits, becoming a zombie
    }
}

void createOrphanProcess() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process
        cout << "Parent process exiting to create orphan process." << endl;
        exit(0);  // Parent exits, child becomes orphan
    } else {  // Child process
        sleep(1);  // Allow the orphan to exist for a while
        cout << "Child process (orphan) continuing after parent termination. PID = " << getpid() << endl;
    }
}

void sumEvenOdd(int arr[], int size) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process
        int evenSum = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 == 0) {
                evenSum += arr[i];
            }
        }
        cout << "Parent process: Sum of even numbers = " << evenSum << endl;
        wait(NULL);  // Wait for the child process to finish
    } else {  // Child process
        int oddSum = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 != 0) {
                oddSum += arr[i];
            }
        }
        cout << "Child process: Sum of odd numbers = " << oddSum << endl;
        exit(0);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Array of integers
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Calculating sum of even and odd numbers:" << endl;
    sumEvenOdd(arr, size);

    cout << "\nCreating a zombie process:" << endl;
    createZombieProcess();

    cout << "\nCreating an orphan process:" << endl;
    createOrphanProcess();

    return 0;
}
