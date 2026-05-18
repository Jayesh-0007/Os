#include <stdio.h>

int main() {
    int n;

    printf("Enter number of segments: ");
    scanf("%d", &n);

    int base[n], limit[n];

    printf("Enter base and limit for each segment:\n");
    for(int i = 0; i < n; i++) {
        printf("Segment %d Base: ", i);
        scanf("%d", &base[i]);
        printf("Segment %d Limit: ", i);
        scanf("%d", &limit[i]);
    }

    int seg, offset;

    printf("Enter segment number: ");
    scanf("%d", &seg);

    printf("Enter offset: ");
    scanf("%d", &offset);

    if(seg >= n || offset >= limit[seg]) {
        printf("Invalid logical address (Segmentation Fault)\n");
    } else {
        int physicalAddress = base[seg] + offset;
        printf("Physical Address = %d\n", physicalAddress);
    }

    return 0;
}