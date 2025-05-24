/*
Preemptive Priority Scheduling (Higher number indicates higher priority)

This program simulates preemptive priority scheduling with different arrival times.
At every time unit, it selects the ready process with the highest priority (numerically highest).
It calculates Completion Time (CT), Turnaround Time (TAT), Waiting Time (WT), and Response Time (RT).
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int id, at, bt, remaining_bt, priority;
    int ct, tat, wt, rt, start = -1;
    bool completed = false;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time, Burst Time, and Priority for P" << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].priority;
        p[i].remaining_bt = p[i].bt;
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, highest_priority = -1;

        for (int i = 0; i < n; ++i) {
            if (p[i].at <= time && p[i].remaining_bt > 0) {
                if (p[i].priority > highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].start == -1)
                p[idx].start = time;

            p[idx].remaining_bt--;
            time++;

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].rt = p[idx].start - p[idx].at;
                p[idx].completed = true;
                completed++;
            }
        } else {
            time++;
        }
    }

    cout << "\nPriority Scheduling Note: A higher priority value indicates a higher scheduling priority.\n\n";
    cout << left << setw(5) << "PID"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "PRI"
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
