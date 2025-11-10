#include <bits/stdc++.h>
using namespace std;
#define int long long

// Bankers Algorithm
// input:
// 5 3
// 10 5 7

// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// 7 5 3
// 3 2 2
// 9 0 2
// 4 2 2
// 5 3 3

void solve() {
    int p, r;
    cin >> p >> r;

    vector<vector<int>> allocation(p, vector<int>(r));
    vector<vector<int>> max_need(p, vector<int>(r));
    vector<vector<int>> rem_need(p, vector<int>(r));
    vector<int> given_resources(r), available(r);

    // Prompt: Total Available Resources
    cout << "Enter total available resources (" << r << " values): " << flush;
    for (int i = 0; i < r; i++) cin >> given_resources[i];

    // Prompt: Allocation Matrix
    cout << "Enter allocation matrix (" << p << "x" << r << "):" << endl;
    for (int i = 0; i < p; i++) {
        cout << "P" << i << ": " << flush;
        for (int j = 0; j < r; j++)
            cin >> allocation[i][j];
    }

    // Prompt: Maximum Need Matrix
    cout << "Enter maximum need matrix (" << p << "x" << r << "):" << endl;
    for (int i = 0; i < p; i++) {
        cout << "P" << i << ": " << flush;
        for (int j = 0; j < r; j++)
            cin >> max_need[i][j];
    }

    // Calculate remaining need = max - allocation
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            rem_need[i][j] = max_need[i][j] - allocation[i][j];

    // Calculate available = given - allocated
    for (int j = 0; j < r; j++) {
        int sum = 0;
        for (int i = 0; i < p; i++)
            sum += allocation[i][j];
        available[j] = given_resources[j] - sum;
    }

    // Banker's Algorithm
    vector<bool> finished(p, false);
    vector<int> safe_sequence;
    int completed = 0;

    while (completed < p) {
        bool found = false;
        for (int i = 0; i < p; i++) {
            if (!finished[i]) {
                bool can_run = true;
                for (int j = 0; j < r; j++) {
                    if (rem_need[i][j] > available[j]) {
                        can_run = false;
                        break;
                    }
                }
                if (can_run) {
                    for (int j = 0; j < r; j++)
                        available[j] += allocation[i][j];
                    finished[i] = true;
                    safe_sequence.push_back(i);
                    completed++;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    // Output Remaining Need
    cout << "\nRemaining Need Matrix:\n";
    for (int i = 0; i < p; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < r; j++)
            cout << setw(3) << rem_need[i][j] << " ";
        cout << endl;
    }

    // Output Result
    if (completed == p) {
        cout << "\nSystem is in a Safe state.\nSafe Sequence: ";
        for (int i = 0; i < safe_sequence.size(); i++) {
            cout << "P" << safe_sequence[i];
            if (i != safe_sequence.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nSystem is in an Unsafe state." << endl;
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
