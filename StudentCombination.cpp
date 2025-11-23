#include "StudentCombination.h"
#include <iostream>
#include <algorithm>

using namespace std;

StudentCombination::StudentCombination() {}

void StudentCombination::addStudent(const string& name) {
    students.push_back(name);
}

void StudentCombination::displayStudents() const {
    cout << "\n=== Students ===\n";
    for (size_t i = 0; i < students.size(); i++) {
        cout << i + 1 << ". " << students[i] << "\n";
    }
}

unsigned long long StudentCombination::factorialRecursive(int n) const {
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

unsigned long long StudentCombination::nCrRecursive(int n, int r) const {
    if (r == 0 || r == n) return 1;
    if (r == 1) return n;
    return nCrRecursive(n - 1, r - 1) + nCrRecursive(n - 1, r);
}

unsigned long long StudentCombination::countCombinations(int groupSize) const {
    int n = students.size();
    if (groupSize > n || groupSize < 0) return 0;
    return nCrRecursive(n, groupSize);
}

void StudentCombination::generateCombinationsRecursive(int start, int k, vector<int>& current,
    vector<vector<int>>& results) const {
    if (results.size() >= 1000) return;
    if ((int)current.size() == k) {
        results.push_back(current);
        return;
    }

    for (int i = start; i < (int)students.size(); i++) {
        current.push_back(i);
        generateCombinationsRecursive(i + 1, k, current, results);
        current.pop_back();
    }
}

void StudentCombination::generateGroups(int groupSize, vector<vector<string>>& groups,
    unsigned long long limit) const {
    groups.clear();
    vector<vector<int>> results;
    vector<int> current;

    generateCombinationsRecursive(0, groupSize, current, results);

    for (size_t i = 0; i < results.size() && i < limit; i++) {
        vector<string> group;
        for (int idx : results[i]) {
            group.push_back(students[idx]);
        }
        groups.push_back(group);
    }
}

void StudentCombination::assignToSessions(int sessionSize, int numSessions) {
    cout << "\n=== Session Assignments ===\n";
    int n = students.size();

    if (sessionSize * numSessions < n) {
        cout << "Warning: Not enough space for all students!\n";
    }

    int studentIdx = 0;
    for (int session = 0; session < numSessions && studentIdx < n; session++) {
        cout << "Session " << (session + 1) << ": ";
        for (int i = 0; i < sessionSize && studentIdx < n; i++) {
            cout << students[studentIdx++];
            if (i < sessionSize - 1 && studentIdx < n) cout << ", ";
        }
        cout << "\n";
    }
}