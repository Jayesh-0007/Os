#include <stdio.h>

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

    printf("\n");

    int remaining = memory;

    for(int i = 0; i < n; i++) {
        int req = process[i];
        int block = 1;

        // Find nearest power of 2
        while(block < req)
            block *= 2;

        printf("---------------------------------------\n");
        printf("P%d | Required: %d KB | Allocating: %d KB\n", i+1, req, block);
        printf("---------------------------------------\n");

        if(block <= remaining) {

            // Show splits happening
            int current = remaining;
            printf("Splitting:\n");
            while(current > block) {
                int half = current / 2;
                printf("  %d  ->  [%d] [%d]  (use left, right is free)\n", current, half, half);
                current = half;
            }
            printf("  Allocated %d KB to P%d\n", block, i+1);

            remaining -= block;
            printf("  Remaining free memory: %d KB\n\n", remaining);

        } else {
            printf("  Not enough memory! (block needed: %d KB, available: %d KB)\n\n", block, remaining);
        }
    }

    // Final summary
    printf("=======================================\n");
    printf("Process\t\tRequired\tAllocated\n");
    printf("=======================================\n");

    remaining = memory;
    for(int i = 0; i < n; i++) {
        int req = process[i];
        int block = 1;
        while(block < req)
            block *= 2;

        if(block <= remaining) {
            printf("P%d\t\t%d KB\t\t%d KB\n", i+1, req, block);
            remaining -= block;
        } else {
            printf("P%d\t\t%d KB\t\tNot Allocated\n", i+1, req);
        }
    }

    return 0;
}