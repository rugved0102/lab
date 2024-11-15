//FCFS
// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// struct Process {
//     int id, arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime, startTime;
// };

// // Sort processes by arrival time
// bool compareArrival(Process p1, Process p2) {
//     return p1.arrivalTime < p2.arrivalTime;
// }

// void displayResults(vector<Process> &processes) {
//     cout << "\n+-----+------------+------------+------------+------------+------------+\n";
//     cout << "| PID | ArrivalTime | BurstTime  | FinishTime | Turnaround | WaitingTime|\n";
//     cout << "+-----+------------+------------+------------+------------+------------+\n";
    
//     for (Process &p : processes) {
//         cout << "|  " << p.id << "  |      " << p.arrivalTime << "     |     " 
//              << p.burstTime << "     |     " << p.finishTime << "     |     "
//              << p.turnaroundTime << "     |     " << p.waitingTime << "     |\n";
//     }
    
//     cout << "+-----+------------+------------+------------+------------+------------+\n";
// }

// void displayGanttChart(vector<Process> &processes) {
//     cout << "\nGantt Chart (Process Flow):\n";
//     for (size_t i = 0; i < processes.size(); ++i) {
//         cout << "P" << processes[i].id;
//         if (i != processes.size() - 1) {
//             cout << " -> ";
//         }
//     }
//     cout << endl;
// }


// void FCFS(vector<Process> &processes) {
//     sort(processes.begin(), processes.end(), compareArrival);
//     int currentTime = 0;
    
//     for (auto &p : processes) {
//         p.startTime = max(currentTime, p.arrivalTime);            // Calculate start time for Gantt chart
//         p.finishTime = p.startTime + p.burstTime;                 // Calculate finish time
//         p.turnaroundTime = p.finishTime - p.arrivalTime;          // TAT = FT - AT
//         p.waitingTime = p.turnaroundTime - p.burstTime;           // WT = TAT - BT
//         currentTime = p.finishTime;                               // Update current time
//     }
    
//     displayResults(processes);       
//     displayGanttChart(processes);
// }

// int main() {
//     int numProcesses;
//     cout << "Enter the number of processes: ";
//     cin >> numProcesses;
    
//     vector<Process> processes(numProcesses);
    
//     for (int i = 0; i < numProcesses; i++) {
//         cout << "Enter Arrival Time and Burst Time for process " << i + 1 << ": ";
//         processes[i].id = i + 1;
//         cin >> processes[i].arrivalTime >> processes[i].burstTime;
//     }
    
//     FCFS(processes);
    
//     return 0;
// }

/*
3
1 3
0 5
3 1
*/

// --------------------------------------------------------------------------

//1)SJF(non-premp)

// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// struct Process {
//     int id, arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime;
//     bool completed = false;
// };

// // Function to sort by arrival time
// bool compareArrival(Process p1, Process p2) {
//     return p1.arrivalTime < p2.arrivalTime;
// }

// // Function to display the result table
// void displayResults(vector<Process> &processes) {
//     cout << "\n+-----+------------+------------+------------+------------+------------+\n";
//     cout << "| PID | ArrivalTime | BurstTime  | FinishTime | Turnaround | WaitingTime|\n";
//     cout << "+-----+------------+------------+------------+------------+------------+\n";
    
//     for (Process &p : processes) {
//         cout << "|  " << p.id << "  |      " << p.arrivalTime << "     |     " 
//              << p.burstTime << "     |     " << p.finishTime << "     |     "
//              << p.turnaroundTime << "     |     " << p.waitingTime << "     |\n";
//     }
    
//     cout << "+-----+------------+------------+------------+------------+------------+\n";
// }

// // Function to display the Gantt chart
// void displayGanttChart(vector<int> &ganttChart) {
//     cout << "\nGantt Chart (Process Flow):\n";
//     for (size_t i = 0; i < ganttChart.size(); ++i) {
//         cout << "P" << ganttChart[i];
//         if (i != ganttChart.size() - 1) {
//             cout << " -> "; 
//         }
//     }
//     cout << endl;
// }

// void SJF_NonPreemptive(vector<Process> &processes) {
//     int currentTime = 0;
//     int completedProcesses = 0;
//     int n = processes.size();
//     vector<int> ganttChart;

//     while (completedProcesses < n) {
//         int idx = -1;
//         int minBurst = 10000;
        
//         // Find the process with the shortest burst time that has arrived and is not completed
//         for (int i = 0; i < n; i++) {
//             if (processes[i].arrivalTime <= currentTime && !processes[i].completed && processes[i].burstTime < minBurst) {
//                 minBurst = processes[i].burstTime;
//                 idx = i;
//             }
//         }

//         if (idx != -1) {  // If a process is found
//             ganttChart.push_back(processes[idx].id);
//             currentTime += processes[idx].burstTime;
//             processes[idx].finishTime = currentTime;
//             processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;  // TAT = FT - AT
//             processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;    // WT = TAT - BT
//             processes[idx].completed = true; 
//             completedProcesses++;
//         } else {
//             currentTime++;  // No process available, so increment time
//         }
//     }

//     displayResults(processes);   
//     displayGanttChart(ganttChart);
// }

// int main() {
//     int numProcesses;
//     cout << "Enter the number of processes: ";
//     cin >> numProcesses;
    
//     vector<Process> processes(numProcesses);
    
//     for (int i = 0; i < numProcesses; i++) {
//         cout << "Enter Arrival Time and Burst Time for process " << i + 1 << ": ";
//         processes[i].id = i + 1;
//         cin >> processes[i].arrivalTime >> processes[i].burstTime;
//     }
    
//     SJF_NonPreemptive(processes);
    
//     return 0;
// }

/*
4
0 4
0 3
0 5
0 2
*/


//-------------------------------------------------------------------------------

// SJF(premp)

// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// // Structure to hold process information
// struct Process {
//     int id, arrivalTime, burstTime, remainingTime, finishTime, turnaroundTime, waitingTime;
//     bool completed = false;  // Flag to check if the process has completed
// };

// // Function to sort by arrival time
// bool compareArrival(Process p1, Process p2) {
//     return p1.arrivalTime < p2.arrivalTime;
// }

// // Function to display the result table
// void displayResults(vector<Process> &processes) {
//     cout << "\n+-----+------------+------------+------------+------------+------------+\n";
//     cout << "| PID | ArrivalTime | BurstTime  | FinishTime | Turnaround | WaitingTime|\n";
//     cout << "+-----+------------+------------+------------+------------+------------+\n";
    
//     for (Process &p : processes) {
//         cout << "|  " << p.id << "  |      " << p.arrivalTime << "     |     " 
//              << p.burstTime << "     |     " << p.finishTime << "     |     "
//              << p.turnaroundTime << "     |     " << p.waitingTime << "     |\n";
//     }
    
//     cout << "+-----+------------+------------+------------+------------+------------+\n";
// }

// // Function to display the Gantt chart
// void displayGanttChart(vector<int> &ganttChart) {
//     cout << "\nGantt Chart (Process Flow):\n";
//     for (size_t i = 0; i < ganttChart.size(); ++i) {
//         cout << "P" << ganttChart[i];
//         if (i != ganttChart.size() - 1) {
//             cout << " -> ";  // Add arrow between processes
//         }
//     }
//     cout << endl;
// }

// // Shortest Job First (Preemptive) Scheduling
// void SJF_Preemptive(vector<Process> &processes) {
//     int currentTime = 0, completedProcesses = 0, n = processes.size();
//     vector<int> ganttChart;  // To store process order in Gantt chart
//     int lastProcess = -1;    // To avoid recording the same process multiple times consecutively
    
//     while (completedProcesses < n) {
//         int idx = -1;
//         int minRemainingTime = 10000;  // A large value to find the minimum remaining time
        
//         // Find the process with the shortest remaining time that has arrived
//         for (int i = 0; i < n; i++) {
//             if (processes[i].arrivalTime <= currentTime && !processes[i].completed && processes[i].remainingTime < minRemainingTime) {
//                 minRemainingTime = processes[i].remainingTime;
//                 idx = i;
//             }
//         }

//         if (idx != -1) {  // If a process is found
//             if (lastProcess != idx) {
//                 ganttChart.push_back(processes[idx].id);  // Record process in Gantt chart if it's new
//                 lastProcess = idx;
//             }
//             processes[idx].remainingTime--; 
//             currentTime++; 

//             // If the process finishes
//             if (processes[idx].remainingTime == 0) {
//                 processes[idx].finishTime = currentTime;  // Set finish time
//                 processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;  // TAT = FT - AT
//                 processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;    // WT = TAT - BT
//                 processes[idx].completed = true;  // Mark process as completed
//                 completedProcesses++;
//             }
//         } else {
//             currentTime++; 
//         }
//     }

//     displayResults(processes);  
//     displayGanttChart(ganttChart);  
// }

// int main() {
//     int numProcesses;
//     cout << "Enter the number of processes: ";
//     cin >> numProcesses;
    
//     vector<Process> processes(numProcesses);
    
//     // Input arrival time and burst time for each process
//     for (int i = 0; i < numProcesses; i++) {
//         cout << "Enter Arrival Time and Burst Time for process " << i + 1 << ": ";
//         processes[i].id = i + 1;
//         cin >> processes[i].arrivalTime >> processes[i].burstTime;
//         processes[i].remainingTime = processes[i].burstTime;  // Initially, remaining time is equal to burst time
//     }
    
//     // Perform SJF Preemptive Scheduling
//     SJF_Preemptive(processes);
    
//     return 0;
// }

/*
6
3 6
2 10
5 2
6 1
4 4
2 8
*/

// -----------------------------------------------------------------------------------

// Priority(non-premp)

// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// struct Process {
//     int id, arrivalTime, burstTime, priority, finishTime, turnaroundTime, waitingTime;
//     bool completed = false;  // Flag to check if the process has completed
// };

// // Function to display the result table
// void displayResults(vector<Process> &processes) {
//     cout << "\n+-----+------------+------------+------------+------------+------------+----------+\n";
//     cout << "| PID | ArrivalTime | BurstTime  | Priority   | FinishTime | Turnaround | Waiting  |\n";
//     cout << "+-----+------------+------------+------------+------------+------------+----------+\n";
    
//     for (Process &p : processes) {
//         cout << "|  " << p.id << "  |      " << p.arrivalTime << "     |     " 
//              << p.burstTime << "     |     " << p.priority << "      |     " 
//              << p.finishTime << "     |     " << p.turnaroundTime << "     |    " 
//              << p.waitingTime << "    |\n";
//     }
    
//     cout << "+-----+------------+------------+------------+------------+------------+----------+\n";
// }

// // Function to display the Gantt chart
// void displayGanttChart(vector<int> &ganttChart) {
//     cout << "\nGantt Chart (Process Flow):\n";
//     for (size_t i = 0; i < ganttChart.size(); ++i) {
//         cout << "P" << ganttChart[i];
//         if (i != ganttChart.size() - 1) {
//             cout << " -> "; 
//         }
//     }
//     cout << endl;
// }

// // Non-Preemptive Priority Scheduling
// void Priority_NonPreemptive(vector<Process> &processes) {
//     int currentTime = 0;
//     int completedProcesses = 0;
//     int n = processes.size();
//     vector<int> ganttChart; 

//     while (completedProcesses < n) {
//         int idx = -1;
//         int highestPriority = 10000;  // Large value to find highest priority (lower value means higher priority)

//         // Find the process with the highest priority that has arrived and is not completed
//         for (int i = 0; i < n; i++) {
//             if (processes[i].arrivalTime <= currentTime && !processes[i].completed && processes[i].priority < highestPriority) {
//                 highestPriority = processes[i].priority;
//                 idx = i;
//             }
//         }

//         if (idx != -1) {  // If a process is found
//             ganttChart.push_back(processes[idx].id);  // Record process in Gantt chart
//             currentTime += processes[idx].burstTime;  // Update the current time
//             processes[idx].finishTime = currentTime;  // Calculate finish time
//             processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;  // TAT = FT - AT
//             processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;    // WT = TAT - BT
//             processes[idx].completed = true;  // Mark process as completed
//             completedProcesses++;
//         } else {
//             currentTime++;  // No process available, increment time
//         }
//     }

//     displayResults(processes);
//     displayGanttChart(ganttChart); 
// }

// int main() {
//     int numProcesses;
//     cout << "Enter the number of processes: ";
//     cin >> numProcesses;

//     vector<Process> processes(numProcesses);

//     // Input arrival time, burst time, and priority for each process
//     for (int i = 0; i < numProcesses; i++) {
//         cout << "Enter Arrival Time, Burst Time, and Priority for process " << i + 1 << ": ";
//         processes[i].id = i + 1;
//         cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
//     }

//     // Perform Non-Preemptive Priority Scheduling
//     Priority_NonPreemptive(processes);

//     return 0;
// }

/*
3
0 4 2
0 2 1
1 5 3
*/

// -------------------------------------------------------------------------------------------------------

//Priority(premp)
// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// // Structure to hold process information
// struct Process {
//     int id, arrivalTime, burstTime, remainingTime, priority, finishTime, turnaroundTime, waitingTime;
//     bool completed = false;  // Flag to check if the process has completed
// };

// // Function to display the result table
// void displayResults(const vector<Process>& processes) {
//     cout << "\n+-----+------------+------------+------------+------------+------------+----------+\n";
//     cout << "| PID | ArrivalTime | BurstTime  | Priority   | FinishTime | Turnaround | Waiting  |\n";
//     cout << "+-----+------------+------------+------------+------------+------------+----------+\n";
    
//     for (const Process &p : processes) {
//         cout << "|  " << p.id << "  |      " << p.arrivalTime << "     |     " 
//              << p.burstTime << "     |     " << p.priority << "      |     " 
//              << p.finishTime << "     |     " << p.turnaroundTime << "     |    " 
//              << p.waitingTime << "    |\n";
//     }
    
//     cout << "+-----+------------+------------+------------+------------+------------+----------+\n";
// }

// // Function to display the Gantt chart
// void displayGanttChart(const vector<int>& ganttChart) {
//     cout << "\nGantt Chart (Process Flow):\n";
//     for (size_t i = 0; i < ganttChart.size(); ++i) {
//         cout << "P" << ganttChart[i];
//         if (i != ganttChart.size() - 1) {
//             cout << " -> ";  // Add arrow between processes
//         }
//     }
//     cout << endl;
// }

// // Preemptive Priority Scheduling
// void Priority_Preemptive(vector<Process>& processes) {
//     int currentTime = 0;
//     int completedProcesses = 0;
//     int n = processes.size();
//     vector<int> ganttChart;  // To store process order in the Gantt chart
//     int lastProcess = -1;    // To avoid recording the same process multiple times consecutively

//     while (completedProcesses < n) {
//         int idx = -1;
//         int highestPriority = 10000;  // Large value to find the highest priority (lower value means higher priority)

//         // Find the process with the highest priority that has arrived
//         for (int i = 0; i < n; i++) {
//             if (processes[i].arrivalTime <= currentTime && !processes[i].completed && processes[i].remainingTime > 0 && processes[i].priority < highestPriority) {
//                 highestPriority = processes[i].priority;
//                 idx = i;
//             }
//         }

//         if (idx != -1) {  // If a process is found
//             if (lastProcess != idx) {
//                 ganttChart.push_back(processes[idx].id);  // Record process in Gantt chart if it's new
//                 lastProcess = idx;
//             }
//             processes[idx].remainingTime--;  // Decrease remaining time
//             currentTime++;  // Increment time

//             // If the process finishes
//             if (processes[idx].remainingTime == 0) {
//                 processes[idx].finishTime = currentTime;  // Set finish time
//                 processes[idx].turnaroundTime = processes[idx].finishTime - processes[idx].arrivalTime;  // TAT = FT - AT
//                 processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;    // WT = TAT - BT
//                 processes[idx].completed = true;  // Mark process as completed
//                 completedProcesses++;
//             }
//         } else {
//             currentTime++;  // No process available, increment time
//         }
//     }

//     displayResults(processes); 
//     displayGanttChart(ganttChart); 
// }

// int main() {
//     int numProcesses;
//     cout << "Enter the number of processes: ";
//     cin >> numProcesses;

//     vector<Process> processes(numProcesses);

//     // Input arrival time, burst time, and priority for each process
//     for (int i = 0; i < numProcesses; i++) {
//         cout << "Enter Arrival Time, Burst Time, and Priority for process " << i + 1 << ": ";
//         processes[i].id = i + 1;
//         cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
//         processes[i].remainingTime = processes[i].burstTime;  // Initially, remaining time is equal to burst time
//     }

//     // Perform Preemptive Priority Scheduling
//     Priority_Preemptive(processes);

//     return 0;
// }


/*
4
0 8 2
1 4 1
2 9 3
3 5 2
*/

// ---------------------------------------------------------------------------------------------

//Round Robin

// #include <iostream>
// #include <vector>
// #include <queue>
// using namespace std;

// // Structure to hold process information
// struct Process {
//     int id, arrivalTime, burstTime, remainingTime, finishTime, turnaroundTime, waitingTime;
//     bool completed = false;  // Flag to check if the process has completed
// };

// // Function to display the result table
// void displayResults(const vector<Process>& processes) {
//     cout << "\n+-----+------------+------------+------------+------------+------------+----------+\n";
//     cout << "| PID | ArrivalTime | BurstTime  | FinishTime | Turnaround | Waiting  |\n";
//     cout << "+-----+------------+------------+------------+------------+----------+\n";
    
//     for (const Process &p : processes) {
//         cout << "|  " << p.id << "  |      " << p.arrivalTime << "     |     " 
//              << p.burstTime << "     |     " << p.finishTime << "     |     " 
//              << p.turnaroundTime << "     |    " 
//              << p.waitingTime << "    |\n";
//     }
    
//     cout << "+-----+------------+------------+------------+------------+----------+\n";
// }

// // Function to display the Gantt chart
// void displayGanttChart(const vector<int>& ganttChart) {
//     cout << "\nGantt Chart (Process Flow):\n";
//     for (size_t i = 0; i < ganttChart.size(); ++i) {
//         cout << "P" << ganttChart[i];
//         if (i != ganttChart.size() - 1) {
//             cout << " -> ";  
//         }
//     }
//     cout << endl;
// }

// // Round Robin Scheduling
// void RoundRobin(vector<Process>& processes, int timeQuantum) {
//     int currentTime = 0;
//     int completedProcesses = 0;
//     int n = processes.size();
//     queue<int> processQueue;  
//     vector<int> ganttChart;  

//     // Initializing the remaining time for each process
//     for (int i = 0; i < n; i++) {
//         processes[i].remainingTime = processes[i].burstTime;
//     }

//     // Start with the first arriving process
//     for (int i = 0; i < n; i++) {
//         if (processes[i].arrivalTime <= currentTime) {
//             processQueue.push(i);
//         }
//     }

//     while (completedProcesses < n) {
//         // If there are no processes in the queue, increment time
//         if (processQueue.empty()) {
//             currentTime++;
//             // Check for newly arrived processes
//             for (int i = 0; i < n; i++) {
//                 if (processes[i].arrivalTime <= currentTime && !processes[i].completed) {
//                     processQueue.push(i);
//                 }
//             }
//             continue;
//         }

//         int currentProcessIdx = processQueue.front();
//         processQueue.pop();

//         // Record the process in Gantt chart
//         ganttChart.push_back(processes[currentProcessIdx].id);

//         // Execute the process for the time quantum or until it finishes
//         if (processes[currentProcessIdx].remainingTime > timeQuantum) {
//             currentTime += timeQuantum;
//             processes[currentProcessIdx].remainingTime -= timeQuantum;
//         } else {
//             currentTime += processes[currentProcessIdx].remainingTime; // Add remaining time to current time
//             processes[currentProcessIdx].remainingTime = 0; // Process finishes
//             processes[currentProcessIdx].finishTime = currentTime; // Set finish time
//             processes[currentProcessIdx].turnaroundTime = processes[currentProcessIdx].finishTime - processes[currentProcessIdx].arrivalTime; // TAT = FT - AT
//             processes[currentProcessIdx].waitingTime = processes[currentProcessIdx].turnaroundTime - processes[currentProcessIdx].burstTime; // WT = TAT - BT
//             processes[currentProcessIdx].completed = true; // Mark process as completed
//             completedProcesses++;
//         }

//         // Check for newly arrived processes after executing the current process
//         for (int i = 0; i < n; i++) {
//             if (processes[i].arrivalTime <= currentTime && !processes[i].completed && processes[i].remainingTime > 0) {
//                 processQueue.push(i);
//             }
//         }

//         // If the current process is not completed, push it back to the queue
//         if (processes[currentProcessIdx].remainingTime > 0) {
//             processQueue.push(currentProcessIdx);
//         }
//     }

//     displayResults(processes);  
//     displayGanttChart(ganttChart); 
// }

// int main() {
//     int numProcesses, timeQuantum;
//     cout << "Enter the number of processes: ";
//     cin >> numProcesses;

//     vector<Process> processes(numProcesses);

//     // Input arrival time and burst time for each process
//     for (int i = 0; i < numProcesses; i++) {
//         cout << "Enter Arrival Time and Burst Time for process " << i + 1 << ": ";
//         processes[i].id = i + 1;
//         cin >> processes[i].arrivalTime >> processes[i].burstTime;
//     }

//     cout << "Enter the time quantum: ";
//     cin >> timeQuantum;

//     // Perform Round Robin Scheduling
//     RoundRobin(processes, timeQuantum);

//     return 0;
// }


/*
3
0 5
1 3
2 8
*/