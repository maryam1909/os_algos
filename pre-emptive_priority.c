#include <stdio.h>
#include <stdlib.h>



typedef struct {
    int id;
    int priority;
    int arrival_time;
    int burst_time;
    int start_time;
    int end_time;
    int turnaround_time;
    int wait_time;
    int remaning_time;

} Process;

// Function to swap two processes
void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}


// Function to perform priority scheduling preemptive
void prior_schedule(Process processes[],int n){
    int curr_time = 0;
    int executed_process = 0;
    int curr_priority = 100;
    Process *curr_process;
    // to sort the process according to their arrival time
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
        if(processes[j].arrival_time>processes[j+1].arrival_time){
            swap(&processes[j],&processes[j+1]);
        };}
    }

    while(executed_process < n){
        for(int i=0;i<n;i++){
            if(processes[i].arrival_time<=curr_time && processes[i].priority<curr_priority && processes[i].burst_time>0){
                curr_priority=processes[i].priority;
                curr_process=&processes[i];
            }
        }
        if(curr_process->start_time<0){
            curr_process->start_time=curr_time;
        }
        curr_process->burst_time--;
        if(curr_process->burst_time==0){
            curr_process->end_time=curr_time+1;
            executed_process++;
            curr_priority=100;
        }
        curr_time++;
//        printf("id:%d , start time : %d,  priority :%d,burst time:%d | curr time:%d\n",curr_process->id,curr_process->start_time,curr_process->priority,curr_process->burst_time,curr_time);
    };

    for(int i=0;i<n;i++){
        processes[i].turnaround_time = processes[i].end_time - processes[i].arrival_time;
        processes[i].wait_time = processes[i].turnaround_time - processes[i].remaning_time;
    }
}

int main() {

    int no;
    printf("enter number of processes");
    scanf("%d",&no);
    Process processes[no];
    for(int j=0;j<no;j++){
        printf("enter id:");
        scanf("%d",&processes[j].id);
        printf("enter arrival time:");
        scanf("%d",&processes[j].arrival_time);
        printf("enter priority:");
        scanf("%d",&processes[j].priority);
        printf("enter burst time:");
        scanf("%d",&processes[j].burst_time);
        processes[j].start_time=-1;
        processes[j].end_time=0;
        processes[j].remaning_time=processes[j].burst_time;
        processes[j].wait_time=0;
        processes[j].turnaround_time=0;
    }
    int n = sizeof(processes) / sizeof(processes[0]);

    prior_schedule(processes,n);
    float total_tat =0;
    float total_wt=0;
    printf("id\tat\tst\tet\tpr\tbt\twt\ttat\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",processes[i].id,processes[i].arrival_time,processes[i].start_time,processes[i].end_time,processes[i].priority,processes[i].remaning_time,processes[i].wait_time,processes[i].turnaround_time);
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].wait_time;
    }

    printf("avg wait time:%f\n",total_wt/n);
    printf("avg turnaround time:%f",total_tat/n);

    return 0;
}
