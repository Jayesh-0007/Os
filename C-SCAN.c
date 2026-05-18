#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, disk_size, seek = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], left[n], right[n];
    int l = 0, r = 0;

    printf("Enter request sequence:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    for(int i = 0; i < n; i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    // sort ascending
    for(int i = 0; i < l-1; i++)
        for(int j = i+1; j < l; j++)
            if(left[i] > left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }

    for(int i = 0; i < r-1; i++)
        for(int j = i+1; j < r; j++)
            if(right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    // move right
    for(int i = 0; i < r; i++) {
        seek += abs(right[i] - head);
        head = right[i];
    }

    // jump to beginning
    seek += abs((disk_size - 1) - head);
    seek += (disk_size - 1);
    head = 0;

    // service left
    for(int i = 0; i < l; i++) {
        seek += abs(left[i] - head);
        head = left[i];
    }

    printf("Total Seek Time (C-SCAN): %d\n", seek);
    return 0;
}