#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], visited[n];

    printf("Enter request sequence:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        visited[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for(int i = 0; i < n; i++) {
        int min = 1e9, index = -1;

        for(int j = 0; j < n; j++) {
            if(!visited[j]) {
                int dist = abs(req[j] - head);
                if(dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        seek += min;
        head = req[index];
    }

    printf("Total Seek Time (SSTF): %d\n", seek);
    return 0;
}