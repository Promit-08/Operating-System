#include <stdio.h>
#include <stdlib.h>
#define MAX_PARTITIONS 10

int partitionSize[MAX_PARTITIONS];
int isOccupied[MAX_PARTITIONS];
int partitionProcessID[MAX_PARTITIONS];
int processID[100];
int processSize[100];

void initializePartitions(int numPartitions)
{
    for (int i = 0; i < numPartitions; i++)
    {
        partitionSize[i] = (rand() % 100) + 50;
        isOccupied[i] = 0;
        partitionProcessID[i] = -1;
    }
}

int allocateMemoryFirstFit(int numPartitions, int processID, int processSize)
{
    for (int i = 0; i < numPartitions; i++)
    {
        if (!isOccupied[i] && partitionSize[i] >= processSize)
        {
            isOccupied[i] = 1;
            partitionProcessID[i] = processID;
            printf("\nAllocated process %d to partition %d (Size: %d)\n", processID, i + 1, partitionSize[i]);
            return 1;
        }
    }
    return 0;
}

int allocateMemoryBestFit(int numPartitions, int processID, int processSize)
{
    int bestFitIndex = -1;
    int minRemainingSpace = -1;

    for (int i = 0; i < numPartitions; i++)
    {
        if (!isOccupied[i] && partitionSize[i] >= processSize)
        {
            int remainingSpace = partitionSize[i] - processSize;
            if (bestFitIndex == -1 || remainingSpace < minRemainingSpace)
            {
                bestFitIndex = i;
                minRemainingSpace = remainingSpace;
            }
        }
    }

    if (bestFitIndex != -1)
    {
        isOccupied[bestFitIndex] = 1;
        partitionProcessID[bestFitIndex] = processID;
        printf("\nAllocated process %d to partition %d (Size: %d)\n", processID, bestFitIndex + 1, partitionSize[bestFitIndex]);
        return 1;
    }

    return 0;
}

int allocateMemoryWorstFit(int numPartitions, int processID, int processSize)
{
    int worstFitIndex = -1;
    int maxRemainingSpace = -1;

    for (int i = 0; i < numPartitions; i++)
    {
        if (!isOccupied[i] && partitionSize[i] >= processSize)
        {
            int remainingSpace = partitionSize[i] - processSize;
            if (worstFitIndex == -1 || remainingSpace > maxRemainingSpace)
            {
                worstFitIndex = i;
                maxRemainingSpace = remainingSpace;
            }
        }
    }

    if (worstFitIndex != -1)
    {
        isOccupied[worstFitIndex] = 1;
        partitionProcessID[worstFitIndex] = processID;
        printf("\nAllocated process %d to partition %d (Size: %d)\n", processID, worstFitIndex + 1, partitionSize[worstFitIndex]);
        return 1;
    }

    return 0;
}

void displayPartitions(int numPartitions)
{
    printf("\n\tPartition Status \n");
    printf(" Partition  Size  Occupied  Process ID  \n");
    for (int i = 0; i < numPartitions; i++)
    {
        printf(" %-9d  %-4d  %-8s  %-11d \n",
               i + 1, partitionSize[i],
               isOccupied[i] ? "Yes" : "No",
               isOccupied[i] ? partitionProcessID[i] : -1);
    }
}

int main()
{
    int numPartitions, numProcesses, allocationChoice;
    printf("Enter the number of partitions: ");
    scanf("%d", &numPartitions);

    if (numPartitions > MAX_PARTITIONS)
    {
        printf("Maximum partitions allowed are %d.\n", MAX_PARTITIONS);
        return 1;
    }

    initializePartitions(numPartitions);

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++)
    {
        processID[i] = i + 1;
        printf("Enter size of process %d: ", processID[i]);
        scanf("%d", &processSize[i]);
    }

    printf("\nSelect allocation strategy:\n");
    printf("1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &allocationChoice);

    for (int i = 0; i < numProcesses; i++)
    {
        int allocated = 0;

        if (allocationChoice == 1)
        {
            allocated = allocateMemoryFirstFit(numPartitions, processID[i], processSize[i]);
        }
        else if (allocationChoice == 2)
        {
            allocated = allocateMemoryBestFit(numPartitions, processID[i], processSize[i]);
        }
        else if (allocationChoice == 3)
        {
            allocated = allocateMemoryWorstFit(numPartitions, processID[i], processSize[i]);
        }

        if (!allocated)
        {
            printf("Process %d could not be allocated memory.\n", processID[i]);
        }
    }

    displayPartitions(numPartitions);

    return 0;
}
