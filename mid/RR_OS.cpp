#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst, remaining, completion, turnaround, waiting;
};

void roundRobin(vector<Process>& processes, int time_quantum) {
    int n = processes.size();
    queue<int> q;
    vector<int> remaining(n);
    int current_time = 0, idx = 0, completed = 0;
    double totalTurnaround = 0, totalWaiting = 0;
    vector<string> gantt_chart;

    // Initialize remaining burst times
    for (int i = 0; i < n; ++i) remaining[i] = processes[i].burst;

    while (completed < n) {
        while (idx < n && processes[idx].arrival <= current_time) {
            q.push(idx);
            idx++;
        }

        if (q.empty()) {
            gantt_chart.push_back("Idle " + to_string(current_time) + "-" + to_string(processes[idx].arrival));
            current_time = processes[idx].arrival;
            continue;
        }

        int i = q.front();
        q.pop();
        int exec_time = min(time_quantum, remaining[i]);
        gantt_chart.push_back("P" + to_string(processes[i].id) + " " + to_string(current_time) + "-" + to_string(current_time + exec_time));
        current_time += exec_time;
        remaining[i] -= exec_time;

        while (idx < n && processes[idx].arrival <= current_time) {
            q.push(idx);
            idx++;
        }

        if (remaining[i] > 0) {
            q.push(i);
        } else {
            processes[i].completion = current_time;
            processes[i].turnaround = processes[i].completion - processes[i].arrival;
            processes[i].waiting = processes[i].turnaround - processes[i].burst;
            totalTurnaround += processes[i].turnaround;
            totalWaiting += processes[i].waiting;
            completed++;
        }
    }

    // Display Gantt Chart
    cout << "\nGantt Chart:\n";
    for (const auto& entry : gantt_chart) {
        cout << entry << endl;
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
    int n, time_quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> time_quantum;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].id = i + 1;
        processes[i].remaining = processes[i].burst;
    }

    roundRobin(processes, time_quantum);

    return 0;
}
