/*
    Non-Preemptive Shortest Job First (SJF) Scheduling

    Simulates the SJF algorithm where the shortest available job is selected 
    at each step and runs to completion without interruption.

    Calculates and displays start, completion, turnaround, and waiting times 
    for each process, along with a Gantt chart showing execution order.
*/

#include <iostream>
#include <iomanip>
#include <climits> // For INT_MAX
using namespace std;

#define MAX_TIME 1000

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool completed;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time for Process P" << p[i].pid << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter Burst Time for Process P" << p[i].pid << ": ";
        cin >> p[i].burst_time;
        p[i].completed = false;
    }

    int completed = 0, time = 0;
    int timeline[MAX_TIME];
    int timeline_index = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_burst) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].start_time = time;
            for (int t = 0; t < p[idx].burst_time; t++) {
                timeline[timeline_index++] = p[idx].pid;
            }

            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].completed = true;
            time = p[idx].completion_time;
            completed++;
        } else {
            timeline[timeline_index++] = -1; // CPU idle
            time++;
        }
    }

    // Print Process Table
    cout << "\n"
         << left << setw(5) << "PID" 
         << setw(14) << "Arrival Time" 
         << setw(12) << "Burst Time" 
         << setw(12) << "Start Time" 
         << setw(18) << "Completion Time" 
         << setw(18) << "Turnaround Time" 
         << setw(14) << "Waiting Time" << endl;

    for (int i = 0; i < n; i++) {
        cout << left << "P" << setw(4) << p[i].pid 
             << setw(14) << p[i].arrival_time 
             << setw(12) << p[i].burst_time 
             << setw(12) << p[i].start_time 
             << setw(18) << p[i].completion_time 
             << setw(18) << p[i].turnaround_time 
             << setw(14) << p[i].waiting_time << endl;
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < timeline_index; i++) {
        if (i == 0 || timeline[i] != timeline[i - 1]) {
            if (timeline[i] == -1)
                cout << " Idle |";
            else
                cout << " P" << timeline[i] << " |";
        }
    }

    cout << "\n0";
    for (int i = 1; i < timeline_index; i++) {
        if (timeline[i] != timeline[i - 1]) {
            cout << setw(6) << i;
        }
    }
    cout << setw(6) << timeline_index << endl;

    return 0;
}
