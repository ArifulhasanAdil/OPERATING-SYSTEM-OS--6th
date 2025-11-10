#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct Process {
    int pid, arrival, burst, start, completion, turnaround;
};

bool compareArrival(Process a, Process b) {
    return a.arrival < b.arrival;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cout << "Enter arrival time and burst time for Process " << p[i].pid << ": ";
        cin >> p[i].arrival >> p[i].burst;
    }

    // Sort by arrival time
    sort(p.begin(), p.end(), compareArrival);

    int currentTime = 0, totalTurnaround = 0;
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < n; ++i) {
        if (currentTime < p[i].arrival) {
            cout << "| IDLE | ";
            cout << currentTime << " - " << p[i].arrival << "\n";
            currentTime = p[i].arrival;
        }

        p[i].start = currentTime;
        p[i].completion = currentTime + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival; // Calculate turnaround time
        totalTurnaround += p[i].turnaround; // Accumulate turnaround time

        cout << "| P" << p[i].pid << "   | ";
        cout << p[i].start << " - " << p[i].completion << "\n";

        currentTime = p[i].completion;
    }

    // Calculate and display average turnaround time
    double avgTurnaround = (double)totalTurnaround / n;
    cout << "\nAverage Turnaround Time: " << avgTurnaround << "\n";

    return 0;
}
