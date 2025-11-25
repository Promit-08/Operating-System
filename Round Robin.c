#include <stdio.h>
void roundRobin(int processes[], int n, int bt[], int quantum) 
{
    int wt[n], tat[n], rem_bt[n];
    int t = 0;
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];
    while (1) 
    {
        int done = 1;

        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0) 
            {
                done = 0;
                if (rem_bt[i] > quantum) 
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } 
                else 
                {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
}

int main() 
{
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], bt[n];

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        processes[i] = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, bt, quantum);
    return 0;
}