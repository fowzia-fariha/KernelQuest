/*
Priority Scheduling (Non-Preemptive)

This program simulates non-preemptive priority scheduling with different arrival times.
At each step, the highest-priority available process is selected and executed to completion.
It calculates and displays Completion Time (CT), Turnaround Time (TAT), Waiting Time (WT), and Response Time (RT) for each process.
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int id, at, bt, priority, ct, tat, wt, rt;
    bool completed = false;
};

int findNext(const vector<Process>& p, int time) {
    int max_priority = -1, idx = -1;
    for (int i = 0; i < p.size(); ++i) {
        if (!p[i].completed && p[i].at <= time) {
            if (p[i].priority > max_priority) {
                max_priority = p[i].priority;
                idx = i;
            }
        }
    }
    return idx;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        cout << "Enter AT, BT, Priority for P" << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].priority;
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = findNext(p, time);
        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].rt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = true;
        completed++;
    }

    cout << "\n"
         << left << setw(5) << "PID"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "Pri"
         << setw(10) << "CT"
         << setw(10) << "TAT"
         << setw(10) << "WT"
         << setw(8) << "RT" << endl;

    for (const auto& proc : p) {
        cout << left << "P" << setw(4) << proc.id
             << setw(8) << proc.at
             << setw(8) << proc.bt
             << setw(8) << proc.priority
             << setw(10) << proc.ct
             << setw(10) << proc.tat
             << setw(10) << proc.wt
             << setw(8) << proc.rt << endl;
    }

    return 0;
}
