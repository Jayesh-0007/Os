#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];

    printf("Enter request sequence:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for(int i = 0; i < n; i++) {
        seek += abs(req[i] - head);
        head = req[i];
    }

    printf("Total Seek Time (FCFS): %d\n", seek);
    return 0;
}