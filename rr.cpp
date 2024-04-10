#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Class to represent a process
class Process {
public:
    int pid;            // Process ID
    int burstTime;      // Burst time
    int remainingTime;  // Remaining burst time
    int arrivalTime;    // Arrival time
    int startTime;      // Start time
    int endTime;        // End time
    int turnaroundTime; // Turnaround time
    int waitTime;       // Wait time

    // Constructor
    Process(int pid, int burstTime, int arrivalTime) {
        this->pid = pid;
        this->burstTime = burstTime;
        this->remainingTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->startTime = -1;  // Initialize to -1, indicating not started
        this->endTime = -1;    // Initialize to -1, indicating not finished
        this->turnaroundTime = 0;
        this->waitTime = 0;
    }
};

// Function to simulate Round Robin scheduling
void roundRobin(vector<Process>& processes, int timeSlice) {
    int currentTime = 0;
    int completedProcesses = 0;
    int totalTurnaroundTime = 0;
    int totalWaitTime = 0;

    // Ready queue to hold processes
    queue<Process> readyQueue;

    // Loop until all processes are completed
    while (completedProcesses < processes.size()) {
        // Add processes to the ready queue as they become ready
        for (Process& process : processes) {
            if (process.remainingTime > 0 && process.arrivalTime <= currentTime) {
                readyQueue.push(process);
            }
        }

        // Dequeue and execute processes from the ready queue
        while (!readyQueue.empty()) {
            Process currentProcess = readyQueue.front();
            readyQueue.pop();

            // Set start time if not already set
            if (currentProcess.startTime == -1) {
                currentProcess.startTime = currentTime;
            }

            // Execute the process for the time slice or its remaining time, whichever is smaller
            int executeTime = min(currentProcess.remainingTime, timeSlice);
            currentTime += executeTime;
            currentProcess.remainingTime -= executeTime;

            // If the process is completed, set end time and calculate turnaround and wait times
            if (currentProcess.remainingTime <= 0) {
                currentProcess.endTime = currentTime;
                currentProcess.turnaroundTime = currentProcess.endTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnaroundTime - currentProcess.burstTime;
                totalTurnaroundTime += currentProcess.turnaroundTime;
                totalWaitTime += currentProcess.waitTime;
                completedProcesses++;
            } else {
                // Re-enqueue if remaining time > 0
                readyQueue.push(currentProcess);
            }
        }
    }

    // Print the scheduling metrics in a tabular format
    cout << "PID\tAT\tST\tET\tTAT\tWT" << endl;
    for (Process& process : processes) {
        cout << process.pid << "\t" << process.arrivalTime << "\t" << process.startTime << "\t" <<
            process.endTime << "\t" << process.turnaroundTime << "\t\t" << process.waitTime << endl;
    }

    // Calculate and print the average turnaround time and average wait time
    double avgTurnaroundTime = (double)totalTurnaroundTime / processes.size();
    double avgWaitTime = (double)totalWaitTime / processes.size();
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Wait Time: " << avgWaitTime << endl;
}

int main() {
    // Example processes
    vector<Process> processes = {
        Process(1, 24, 0),   // PID, Burst time, Arrival time
        Process(2, 3, 0),
        Process(3, 3, 0)
    };

    int timeSlice = 4;  // Time slice

    cout << "Round Robin Scheduling" << endl;
    roundRobin(processes, timeSlice);

    return 0;
}
