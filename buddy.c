#include <stdio.h>
#include <math.h>

int main() {
    int memory, n;

    printf("Enter total memory (power of 2): ");
    scanf("%d", &memory);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int process[n];

    printf("Enter process sizes:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &process[i]);

    printf("\nProcess\tRequired\tAllocated\n");

    for(int i = 0; i < n; i++) {
        int req = process[i];
        int block = 1;

        // Find nearest power of 2
        while(block < req)
            block *= 2;

        if(block <= memory) {
            printf("P%d\t%d\t\t%d\n", i+1, req, block);
            memory -= block;
        } else {
            printf("P%d\t%d\t\tNot Allocated\n", i+1, req);
        }
    }

    return 0;
}