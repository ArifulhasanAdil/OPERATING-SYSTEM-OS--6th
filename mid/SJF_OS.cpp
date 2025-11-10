#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst, remaining, completion, turnaround, waiting;
};

bool compareArrival(Process a, Process b) {
    return a.arrival < b.arrival;
}

void preemptiveSJF(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0, completed = 0;
    double totalTurnaround = 0, totalWaiting = 0;
    vector<bool> done(n, false);

    sort(processes.begin(), processes.end(), compareArrival);

    cout << "\nGantt Chart:\n";

    while (completed < n) {
        int idx = -1, minRemaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrival <= currentTime && processes[i].remaining < minRemaining) {
                minRemaining = processes[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) {
            currentTime++;
            continue;
        }

        int startTime = currentTime;
        while (idx != -1 && processes[idx].remaining > 0) {
            processes[idx].remaining--;
            currentTime++;

            // Check if a new process with a shorter burst time arrives
            for (int i = 0; i < n; i++) {
                if (!done[i] && processes[i].arrival <= currentTime && processes[i].remaining < processes[idx].remaining) {
                    cout << "P" << processes[idx].id << " " << startTime << "-" << currentTime << endl;
                    startTime = currentTime;
                    idx = i;
                }
            }
        }

        processes[idx].completion = currentTime;
        processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;

        totalTurnaround += processes[idx].turnaround;
        totalWaiting += processes[idx].waiting;

        done[idx] = true;
        completed++;

        cout << "P" << processes[idx].id << " " << startTime << "-" << currentTime << endl;
    }

    // Display process completion details
    cout << "\nProcess Completion Times:\n";
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &proc : processes) {
        cout << "P" << proc.id << "\t" << proc.arrival << "\t" << proc.burst << "\t"
             << proc.completion << "\t" << proc.turnaround << "\t" << proc.waiting << endl;
    }

    // Display average turnaround & waiting times
    cout << "\nAverage Turnaround Time: " << totalTurnaround / n << endl;
    cout << "Average Waiting Time: " << totalWaiting / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].id = i + 1;
        processes[i].remaining = processes[i].burst;
    }

    preemptiveSJF(processes);

    return 0;
}
