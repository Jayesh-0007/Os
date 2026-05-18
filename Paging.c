#include <stdio.h>

int main() {
    int pageSize, n;

    printf("Enter page size: ");
    scanf("%d", &pageSize);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pageTable[n];

    printf("Enter frame number for each page:\n");
    for(int i = 0; i < n; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    int page, offset;

    printf("Enter page number: ");
    scanf("%d", &page);

    printf("Enter offset: ");
    scanf("%d", &offset);

    if(page >= n || offset >= pageSize) {
        printf("Invalid logical address\n");
    } else {
        int frame = pageTable[page];
        int physicalAddress = frame * pageSize + offset;

        printf("Physical Address = %d\n", physicalAddress);
    }

    return 0;
}