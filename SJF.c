#include <stdio.h>

struct Process 
{
    int pid;        
    int arrivalTime;  
    int burstTime;    
    int completionTime; 
    int waitingTime;   
    int turnaroundTime; 
    int isCompleted;   
};

void findWaitingTime(struct Process p[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
    }
}

void findTurnaroundTime(struct Process p[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
    }
}

void SJF(struct Process p[], int n) 
{
    int completed = 0, currentTime = 0;
    
    while (completed < n) {
        int shortestJobIndex = -1;
        int minBurstTime = 9999;  
        for (int i = 0; i < n; i++) 
        {
            if (p[i].arrivalTime <= currentTime && !p[i].isCompleted && p[i].burstTime < minBurstTime) 
            {
                minBurstTime = p[i].burstTime;
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex == -1) 
        {
            currentTime++;  
            continue;
        }
        
        currentTime += p[shortestJobIndex].burstTime;
        p[shortestJobIndex].completionTime = currentTime;
        p[shortestJobIndex].isCompleted = 1;
        completed++;
    }

    findTurnaroundTime(p, n);
    findWaitingTime(p, n);
}

void printProcesses(struct Process p[], int n) 
{
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].arrivalTime, p[i].burstTime, 
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }
}

int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) 
    {
        printf("\nEnter details for Process %d\n", i + 1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &p[i].burstTime);
        p[i].isCompleted = 0;  
    }
    SJF(p, n);
    printProcesses(p, n);
    return 0;
}