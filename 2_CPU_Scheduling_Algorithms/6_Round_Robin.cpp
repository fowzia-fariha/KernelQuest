/*Round Robin Scheduling (Preemptive)
-----------------------------------
This program simulates a preemptive Round Robin CPU scheduling algorithm.
Each process is given a fixed time quantum. If a process doesn't finish in its time slice,
it is preempted and added to the back of the ready queue.*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main()
{
    int n, time_quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i)
    {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time for P" << p[i].pid << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter Burst Time for P" << p[i].pid << ": ";
        cin >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
    }

    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    int time = 0, completed = 0;
    vector<int> queue;
    vector<bool> in_queue(n, false);

    // Enqueue processes that arrive at time 0
    for (int i = 0; i < n; ++i)
    {
        if (p[i].arrival_time == 0)
        {
            queue.push_back(i);
            in_queue[i] = true;
        }
    }

    if (queue.empty())
    {
        int earliest = 0;
        for (int i = 1; i < n; ++i)
            if (p[i].arrival_time < p[earliest].arrival_time)
                earliest = i;
        time = p[earliest].arrival_time;
        queue.push_back(earliest);
        in_queue[earliest] = true;
    }

    while (completed < n)
    {
        if (queue.empty())
        {
            int next_arrival = 1e9, idx = -1;
            for (int i = 0; i < n; ++i)
            {
                if (!in_queue[i] && p[i].remaining_time > 0 && p[i].arrival_time < next_arrival)
                {
                    next_arrival = p[i].arrival_time;
                    idx = i;
                }
            }
            time = next_arrival;
            queue.push_back(idx);
            in_queue[idx] = true;
        }

        int current = queue.front();
        queue.erase(queue.begin());

        int exec_time = min(p[current].remaining_time, time_quantum);
        p[current].remaining_time -= exec_time;
        time += exec_time;

        // Add new arrivals to queue
        for (int i = 0; i < n; ++i)
        {
            if (!in_queue[i] && p[i].arrival_time <= time && p[i].remaining_time > 0)
            {
                queue.push_back(i);
                in_queue[i] = true;
            }
        }

        // Re-enqueue if not done
        if (p[current].remaining_time > 0)
        {
            queue.push_back(current);
        }
        else
        {
            p[current].completion_time = time;
            p[current].turnaround_time = time - p[current].arrival_time;
            p[current].waiting_time = p[current].turnaround_time - p[current].burst_time;
            completed++;
        }
    }

    // Output Table
    cout << "\n------------------------------------ Process Scheduling Table ------------------------------------\n";
    cout << left << setw(8) << "PID"
         << setw(15) << "Arrival"
         << setw(12) << "Burst"
         << setw(18) << "Completion"
         << setw(18) << "Turnaround"
         << setw(14) << "Waiting" << "\n";
    cout << "-----------------------------------------------------------------------------------------------\n";

    for (const auto &proc : p)
    {
        cout << left << "P" << setw(7) << proc.pid
             << setw(15) << proc.arrival_time
             << setw(12) << proc.burst_time
             << setw(18) << proc.completion_time
             << setw(18) << proc.turnaround_time
             << setw(14) << proc.waiting_time << "\n";
    }

    return 0;
}
