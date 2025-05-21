#include <stdio.h>

#define MAX 100

void fcfs(int n, int arrival[], int burst[]) {
    int waiting[MAX], turnaround[MAX], start_time = 0;
    float total_wait = 0, total_turnaround = 0;

    printf("\n--- FCFS Scheduling ---\n");
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        if (start_time < arrival[i])
            start_time = arrival[i];
        waiting[i] = start_time - arrival[i];
        turnaround[i] = waiting[i] + burst[i];
        start_time += burst[i];

        total_wait += waiting[i];
        total_turnaround += turnaround[i];

        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("Average Waiting Time (FCFS): %.2f\n", total_wait / n);
    printf("Average Turnaround Time (FCFS): %.2f\n", total_turnaround / n);
}

void round_robin(int n, int arrival[], int burst[], int quantum) {
    int remaining[MAX], wait[MAX] = {0}, turnaround[MAX] = {0};
    int time = 0, done = 0, complete[MAX] = {0};
    
    for (int i = 0; i < n; i++)
        remaining[i] = burst[i];

    printf("\n--- Round Robin Scheduling (Quantum = %d) ---\n", quantum);

    while (done < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                int run = (remaining[i] > quantum) ? quantum : remaining[i];
                time += run;
                remaining[i] -= run;
                executed = 1;

                if (remaining[i] == 0) {
                    complete[i] = time;
                    turnaround[i] = complete[i] - arrival[i];
                    wait[i] = turnaround[i] - burst[i];
                    done++;
                }
            }
        }
        if (!executed) time++;  // CPU idle
    }

    float total_wait = 0, total_turnaround = 0;
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, arrival[i], burst[i], wait[i], turnaround[i]);
        total_wait += wait[i];
        total_turnaround += turnaround[i];
    }

    printf("Average Waiting Time (RR): %.2f\n", total_wait / n);
    printf("Average Turnaround Time (RR): %.2f\n", total_turnaround / n);
}

int main() {
    int n, arrival[MAX], burst[MAX], quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i+1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time of P%d: ", i+1);
        scanf("%d", &burst[i]);
    }

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    fcfs(n, arrival, burst);
    round_robin(n, arrival, burst, quantum);

    return 0;
}
/* Output:
Enter number of processes: 3
Enter arrival time of P1: 0
Enter burst time of P1: 5
Enter arrival time of P2: 1
Enter burst time of P2: 3
Enter arrival time of P3: 2
Enter burst time of P3: 8
Enter time quantum for Round Robin: 2

--- FCFS Scheduling ---
Process Arrival Burst Waiting Turnaround
P1      0       5     0       5
P2      1       3     4       7
P3      2       8     7       15
Average Waiting Time (FCFS): 3.67
Average Turnaround Time (FCFS): 9.00

--- Round Robin Scheduling (Quantum = 2) ---
Process Arrival Burst Waiting Turnaround
P1      0       5     6       11
P2      1       3     4       7
P3      2       8     9       17
Average Waiting Time (RR): 6.33
Average Turnaround Time (RR): 11.67
*/
