#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

#define N 5

mutex forks[N];  // Mutexes for each fork

void philosopher(int id) {
    for (int i = 0; i < 3; i++) {
        cout << "Philosopher " << id << " is thinking.\n";
        this_thread::sleep_for(chrono::microseconds(100000));

        // Try to pick up forks (mutex locking)
        unique_lock<mutex> left_fork_lock(forks[id]);  // Lock left fork
        unique_lock<mutex> right_fork_lock(forks[(id + 1) % N]);  // Lock right fork

        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::microseconds(100000));

        // Finished eating, release forks (unlock)
        cout << "Philosopher " << id << " finished eating.\n";
    }
}

int main() {
    vector<thread> philosophers;
    
    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        philosophers.push_back(thread(philosopher, i));
    }

    // Wait for all threads to finish
    for (auto& t : philosophers) {
        t.join();
    }

    return 0;
}
