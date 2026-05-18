#include <iostream>
using namespace std;

struct Process {
    int pid, at, bt, rt, ct, wt, tat;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i+1;
        cout << "Enter AT and BT for P" << i+1 << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;   
    }

    int completed = 0, time = 0;

    while(completed < n) {
        int idx = -1;
        int minRT = 1e9;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].rt < minRT) {
                    minRT = p[i].rt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            p[idx].rt--;
            time++;

            if(p[idx].rt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        } else {
            time++;
        }
    }

    cout << "\nPID AT BT CT WT TAT\n";
    for(int i = 0; i < n; i++)
        cout << p[i].pid << "   "
             << p[i].at << "  "
             << p[i].bt << "  "
             << p[i].ct << "  "
             << p[i].wt << "  "
             << p[i].tat << endl;

    return 0;
}