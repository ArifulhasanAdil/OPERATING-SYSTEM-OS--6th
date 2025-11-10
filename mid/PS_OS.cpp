#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, priority, arrival, burst, remaining, completion, turnaround, waiting;
};

// Sorting function: First by arrival time, then by priority
bool compare(Process a, Process b) {
    if (a.arrival == b.arrival)
        return a.priority < b.priority;
    return a.arrival < b.arrival;
}

void priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), compare);

    int currentTime = 0, totalTurnaround = 0, totalWaiting = 0;
    vector<string> gantt_chart;
    vector<bool> done(n, false);

    while (count(done.begin(), done.end(), true) < n) {
        int idx = -1, highestPriority = INT_MAX;

        // Select process with highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrival <= currentTime && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }

        // If no process is available, CPU remains idle
        if (idx == -1) {
            gantt_chart.push_back("Idle " + to_string(currentTime) + "-" + to_string(processes[count(done.begin(), done.end(), false)].arrival));
            currentTime = processes[count(done.begin(), done.end(), false)].arrival;
            continue;
        }

        // Execute process
        gantt_chart.push_back("P" + to_string(processes[idx].id) + " " + to_string(currentTime) + "-" + to_string(currentTime + processes[idx].burst));
        processes[idx].completion = currentTime + processes[idx].burst;
        processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
        totalTurnaround += processes[idx].turnaround;
        totalWaiting += processes[idx].waiting;
        currentTime += processes[idx].burst;
        done[idx] = true;
    }

    // Display Gantt Chart
    cout << "\nGantt Chart:\n";
    for (const auto& entry : gantt_chart) {
        cout << entry << endl;
    }

    // Display process completion details
    cout << "\nProcess Completion Times:\n";
    cout << "PID\tPriority\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &proc : processes) {
        cout << "P" << proc.id << "\t" << proc.priority << "\t\t" << proc.arrival << "\t"
             << proc.burst << "\t" << proc.completion << "\t" << proc.turnaround << "\t" << proc.waiting << endl;
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
        cout << "Enter priority, arrival time, and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].priority >> processes[i].arrival >> processes[i].burst;
        processes[i].id = i + 1;
        processes[i].remaining = processes[i].burst;
    }

    priorityScheduling(processes);

    return 0;
}
