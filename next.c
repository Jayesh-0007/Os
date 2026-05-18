#include <stdio.h>

int main() {
    int nb, np;

    printf("Enter number of blocks: ");
    scanf("%d", &nb);

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int block[nb], process[np], allocation[np];

    printf("Enter block sizes:\n");
    for(int i = 0; i < nb; i++)
        scanf("%d", &block[i]);

    printf("Enter process sizes:\n");
    for(int i = 0; i < np; i++) {
        scanf("%d", &process[i]);
        allocation[i] = -1;
    }

    int last = 0;

    for(int i = 0; i < np; i++) {
        int count = 0;

        while(count < nb) {
            if(block[last] >= process[i]) {
                allocation[i] = last;
                block[last] -= process[i];
                break;
            }

            last = (last + 1) % nb;
            count++;
        }
    }

    printf("\nProcess\tBlock\n");
    for(int i = 0; i < np; i++) {
        if(allocation[i] != -1)
            printf("P%d\t%d\n", i+1, allocation[i]+1);
        else
            printf("P%d\tNot Allocated\n", i+1);
    }

    return 0;
}