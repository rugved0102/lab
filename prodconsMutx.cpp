#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iomanip>

// Shared buffer and synchronization primitives
std::queue<int> buffer;
const unsigned int BUFFER_SIZE = 5;
std::mutex buffer_mutex;
std::condition_variable cv_producer, cv_consumer;  // Condition variables for signaling

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
        std::unique_lock<std::mutex> lock(buffer_mutex);

        // Wait if the buffer is full
        cv_producer.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        // Critical section (producing)
        buffer.push(item);
        print_table("Produced item", "Producer " + std::to_string(producer_id), item);

        lock.unlock(); // Unlock before notifying
        cv_consumer.notify_one(); // Notify consumer that an item is available
    }
}

void consumer(int consumer_id, int max_items) {
    for (int i = 0; i < max_items; ++i) {
        std::unique_lock<std::mutex> lock(buffer_mutex);

        // Wait if the buffer is empty
        cv_consumer.wait(lock, [] { return !buffer.empty(); });

        // Critical section (consuming)
        int item = buffer.front();
        buffer.pop();
        print_table("Consumed item", "Consumer " + std::to_string(consumer_id), item);

        lock.unlock(); // Unlock before notifying
        cv_producer.notify_one(); // Notify producer that a slot is available
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
