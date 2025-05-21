#include <stdio.h>
 
 #define MAX 10
 
 typedef struct {
     int id, at, bt, ct, tat, wt, type;
 } Process;
 
 void fcfs(Process p[], int n, int *time) {
     for (int i = 0; i < n; i++) {
         if (*time < p[i].at) *time = p[i].at;
         p[i].ct = *time + p[i].bt;
         p[i].tat = p[i].ct - p[i].at;
         p[i].wt = p[i].tat - p[i].bt;
         *time = p[i].ct;
     }
 }
 
 int main() {
     int n, sys_count = 0, user_count = 0;
     Process p[MAX], sys[MAX], user[MAX];
 
     printf("Enter number of processes: ");
     scanf("%d", &n);
 
     for (int i = 0; i < n; i++) {
         p[i].id = i + 1;
         printf("Enter arrival time, burst time, and type (0=System, 1=User) for process %d: ", p[i].id);
         scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].type);
 
         if (p[i].type == 0)
             sys[sys_count++] = p[i];
         else
             user[user_count++] = p[i];
     }
 
     int time = 0;
     fcfs(sys, sys_count, &time);
     fcfs(user, user_count, &time);
 
     printf("\nID Type AT BT CT TAT WT\n");
     for (int i = 0; i < sys_count; i++)
         printf("%2d Sys %2d %2d %2d %2d %2d\n", sys[i].id, sys[i].at, sys[i].bt, sys[i].ct, sys[i].tat, sys[i].wt);
     for (int i = 0; i < user_count; i++)
         printf("%2d User %2d %2d %2d %2d %2d\n", user[i].id, user[i].at, user[i].bt, user[i].ct, user[i].tat, user[i].wt);
 
     return 0;
 }

/* output:
Enter number of processes: 4
Enter arrival time, burst time, and type (0=System, 1=User) for process 1: 0 4 0
Enter arrival time, burst time, and type (0=System, 1=User) for process 2: 1 3 1
Enter arrival time, burst time, and type (0=System, 1=User) for process 3: 2 2 0
Enter arrival time, burst time, and type (0=System, 1=User) for process 4: 3 1 1

ID Type AT BT CT TAT WT
 1 Sys  0  4  4   4   0
 3 Sys  2  2  6   4   2
 2 User 1  3  9   8   5
 4 User 3  1 10   7   6
*/
