#include <stdio.h>
#include <limits.h>

void priorityScheduling(int n, int bt[], int priority[]) {
    int wt[n], tat[n], finished[n];
    for (int i = 0; i < n; i++)
        finished[i] = 0;

    int t = 0, completed = 0;
    while (completed != n) {
        int min_priority = INT_MAX, idx = -1;

        for (int i = 0; i < n; i++) {
            if (!finished[i] && priority[i] < min_priority) {
                min_priority = priority[i];
                idx = i;
            }
        }

        if (idx != -1) {
            wt[idx] = t;
            t += bt[idx];
            tat[idx] = t;
            finished[idx] = 1;
            completed++;
        }
    }

    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], priority[i], wt[i], tat[i]);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int bt[n], priority[n];

    printf("Enter burst time and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d:\nBurst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
    }

    priorityScheduling(n, bt, priority);
    return 0;
}
