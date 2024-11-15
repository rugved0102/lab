#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iomanip>

using namespace std;

// Shared variables
int read_count = 0;
mutex buffer_mutex;
condition_variable cv_reader, cv_writer;  // Condition variables for signaling

void print_table(const string& action, const string& reader_writer, const string& state, const string& comment) {
    std::cout << "| " << setw(22) << std::left << action
              << "| " << setw(15) << std::left << reader_writer
              << "| " << setw(20) << std::left << state
              << "| " << setw(35) << std::left << comment << "|\n";
}

void reader(int reader_id) {
    while (true) {
        unique_lock<mutex> lock(buffer_mutex);
        
        // Entry section
        if (read_count == 0) {
            cv_writer.wait(lock);  // First reader waits for writers
        }
        
        read_count++;  // Increment reader count

        lock.unlock(); 
        print_table("Reader is reading", "Reader " + to_string(reader_id), "Critical Section", "First reader entered");
        this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 100)); // Simulate reading
        
        lock.lock();  // Lock before updating reader count
        read_count--;
        
        if (read_count == 0) {
            cv_writer.notify_one();  // Last reader notifies writer
        }
        lock.unlock();  // Unlock after updating

        print_table("Reader finished reading", "Reader " + to_string(reader_id), "Finished", "Reader finished reading");
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000 + 500)); // Simulate delay
    }
}

void writer(int writer_id) {
    while (true) {
        print_table("Writer is trying", "Writer " + to_string(writer_id), "Waiting", "Waiting for readers to finish");
        
        unique_lock<mutex> lock(buffer_mutex);
        
        // Entry section
        cv_writer.wait(lock, [] { return read_count == 0; });  // Wait until no readers are present
        
        // Critical section
        print_table("Writer is writing", "Writer " + to_string(writer_id), "Critical Section", "Writer entered");
        this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 100)); // Simulate writing

        lock.unlock();  // Unlock after writing
        print_table("Writer finished writing", "Writer " + std::to_string(writer_id), "Finished", "Writer finished writing");
        this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000 + 1000)); // Simulate delay
    }
}

int main() {
    srand(time(0));

    // Print table header
    std::cout << "| " << setw(22) << left << "Action"
              << "| " << setw(15) << left << "Reader/Writer"
              << "| " << setw(20) << left << "State"
              << "| " << setw(35) << left << "Comment" << "|\n";
    cout << std::string(100, '-') << "\n";

    // Creating reader and writer threads
    thread readers[3], writers[2];
    for (int i = 0; i < 3; i++) {
        readers[i] = thread(reader, i);
    }
    for (int i = 0; i < 2; i++) {
        writers[i] = thread(writer, i);
    }

    for (int i = 0; i < 3; i++) {
        readers[i].join();
    }
    for (int i = 0; i < 2; i++) {
        writers[i].join();
    }

    return 0;
}
