#include <stdio.h>

#define MAX 100

struct Process {
    int id, at, bt, rt, ct, tat, wt;
};

int queue[MAX];
int front = -1, rear = -1;

// Enqueue
void enqueue(int x) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = x;
}

// Dequeue
int dequeue() {
    if (front == -1) return -1;
    int x = queue[front];
    if (front == rear)
        front = rear = -1;
    else
        front++;
    return x;
}

// Check if queue is empty
int isEmpty() {
    return front == -1;
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int visited[n]; // to track if process is added to queue

    for (int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i);
        p[i].id = i;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        visited[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    // Add processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            enqueue(i);
            visited[i] = 1;
        }
    }

    while (completed < n) {

        if (isEmpty()) {
            time++; // CPU idle
            // check for new arrivals
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !visited[i]) {
                    enqueue(i);
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = dequeue();

        if (p[i].rt > tq) {
            time += tq;
            p[i].rt -= tq;
        } else {
            time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = time;
            completed++;
        }

        // Add newly arrived processes during execution
        for (int j = 0; j < n; j++) {
            if (p[j].at <= time && !visited[j]) {
                enqueue(j);
                visited[j] = 1;
            }
        }

        // If current process not finished → re-add to queue
        if (p[i].rt > 0) {
            enqueue(i);
        }
    }

    // Calculate TAT and WT
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}