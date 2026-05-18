#include <stdio.h>

int main() {
    int frames, n, faults = 0, index = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n], frame[frames];

    printf("Enter reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
        
        for(int i = 0; i < frames; i++)
        frame[i] = -1;
        
    for(int i = 0; i < n; i++) {
        int found = 0;
        
        for(int j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        
        if(!found) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            faults++;
        }
    }
    
    printf("FIFO Page Faults = %d\n", faults);
    return 0;
}