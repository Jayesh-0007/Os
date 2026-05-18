#include <stdio.h>
#define MAX 100

struct Process {
    int id, at, bt, rt, ct, tat, wt, priority;
};

void input(struct Process p[], int n, int isPriority) {
    for(int i = 0; i < n; i++) {
        p[i].id = i;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        if(isPriority) scanf("%d", &p[i].priority);
    }
}

void print(struct Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
}

void fcfs(struct Process p[], int n) {
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
    }
    print(p, n);
}

void sjf_np(struct Process p[], int n) {
    int completed = 0, time = 0, visited[MAX] = {0};
    while(completed < n) {
        int idx = -1, min = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !visited[i] && p[i].bt < min) {
                min = p[i].bt;
                idx = i;
            }
        }
        if(idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            visited[idx] = 1;
            completed++;
        } else time++;
    }
    print(p, n);
}

void sjf_p(struct Process p[], int n) {
    int completed = 0, time = 0;
    while(completed < n) {
        int idx = -1, min = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0 && p[i].rt < min) {
                min = p[i].rt;
                idx = i;
            }
        }
        if(idx != -1) {
            p[idx].rt--;
            time++;
            if(p[idx].rt == 0) {
                p[idx].ct = time;
                completed++;
            }
        } else time++;
    }
    print(p, n);
}

void priority_np(struct Process p[], int n) {
    int completed = 0, time = 0, visited[MAX] = {0};
    while(completed < n) {
        int idx = -1, best = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !visited[i] && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }
        if(idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            visited[idx] = 1;
            completed++;
        } else time++;
    }
    print(p, n);
}

void priority_p(struct Process p[], int n) {
    int completed = 0, time = 0;
    while(completed < n) {
        int idx = -1, best = 1e9;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0 && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }
        if(idx != -1) {
            p[idx].rt--;
            time++;
            if(p[idx].rt == 0) {
                p[idx].ct = time;
                completed++;
            }
        } else time++;
    }
    print(p, n);
}

void round_robin(struct Process p[], int n, int tq) {
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};
    int time = 0, completed = 0;

    for(int i = 0; i < n; i++) {
        if(p[i].at == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(completed < n) {
        if(front == rear) {
            time++;
            for(int i = 0; i < n; i++) {
                if(p[i].at <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        if(p[i].rt > tq) {
            time += tq;
            p[i].rt -= tq;
        } else {
            time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = time;
            completed++;
        }

        for(int j = 0; j < n; j++) {
            if(p[j].at <= time && !visited[j]) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(p[i].rt > 0) queue[rear++] = i;
    }

    print(p, n);
}

int main() {
    int choice, n, tq;
    struct Process p[MAX];

    scanf("%d", &n);

    do {
        printf("\n1.FCFS\n2.SJF(NP)\n3.SJF(P)\n4.Priority(NP)\n5.Priority(P)\n6.RoundRobin\n0.Exit\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                input(p, n, 0);
                fcfs(p, n);
                break;
            case 2:
                input(p, n, 0);
                sjf_np(p, n);
                break;
            case 3:
                input(p, n, 0);
                sjf_p(p, n);
                break;
            case 4:
                input(p, n, 1);
                priority_np(p, n);
                break;
            case 5:
                input(p, n, 1);
                priority_p(p, n);
                break;
            case 6:
                input(p, n, 0);
                scanf("%d", &tq);
                round_robin(p, n, tq);
                break;
        }

    } while(choice != 0);

    return 0;
}