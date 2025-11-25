#include <stdio.h>

struct Process 
{
    int pid;        
    int arrivalTime;  
    int burstTime;    
    int completionTime; 
    int waitingTime;   
    int turnaroundTime; 
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

void findCompletionTime(struct Process p[], int n) 
{
    int currentTime = 0;
    for (int i = 0; i < n; i++) 
    {
        if (currentTime < p[i].arrivalTime) 
        {
            currentTime = p[i].arrivalTime;
        }
        currentTime += p[i].burstTime;
        p[i].completionTime = currentTime;
    }
}

void FCFS(struct Process p[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrivalTime > p[j].arrivalTime) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    findCompletionTime(p, n);
    findTurnaroundTime(p, n);
    findWaitingTime(p, n);
}

void printProcesses(struct Process p[], int n) 
{
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) 
    {
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
    }

    FCFS(p, n);
    printProcesses(p, n);

    return 0;
}