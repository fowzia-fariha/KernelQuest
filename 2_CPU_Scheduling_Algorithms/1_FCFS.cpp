/*
    First-Come, First-Served (FCFS) CPU Scheduling Simulation

    This program simulates the FCFS CPU scheduling algorithm. 
    It takes arrival and burst times for 'n' processes, calculates 
    each process's start time, waiting time, and turnaround time, 
    and prints a summary table along with the average waiting and 
    turnaround times.

    FCFS processes are executed in the order they arrive. 
    This implementation automatically sorts processes based on arrival time.
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int start;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process p[n];

    cout << "Enter the Arrival Time of each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Process " << p[i].id << " Arrival Time: ";
        cin >> p[i].arrival;
    }

    cout << "Enter the Burst Time of each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << p[i].id << " Burst Time: ";
        cin >> p[i].burst;
    }

    // Sort processes by arrival time
    sort(p, p + n, [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    int total_waiting = 0, total_turnaround = 0;

    p[0].start = p[0].arrival;
    p[0].waiting = 0;
    p[0].turnaround = p[0].burst;
    total_turnaround += p[0].turnaround;

    for (int i = 1; i < n; i++) {
        int finish = p[i - 1].start + p[i - 1].burst;
        p[i].start = max(finish, p[i].arrival);
        p[i].waiting = p[i].start - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;
        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    cout << endl << "Process\tBT\tAT\tST\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].burst << "\t"
             << p[i].arrival << "\t"
             << p[i].start << "\t"
             << p[i].waiting << "\t"
             << p[i].turnaround << endl;
    }

    float avg_waiting = (float)total_waiting / n;
    float avg_turnaround = (float)total_turnaround / n;

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avg_waiting << endl;
    cout << "Average Turnaround Time: " << avg_turnaround << endl;

    return 0;
}
