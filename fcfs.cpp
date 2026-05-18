#include<bits/stdc++.h>
using namespace std;
    struct process
    {
        int tat;
        int ct;
        int bt;
        int at;
        int pid;
        int wt;
    };
int main(){
    int n;
    cin>>n;
    process p[n];
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter AT and BT for P" << i+1 << ": ";
        cin >> p[i].at >> p[i].bt;
    }
    sort(p,p+n,[](process a,process b){
        return a.at<b.at;
    });
        int time = 0;

    for(int i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;
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

