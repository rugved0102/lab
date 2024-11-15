#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <condition_variable>

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

// Shared buffer and semaphores
std::queue<int> buffer;
const unsigned int BUFFER_SIZE = 5;
Semaphore empty_slots(BUFFER_SIZE); // Controls how many empty slots are in the buffer
Semaphore full_slots(0);            // Controls how many items are available in the buffer

// Helper function to print table-like formatted output
void print_table(const std::string& action, const std::string& producer_consumer, int item) {
    std::cout << "| " << std::setw(22) << std::left << action
              << "| " << std::setw(15) << std::left << producer_consumer
              << "| " << std::setw(5) << std::left << item << "|\n";
}

void producer(int producer_id, int max_items) {
    int item = 0;
    for (int i = 0; i < max_items; ++i) {
        item++;
        empty_slots.wait();  // Wait for an empty slot in the buffer

        // Critical section (producing)
        buffer.push(item);
        print_table("Produced item", "Producer " + std::to_string(producer_id), item);

        full_slots.signal();  // Signal that a new item is available
    }
}

void consumer(int consumer_id, int max_items) {
    for (int i = 0; i < max_items; ++i) {
        full_slots.wait();  // Wait for an available item

        // Critical section (consuming)
        int item = buffer.front();
        buffer.pop();
        print_table("Consumed item", "Consumer " + std::to_string(consumer_id), item);

        empty_slots.signal();  // Signal that an empty slot is available
    }
}

int main() {
    srand(time(0));
    const int MAX_ITEMS = 6; // Limit the number of items produced and consumed

    // Print table header
    std::cout << "| " << std::setw(22) << std::left << "Action"
              << "| " << std::setw(15) << std::left << "Producer/Consumer"
              << "| " << std::setw(5) << std::left << "Item" << "|\n";
    std::cout << std::string(50, '-') << "\n";

    // Creating producer and consumer threads
    std::thread producers[2], consumers[2];
    for (int i = 0; i < 2; i++) {
        producers[i] = std::thread(producer, i, MAX_ITEMS);
        consumers[i] = std::thread(consumer, i, MAX_ITEMS);
    }

    // Joining threads (for demonstration purposes, these will run a fixed number of iterations)
    for (int i = 0; i < 2; i++) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}
