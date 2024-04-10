#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Process {
public:
    int pid;            
    int burstTime;      
    int remainingTime;  
    int arrivalTime;    
    int startTime;     
    int endTime;      
    int turnaroundTime; 
    int waitTime;      

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

//Round Robin scheduling
void roundRobin(vector<Process>& processes, int timeSlice) {
    int currentTime = 0;
    int completedProcesses = 0;
    int totalTurnaroundTime = 0;
    int totalWaitTime = 0;

    // Ready queue
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
            Process& currentProcess = readyQueue.front(); // Use reference instead of copy
            readyQueue.pop();

            // Set start time if not already set
            if (currentProcess.startTime == -1) {
                currentProcess.startTime = currentTime;
            }

            //whichever is smaller
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

    // Print in a tabular format
    cout << "PID\tAT\tST\tET\tTAT\tWT" << endl;
    for (int i = 0; i < processes.size(); i++) {
        cout << processes[i].pid << "\t" << processes[i].arrivalTime << "\t" << processes[i].startTime << "\t" <<
            processes[i].endTime << "\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitTime << endl;
    }

    // Calculate and print the average turnaround time and average wait time
    double avgTurnaroundTime = (double)totalTurnaroundTime / processes.size();
    double avgWaitTime = (double)totalWaitTime / processes.size();
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Wait Time: " << avgWaitTime << endl;
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    // Input arrival time and burst time for each process
    vector<Process> processes;
    for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime, burstTime;
        cout << "Process " << (i + 1) << " Arrival Time: ";
        cin >> arrivalTime;
        cout << "Process " << (i + 1) << " Burst Time: ";
        cin >> burstTime;
        processes.push_back(Process(i + 1, burstTime, arrivalTime));
    }

    int timeSlice;
    cout << "Enter the time slice: ";
    cin >> timeSlice;

    cout << "Round Robin Scheduling" << endl;
    roundRobin(processes, timeSlice);

    return 0;
}
