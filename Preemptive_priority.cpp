#include <stdio.h>

struct Process {
    int id;
    int at;   
    int bt;   
    int pr;   
    int rt;   
    int ct;   
    int tat;  
    int wt;   
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter AT, BT, Priority for P%d: ", i);
        p[i].id = i;
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt; 
    }

    int completed = 0, time = 0;

    while(completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].pr < highest_priority) {
                    highest_priority = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            p[idx].rt--;
            time++;

            if(p[idx].rt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        } else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}