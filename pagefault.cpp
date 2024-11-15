#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool isPageInMemory(vector<int>& memory, int page) {
    return find(memory.begin(), memory.end(), page) != memory.end();
}

int fifoPageFaults(vector<int>& pages, int frames) {
    vector<int> memory;
    int pageFaults = 0;

    for (int page : pages) {
        if (!isPageInMemory(memory, page)) {
            if (memory.size() == frames) {
                memory.erase(memory.begin()); // Remove the first inserted page
            }
            memory.push_back(page); // Insert new page
            pageFaults++;
        }
    }
    return pageFaults;
}

int lruPageFaults(vector<int>& pages, int frames) {
    vector<int> memory;
    unordered_map<int, int> recentUse; // To track when pages were last used
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (!isPageInMemory(memory, page)) {
            if (memory.size() == frames) {
                // Find least recently used page
                int lruPage = *min_element(memory.begin(), memory.end(), 
                    [&](int a, int b) { return recentUse[a] < recentUse[b]; });
                memory.erase(find(memory.begin(), memory.end(), lruPage));
            }
            memory.push_back(page); // Insert new page
            pageFaults++;
        }
        recentUse[page] = i; // Update recent use for the current page
    }
    return pageFaults;
}

int optimalPageFaults(vector<int>& pages, int frames) {
    vector<int> memory;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (!isPageInMemory(memory, page)) {
            if (memory.size() == frames) {
                int furthestPageIndex = -1;
                int replaceIndex = -1;

                // Find the page in memory that won't be used for the longest time
                for (int j = 0; j < memory.size(); j++) {
                    int nextUse = find(pages.begin() + i + 1, pages.end(), memory[j]) - pages.begin();
                    if (nextUse > furthestPageIndex) {
                        furthestPageIndex = nextUse;
                        replaceIndex = j;
                    }
                    if (nextUse == pages.size()) break; // Page won't be used again
                }
                memory[replaceIndex] = page;
            } else {
                memory.push_back(page); // Insert new page
            }
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    int frames;
    vector<int> pages;
    int n, page;

    // Input number of frames
    cout << "Enter number of frames: ";
    cin >> frames;

    // Input number of pages and the reference string
    cout << "Enter number of pages: ";
    cin >> n;
    cout << "Enter the reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> page;
        pages.push_back(page);
    }

    // Calculate page faults for FIFO, LRU, and Optimal
    cout << "FIFO Page Faults: " << fifoPageFaults(pages, frames) << endl;
    cout << "LRU Page Faults: " << lruPageFaults(pages, frames) << endl;
    cout << "Optimal Page Faults: " << optimalPageFaults(pages, frames) << endl;

    return 0;
}


// input
/*
3
9
7 0 1 2 0 3 0 4 2
*/