#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <queue>
#include <condition_variable>
#include <mutex>

class Semaphore {
public:
    Semaphore(int count = 0) : count(count) {}

    void signal() {
        std::unique_lock<std::mutex> lock(mutex_);
        count++;
        cv_.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count == 0) {
            cv_.wait(lock);
        }
        count--;
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count;
};

// Shared variables
int read_count = 0;
Semaphore read_count_sem(1);  // Semaphore for protecting read_count
Semaphore write_sem(1);        // Semaphore for writer access

// Helper function to print table-like formatted output
void print_table(const std::string& action, const std::string& reader_writer, const std::string& state, const std::string& comment) {
    std::cout << "| " << std::setw(22) << std::left << action
              << "| " << std::setw(15) << std::left << reader_writer
              << "| " << std::setw(20) << std::left << state
              << "| " << std::setw(35) << std::left << comment << "|\n";
}

void reader(int reader_id) {
    while (true) {
        // Entry section
        read_count_sem.wait();  // Lock to update read_count
        read_count++;
        
        if (read_count == 1) {
            write_sem.wait();  // First reader locks the writer
        }
        
        read_count_sem.signal();  // Unlock read_count_sem

        // Critical section
        print_table("Reader is reading", "Reader " + std::to_string(reader_id), "Critical Section", "First reader entered");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 100)); // Simulate reading

        // Exit section
        read_count_sem.wait();  // Lock to update read_count
        read_count--;
        
        if (read_count == 0) {
            write_sem.signal();  // Last reader unlocks the writer
        }
        
        read_count_sem.signal();  // Unlock read_count_sem

        print_table("Reader finished reading", "Reader " + std::to_string(reader_id), "Finished", "Reader finished reading");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500)); // Simulate delay
    }
}

void writer(int writer_id) {
    while (true) {
        print_table("Writer is trying", "Writer " + std::to_string(writer_id), "Waiting", "Waiting for readers to finish");

        // Entry section
        write_sem.wait();  // Only one writer can access the critical section at a time

        // Critical section
        print_table("Writer is writing", "Writer " + std::to_string(writer_id), "Critical Section", "Writer entered");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 100)); // Simulate writing

        // Exit section
        write_sem.signal();
        print_table("Writer finished writing", "Writer " + std::to_string(writer_id), "Finished", "Writer finished writing");
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000 + 1000)); // Simulate delay
    }
}

int main() {
    srand(time(0));

    // Print table header
    std::cout << "| " << std::setw(22) << std::left << "Action"
              << "| " << std::setw(15) << std::left << "Reader/Writer"
              << "| " << std::setw(20) << std::left << "State"
              << "| " << std::setw(35) << std::left << "Comment" << "|\n";
    std::cout << std::string(100, '-') << "\n";

    // Creating reader and writer threads
    std::thread readers[3], writers[2];
    for (int i = 0; i < 3; i++) {
        readers[i] = std::thread(reader, i);
    }
    for (int i = 0; i < 2; i++) {
        writers[i] = std::thread(writer, i);
    }

    // Joining threads (for demonstration purposes, these will run indefinitely)
    for (int i = 0; i < 3; i++) {
        readers[i].join();
    }
    for (int i = 0; i < 2; i++) {
        writers[i].join();
    }

    return 0;
}



// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <vector>
// #include <atomic>
// #include <chrono>

// using namespace std;

// mutex wrt_mutex; // Mutex for controlling access to shared_data
// mutex read_count_mutex; // Mutex for read_count
// atomic<int> read_count(0); // Atomic read_count to prevent race conditions
// int shared_data = 0;

// void reader(int reader_id) {
//     // Entry section
//     {
//         lock_guard<mutex> lock(read_count_mutex);
//         read_count++;
//         if (read_count == 1) {
//             wrt_mutex.lock(); // First reader waits for writer to finish
//         }
//     }

//     // Reading section
//     cout << "Reader " << reader_id << ": read data = " << shared_data << endl;
//     this_thread::sleep_for(chrono::microseconds(100000)); // Simulate reading time

//     // Exit section
//     {
//         lock_guard<mutex> lock(read_count_mutex);
//         read_count--;
//         if (read_count == 0) {
//             wrt_mutex.unlock(); // Last reader releases the writer lock
//         }
//     }
// }

// void writer(int writer_id) {
//     wrt_mutex.lock(); // Writer locks shared data

//     // Writing section
//     shared_data += 1;
//     cout << "Writer " << writer_id << ": wrote data = " << shared_data << endl;
//     this_thread::sleep_for(chrono::microseconds(100000)); // Simulate writing time

//     wrt_mutex.unlock(); // Writer releases the lock
// }

// int main() {
//     const int num_readers = 5, num_writers = 2;
//     vector<thread> readers, writers;

//     // Create reader threads
//     for (int i = 0; i < num_readers; ++i) {
//         readers.push_back(thread(reader, i + 1));
//     }

//     // Create writer threads
//     for (int i = 0; i < num_writers; ++i) {
//         writers.push_back(thread(writer, i + 1));
//     }

//     // Join reader threads
//     for (auto &r : readers) {
//         r.join();
//     }

//     // Join writer threads
//     for (auto &w : writers) {
//         w.join();
//     }

//     return 0;
// }
