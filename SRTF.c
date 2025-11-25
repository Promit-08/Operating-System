#include <stdio.h>

struct Process 
{
    int pid;          
    int arrivalTime;   
    int burstTime;     
    int remainingTime; 
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

void SRTF(struct Process p[], int n) 
{
    int completed = 0, currentTime = 0, minRemainingTime, shortestJobIndex;
    int isAnyProcessAvailable = 0;

    while (completed < n) 
    {
        minRemainingTime = 9999;
        shortestJobIndex = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0 && p[i].remainingTime < minRemainingTime) 
            {
                minRemainingTime = p[i].remainingTime;
                shortestJobIndex = i;
                isAnyProcessAvailable = 1;
            }
        }

        if (!isAnyProcessAvailable) 
        {
            currentTime++;  
            continue;
        }

        p[shortestJobIndex].remainingTime--;

        if (p[shortestJobIndex].remainingTime == 0) 
        {
            completed++;
            p[shortestJobIndex].completionTime = currentTime + 1;
            p[shortestJobIndex].turnaroundTime = p[shortestJobIndex].completionTime - p[shortestJobIndex].arrivalTime;
            p[shortestJobIndex].waitingTime = p[shortestJobIndex].turnaroundTime - p[shortestJobIndex].burstTime;
        }

        currentTime++;
    }
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
        p[i].remainingTime = p[i].burstTime; 
        p[i].isCompleted = 0;  
    }
    SRTF(p, n);
    printProcesses(p, n);
    return 0;
}