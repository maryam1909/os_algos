#include <stdio.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
} Process;

void completion_Time(Process processes[], int n) {

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        processes[i].ct = current_time + processes[i].bt;
        current_time = processes[i].ct;
    }
}

void turnaround_Time(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].ct - processes[i].at;
    }
}

void waiting_Time(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].wt = processes[i].tat - processes[i].bt;
        if (processes[i].wt < 0) 
            processes[i].wt = 0;
    }
}

void solution(Process processes[], int n) {
    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at,
               processes[i].bt, processes[i].ct, processes[i].wt, processes[i].tat);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].at);
        printf("Enter burst time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].bt);
    }

    completion_Time(processes, n);
    turnaround_Time(processes, n);
    waiting_Time(processes, n);

    solution(processes, n);

    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].wt;
    }
    float avg_waiting_time = (float)total_waiting_time / n;
    printf("\nAvg WT: %.2f\n", avg_waiting_time);

    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].tat;
    }
    float avg_turnaround_time = (float)total_turnaround_time / n;
    printf("Avg TAT: %.2f\n", avg_turnaround_time);

    return 0;
}
