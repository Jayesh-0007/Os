#include <stdio.h>

struct Process {
    int id;
    int at;   
    int bt;   
    int rt;   
    int ct;   
    int tat;  
    int wt;   
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i);
        p[i].id = i;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; 
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    while(completed < n) {
        int executed = 0;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {

                if(p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    completed++;
                }

                executed = 1;
            }
        }

        if(executed == 0) {
            time++; 
        }
    }

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}