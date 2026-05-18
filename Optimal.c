#include <stdio.h>

int predict(int pages[], int frame[], int n, int frames, int index) {
    int farthest = index, pos = -1;

    for(int i = 0; i < frames; i++) {
        int j;
        for(j = index; j < n; j++) {
            if(frame[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        if(j == n)
            return i;
    }

    return (pos == -1) ? 0 : pos;
}

int main() {
    int frames, n, faults = 0;

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
            int pos = -1;

            for(int j = 0; j < frames; j++) {
                if(frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
                pos = predict(pages, frame, n, frames, i + 1);

            frame[pos] = pages[i];
            faults++;
        }
    }

    printf("Optimal Page Faults = %d\n", faults);
    return 0;
}