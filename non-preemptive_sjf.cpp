#include <iostream>
using namespace std;

struct Process {
    int pid, at, bt, ct, wt, tat;
    bool completed;
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
        p[i].completed = false;
    }

    int completed = 0, time = 0;

    while(completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && !p[i].completed) {
                if(p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = true;
            completed++;
            time = p[idx].ct;
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