/*
Preemptive Shortest Job First (SJF) Scheduling (Shortest Remaining Time First)

Selects the process with the shortest remaining burst time at every time unit.
A running process can be preempted if a shorter job arrives.
Calculates start, completion, turnaround, and waiting times for each process.
Displays the process table and a Gantt chart of execution.
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_started;
    bool is_completed;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time for Process P" << p[i].pid << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter Burst Time for Process P" << p[i].pid << ": ";
        cin >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
        p[i].is_completed = false;
        p[i].is_started = false;
    }

    int completed = 0, time = 0;
    vector<int> timeline;  // For Gantt chart

    while (completed < n) {
        int idx = -1;
        int min_remain = 1e9;

        for (int i = 0; i < n; ++i) {
            if (p[i].arrival_time <= time && !p[i].is_completed) {
                if (p[i].remaining_time < min_remain) {
                    min_remain = p[i].remaining_time;
                    idx = i;
                } else if (p[i].remaining_time == min_remain) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            if (!p[idx].is_started) {
                p[idx].start_time = time;
                p[idx].is_started = true;
            }

            p[idx].remaining_time--;
            timeline.push_back(p[idx].pid);
            time++;

            if (p[idx].remaining_time == 0) {
                p[idx].completion_time = time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].is_completed = true;
                completed++;
            }
        } else {
            timeline.push_back(-1);  // CPU idle
            time++;
        }
    }

    // Print Table Header
    cout << "\n"
         << left << setw(5) << "PID"
         << setw(14) << "Arrival Time"
         << setw(12) << "Burst Time"
         << setw(12) << "Start Time"
         << setw(18) << "Completion Time"
         << setw(18) << "Turnaround Time"
         << setw(14) << "Waiting Time" << endl;

    // Print Process Info
    for (const auto& proc : p) {
        cout << left << "P" << setw(4) << proc.pid
             << setw(14) << proc.arrival_time
             << setw(12) << proc.burst_time
             << setw(12) << proc.start_time
             << setw(18) << proc.completion_time
             << setw(18) << proc.turnaround_time
             << setw(14) << proc.waiting_time << endl;
    }

    // Print Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (size_t i = 0; i < timeline.size(); ++i) {
        if (i == 0 || timeline[i] != timeline[i - 1]) {
            if (timeline[i] == -1)
                cout << " Id |";
            else
                cout << " P" << timeline[i] << " |";
        }
    }

    cout << "\n0";
    for (size_t i = 1; i < timeline.size(); ++i) {
        if (timeline[i] != timeline[i - 1]) {
            cout << setw(5) << i;
        }
    }
    cout << setw(5) << timeline.size() << endl;

    return 0;
}


