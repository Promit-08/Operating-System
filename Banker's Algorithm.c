#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

void printMatrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], int rows, int cols, const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int processes[], int avail[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES], int numProcesses, int numResources) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];

    // Initialize work as available resources
    for (int i = 0; i < numResources; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < numProcesses) {
        bool found = false;

        for (int p = 0; p < numProcesses; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < numResources; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int r = 0; r < numResources; r++) {
                        work[r] += alloc[p][r];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    printf("The system is in a safe state. Safe sequence: ");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int processes[MAX_PROCESSES] = {0, 1, 2, 3, 4};
    int numProcesses = 5;
    int numResources = 3;

    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {4, 2, 2},
        {5, 3, 3}
    };

    int avail[MAX_RESOURCES] = {3, 3, 2};

    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printMatrix(alloc, numProcesses, numResources, "Allocation Matrix");
    printMatrix(max, numProcesses, numResources, "Max Matrix");
    printMatrix(need, numProcesses, numResources, "Need Matrix");

    isSafe(processes, avail, max, alloc, need, numProcesses, numResources);

    return 0;
}
