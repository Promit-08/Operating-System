#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    int b[n], p[n], arrival[n], index[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time, Burst Time and Priority Value for Process %d: ", i  + 1);
        scanf("%d %d %d", &arrival[i],&b[i], &p[i]);
        index[i] = i + 1;
    }

    for (int i = 0; i < n; i++)
    {
        int max_priority = p[i], max_index = i;

        for (int j = i + 1; j < n; j++)
        {
            if (p[j] > max_priority)
            {
                max_priority = p[j];
                max_index = j;
            }
        }

        swap(&p[i], &p[max_index]);
        swap(&b[i], &b[max_index]);
        swap(&arrival[i], &arrival[max_index]);
        swap(&index[i], &index[max_index]);
    }

    int t = 0;
    printf("\nOrder of Process Execution is\n");
    for (int i = 0; i < n; i++)
    {
        if (t < arrival[i])
        {
            t = arrival[i];
        }
        printf("P%d is executed from %d to %d\n", index[i], t, t + b[i]);
        t += b[i];
    }

    printf("\n");
    printf("Process Id\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\n");

    int wait_time = 0;
    int turnaround_time;

    for (int i = 0; i < n; i++)
    {
        turnaround_time = wait_time + b[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", index[i], b[i], arrival[i], wait_time - arrival[i], turnaround_time);
        wait_time += b[i];
    }
}
