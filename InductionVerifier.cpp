#include "InductionVerifier.h"
#include <iostream>
#include <algorithm>

using namespace std;

InductionVerifier::InductionVerifier() {}

void InductionVerifier::addPrerequisite(const string& course, const string& prereq) {
    prereqMap[course].push_back(prereq);
}

bool InductionVerifier::verifyChainRecursive(const string& current, const string& target,
    vector<string>& chain, int depth) const {
    if (depth > 100) return false; // prevent infinite recursion

    chain.push_back(current);

    if (current == target) return true;

    if (prereqMap.count(current)) {
        for (const string& prereq : prereqMap.at(current)) {
            if (verifyChainRecursive(prereq, target, chain, depth + 1))
                return true;
        }
    }

    chain.pop_back();
    return false;
}

bool InductionVerifier::verifyPrerequisiteChain(const string& course, vector<string>& chain) const {
    chain.clear();
    return verifyChainRecursive(course, course, chain, 0);
}

bool InductionVerifier::canTakeCourseRecursive(const string& course,
    const vector<string>& completed,
    vector<string>& missing, int depth) const {
    if (depth > 100) return false;

    if (!prereqMap.count(course)) return true;

    for (const string& prereq : prereqMap.at(course)) {
        bool found = false;
        for (const string& comp : completed) {
            if (comp == prereq) {
                found = true;
                break;
            }
        }

        if (!found) {
            missing.push_back(prereq);
            if (!canTakeCourseRecursive(prereq, completed, missing, depth + 1))
                return false;
        }
    }

    return missing.empty();
}

bool InductionVerifier::canTakeCourse(const string& course,
    const vector<string>& completed,
    vector<string>& missing) const {
    missing.clear();
    return canTakeCourseRecursive(course, completed, missing, 0);
}

void InductionVerifier::displayPrerequisites() const {
    cout << "\n=== Course Prerequisites ===\n";
    for (const auto& pair : prereqMap) {
        cout << pair.first << " requires: ";
        for (size_t i = 0; i < pair.second.size(); i++) {
            cout << pair.second[i];
            if (i + 1 < pair.second.size()) cout << ", ";
        }
        cout << "\n";
    }
}

void InductionVerifier::proveByInduction(int n) const {
    cout << "\n=== Mathematical Induction Proof ===\n";
    cout << "Proving: Sum of first n natural numbers = n(n+1)/2\n\n";

    cout << "Base Case (n=1):\n";
    cout << "  LHS: 1\n";
    cout << "  RHS: 1(1+1)/2 = 1\n";
    cout << "  Base case holds!\n\n";

    cout << "Inductive Step:\n";
    cout << "  Assume true for n=k: 1+2+...+k = k(k+1)/2\n";
    cout << "  Prove for n=k+1:\n";
    cout << "    1+2+...+k+(k+1) = k(k+1)/2 + (k+1)\n";
    cout << "                     = (k(k+1) + 2(k+1))/2\n";
    cout << "                     = (k+1)(k+2)/2\n";
    cout << "                     = (k+1)((k+1)+1)/2\n";
    cout << "  Inductive step holds!\n\n";

    cout << "Verification for n=" << n << ":\n";
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    int formula = n * (n + 1) / 2;
    cout << "  Sum: " << sum << "\n";
    cout << "  Formula: " << formula << "\n";
    cout << "  Match: " << (sum == formula ? "YES" : "NO") << "\n";
}

void InductionVerifier::proveByStrongInduction(int n) const {
    cout << "\n=== Strong Induction Proof ===\n";
    cout << "Proving: Every integer n >= 2 can be expressed as a product of primes\n\n";

    cout << "Base Case (n=2):\n";
    cout << "  2 is prime itself\n";
    cout << "  Base case holds!\n\n";

    cout << "Strong Inductive Step:\n";
    cout << "  Assume true for all 2 <= k < n\n";
    cout << "  Prove for n:\n";
    cout << "    Case 1: If n is prime, done.\n";
    cout << "    Case 2: If n is composite, n = a*b where 2 <= a,b < n\n";
    cout << "            By hypothesis, a and b are products of primes\n";
    cout << "            Therefore n is also a product of primes\n\n";

    cout << "Prime factorization of " << n << ": ";
    int temp = n;
    for (int i = 2; i <= temp; i++) {
        while (temp % i == 0) {
            cout << i;
            temp /= i;
            if (temp > 1) cout << " * ";
        }
    }
    cout << "\n";
}