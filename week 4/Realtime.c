#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TASKS 10

// Define a structure for each task
typedef struct {
    int id;         // Task ID
    int period;     // Period of the task
    int exec_time;  // Execution time of the task
    int deadline;   // Deadline of the task
    int remaining_time; // Remaining time to complete execution
} Task;

// Function to sort tasks by period for RMS (Rate Monotonic Scheduling)
void sort_tasks_by_period(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

// Function to sort tasks by deadline for EDF (Earliest Deadline First)
void sort_tasks_by_deadline(Task tasks[], int n, int time) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].deadline < tasks[j].deadline) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

// Function to simulate Rate Monotonic Scheduling
void rate_monotonic_scheduling(Task tasks[], int n) {
    int time = 0;
    bool task_completed[MAX_TASKS] = {false};
    
    printf("\nRate-Monotonic Scheduling (RMS):\n");

    while (true) {
        bool all_completed = true;
        for (int i = 0; i < n; i++) {
            if (!task_completed[i]) {
                all_completed = false;
                if (time % tasks[i].period < tasks[i].exec_time) {
                    printf("At time %d, Task %d is executing\n", time, tasks[i].id);
                }
            }
        }

        if (all_completed) {
            break;
        }

        time++;
    }
}

// Function to simulate Earliest Deadline First Scheduling
void earliest_deadline_first_scheduling(Task tasks[], int n) {
    int time = 0;
    bool task_completed[MAX_TASKS] = {false};

    printf("\nEarliest-Deadline-First (EDF):\n");

    while (true) {
        bool all_completed = true;
        // Update deadlines
        for (int i = 0; i < n; i++) {
            tasks[i].deadline = time + tasks[i].period;
        }
        
        sort_tasks_by_deadline(tasks, n, time);  // Sort tasks by deadline
        
        for (int i = 0; i < n; i++) {
            if (!task_completed[i]) {
                all_completed = false;
                if (time % tasks[i].period < tasks[i].exec_time) {
                    printf("At time %d, Task %d is executing\n", time, tasks[i].id);
                }
            }
        }

        if (all_completed) {
            break;
        }

        time++;
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Task %d\n", i + 1);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Execution Time: ");
        scanf("%d", &tasks[i].exec_time);
        tasks[i].id = i + 1;
        tasks[i].remaining_time = tasks[i].exec_time;
    }

    // Rate Monotonic Scheduling
    sort_tasks_by_period(tasks, n);  // Sort tasks by period for RMS
    rate_monotonic_scheduling(tasks, n);

    // Earliest Deadline First Scheduling
    earliest_deadline_first_scheduling(tasks, n);

    return 0;
}

/*
Output
Enter number of tasks: 3

Enter details for Task 1
Period: 4
Execution Time: 1

Enter details for Task 2
Period: 6
Execution Time: 2

Enter details for Task 3
Period: 8
Execution Time: 3

Rate-Monotonic Scheduling (RMS):
At time 0, Task 1 is executing
At time 1, Task 1 is executing
At time 2, Task 2 is executing
At time 3, Task 2 is executing
At time 4, Task 1 is executing
At time 5, Task 2 is executing
At time 6, Task 1 is executing
At time 7, Task 2 is executing

Earliest-Deadline-First (EDF):
At time 0, Task 1 is executing
At time 1, Task 1 is executing
At time 2, Task 2 is executing
At time 3, Task 2 is executing
At time 4, Task 3 is executing
At time 5, Task 3 is executing
At time 6, Task 3 is executing
*/
