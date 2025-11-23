#include <iostream>
#include <string>
#include <limits>
#include "CourseGraph.h"
#include "StudentCombination.h"
#include "InductionVerifier.h"
#include "LogicEngine.h"
#include "SetOperations.h"
#include "Relations.h"
#include "Functions.h"
#include "ProofVerifier.h"
#include "ConsistencyChecker.h"
#include "Benchmark.h"

using namespace std;

// Global instances
CourseGraph courseGraph;
StudentCombination studentCombo;
InductionVerifier inductionVerifier;
LogicEngine logicEngine;
SetOperations<string> setOps;
Relations<string> relations;
Functions<string, string> functions;
ProofVerifier proofVerifier;
ConsistencyChecker consistencyChecker;
Benchmark benchmark;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displayHeader() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║                    UNIDISC ENGINE                          ║\n";
    cout << "║        FAST University Discrete Structures System          ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";
}

void module1Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 1: Course & Scheduling ===\n";
        cout << "1. Add course\n";
        cout << "2. Add prerequisite\n";
        cout << "3. Display courses and prerequisites\n";
        cout << "4. Check for cycles\n";
        cout << "5. Count valid sequences\n";
        cout << "6. Generate valid sequences\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string name;
            cout << "Enter course name: ";
            getline(cin, name);
            courseGraph.addCourse(name);
            cout << "Course added!\n";
            pause();
            break;
        }
        case 2: {
            string pre, course;
            cout << "Enter prerequisite: ";
            getline(cin, pre);
            cout << "Enter course: ";
            getline(cin, course);
            courseGraph.addPrereq(pre, course);
            cout << "Prerequisite added!\n";
            pause();
            break;
        }
        case 3:
            courseGraph.displayCourses();
            courseGraph.displayPrerequisites();
            pause();
            break;
        case 4:
            if (courseGraph.hasCycle()) {
                cout << "\n✗ Cycle detected! Cannot generate schedules.\n";
            }
            else {
                cout << "\n✓ No cycles detected.\n";
            }
            pause();
            break;
        case 5: {
            unsigned long long count = courseGraph.countSequences();
            cout << "\nTotal valid sequences: " << count << "\n";
            pause();
            break;
        }
        case 6: {
            unsigned long long limit;
            cout << "Enter max sequences to generate: ";
            cin >> limit;

            vector<vector<int>> sequences;
            courseGraph.enumerateSequences(sequences, limit);

            cout << "\nGenerated " << sequences.size() << " sequences:\n";
            for (size_t i = 0; i < sequences.size(); i++) {
                vector<string> names = courseGraph.toNames(sequences[i]);
                cout << i + 1 << ") ";
                for (size_t j = 0; j < names.size(); j++) {
                    cout << names[j];
                    if (j + 1 < names.size()) cout << " -> ";
                }
                cout << "\n";
            }
            pause();
            break;
        }
        }
    }
}

void module2Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 2: Student Group Combinations ===\n";
        cout << "1. Add student\n";
        cout << "2. Display students\n";
        cout << "3. Count group combinations\n";
        cout << "4. Generate groups\n";
        cout << "5. Assign to lab sessions\n";
        cout << "6. Clear all students\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string name;
            cout << "Enter student name: ";
            getline(cin, name);
            studentCombo.addStudent(name);
            cout << "Student added!\n";
            pause();
            break;
        }
        case 2:
            studentCombo.displayStudents();
            pause();
            break;
        case 3: {
            int size;
            cout << "Enter group size: ";
            cin >> size;
            unsigned long long count = studentCombo.countCombinations(size);
            cout << "Total combinations C(" << studentCombo.getStudentCount()
                << "," << size << ") = " << count << "\n";
            pause();
            break;
        }
        case 4: {
            int size;
            cout << "Enter group size: ";
            cin >> size;

            vector<vector<string>> groups;
            studentCombo.generateGroups(size, groups, 50);

            cout << "\nGenerated " << groups.size() << " groups:\n";
            for (size_t i = 0; i < groups.size(); i++) {
                cout << "Group " << i + 1 << ": ";
                for (size_t j = 0; j < groups[i].size(); j++) {
                    cout << groups[i][j];
                    if (j + 1 < groups[i].size()) cout << ", ";
                }
                cout << "\n";
            }
            pause();
            break;
        }
        case 5: {
            int sessionSize, numSessions;
            cout << "Students per session: ";
            cin >> sessionSize;
            cout << "Number of sessions: ";
            cin >> numSessions;
            studentCombo.assignToSessions(sessionSize, numSessions);
            pause();
            break;
        }
        case 6:
            studentCombo.clearStudents();
            cout << "All students cleared!\n";
            pause();
            break;
        }
    }
}

void module3Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 3: Induction & Strong Induction ===\n";
        cout << "1. Add prerequisite chain\n";
        cout << "2. Verify prerequisite chain\n";
        cout << "3. Check if student can take course\n";
        cout << "4. Display prerequisites\n";
        cout << "5. Demonstrate mathematical induction\n";
        cout << "6. Demonstrate strong induction\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string course, prereq;
            cout << "Enter course: ";
            getline(cin, course);
            cout << "Enter prerequisite: ";
            getline(cin, prereq);
            inductionVerifier.addPrerequisite(course, prereq);
            cout << "Prerequisite added!\n";
            pause();
            break;
        }
        case 2: {
            string course;
            cout << "Enter course to verify: ";
            getline(cin, course);

            vector<string> chain;
            if (inductionVerifier.verifyPrerequisiteChain(course, chain)) {
                cout << "\nPrerequisite chain:\n";
                for (const string& c : chain) {
                    cout << c << "\n";
                }
            }
            else {
                cout << "\nNo prerequisite chain found.\n";
            }
            pause();
            break;
        }
        case 3: {
            string course;
            cout << "Enter course: ";
            getline(cin, course);

            int n;
            cout << "How many completed courses? ";
            cin >> n;
            cin.ignore();

            vector<string> completed;
            for (int i = 0; i < n; i++) {
                string c;
                cout << "Completed course " << (i + 1) << ": ";
                getline(cin, c);
                completed.push_back(c);
            }

            vector<string> missing;
            if (inductionVerifier.canTakeCourse(course, completed, missing)) {
                cout << "\n✓ Student can take " << course << "\n";
            }
            else {
                cout << "\n✗ Missing prerequisites: ";
                for (const string& m : missing) cout << m << " ";
                cout << "\n";
            }
            pause();
            break;
        }
        case 4:
            inductionVerifier.displayPrerequisites();
            pause();
            break;
        case 5: {
            int n;
            cout << "Enter value of n: ";
            cin >> n;
            inductionVerifier.proveByInduction(n);
            pause();
            break;
        }
        case 6: {
            int n;
            cout << "Enter value of n: ";
            cin >> n;
            inductionVerifier.proveByStrongInduction(n);
            pause();
            break;
        }
        }
    }
}

void module4Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 4: Logic & Inference Engine ===\n";
        cout << "1. Add logic rule (IMPLIES)\n";
        cout << "2. Add fact\n";
        cout << "3. Query fact\n";
        cout << "4. Display rules\n";
        cout << "5. Display facts\n";
        cout << "6. Infer new facts\n";
        cout << "7. Check consistency\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string cond, concl;
            cout << "Enter condition: ";
            getline(cin, cond);
            cout << "Enter conclusion: ";
            getline(cin, concl);
            logicEngine.addRule(cond, concl, IMPLIES);
            cout << "Rule added!\n";
            pause();
            break;
        }
        case 2: {
            string fact;
            char val;
            cout << "Enter fact: ";
            getline(cin, fact);
            cout << "True or False (T/F): ";
            cin >> val;
            logicEngine.addFact(fact, (val == 'T' || val == 't'));
            cout << "Fact added!\n";
            pause();
            break;
        }
        case 3: {
            string fact;
            cout << "Enter fact to query: ";
            getline(cin, fact);
            bool result = logicEngine.query(fact);
            cout << "\nResult: " << (result ? "TRUE" : "FALSE") << "\n";
            pause();
            break;
        }
        case 4:
            logicEngine.displayRules();
            pause();
            break;
        case 5:
            logicEngine.displayFacts();
            pause();
            break;
        case 6:
            logicEngine.inferNewFacts();
            pause();
            break;
        case 7:
            logicEngine.checkConsistency();
            pause();
            break;
        }
    }
}

void module5Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 5: Set Operations ===\n";
        cout << "1. Add element to set A\n";
        cout << "2. Display set A\n";
        cout << "3. Union with another set\n";
        cout << "4. Intersection with another set\n";
        cout << "5. Difference with another set\n";
        cout << "6. Generate power set\n";
        cout << "7. Check subset/superset\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string elem;
            cout << "Enter element: ";
            getline(cin, elem);
            setOps.addElement(elem);
            cout << "Element added!\n";
            pause();
            break;
        }
        case 2:
            cout << "\nSet A: ";
            setOps.display();
            pause();
            break;
        case 3: {
            SetOperations<string> setB;
            int n;
            cout << "How many elements in set B? ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; i++) {
                string elem;
                cout << "Element " << (i + 1) << ": ";
                getline(cin, elem);
                setB.addElement(elem);
            }

            SetOperations<string> result = setOps.unionWith(setB);
            cout << "\nA ∪ B: ";
            result.display();
            pause();
            break;
        }
        case 4: {
            SetOperations<string> setB;
            int n;
            cout << "How many elements in set B? ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; i++) {
                string elem;
                cout << "Element " << (i + 1) << ": ";
                getline(cin, elem);
                setB.addElement(elem);
            }

            SetOperations<string> result = setOps.intersectionWith(setB);
            cout << "\nA ∩ B: ";
            result.display();
            pause();
            break;
        }
        case 5: {
            SetOperations<string> setB;
            int n;
            cout << "How many elements in set B? ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; i++) {
                string elem;
                cout << "Element " << (i + 1) << ": ";
                getline(cin, elem);
                setB.addElement(elem);
            }

            SetOperations<string> result = setOps.differenceWith(setB);
            cout << "\nA - B: ";
            result.display();
            pause();
            break;
        }
        case 6: {
            vector<vector<string>> ps = setOps.powerSet();
            cout << "\nPower Set of A (size " << ps.size() << "):\n";
            for (size_t i = 0; i < ps.size() && i < 20; i++) {
                cout << "{ ";
                for (size_t j = 0; j < ps[i].size(); j++) {
                    cout << ps[i][j];
                    if (j + 1 < ps[i].size()) cout << ", ";
                }
                cout << " }\n";
            }
            if (ps.size() > 20) {
                cout << "... (showing first 20)\n";
            }
            pause();
            break;
        }
        case 7: {
            SetOperations<string> setB;
            int n;
            cout << "How many elements in set B? ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; i++) {
                string elem;
                cout << "Element " << (i + 1) << ": ";
                getline(cin, elem);
                setB.addElement(elem);
            }

            cout << "\nA ⊆ B: " << (setOps.isSubsetOf(setB) ? "YES" : "NO") << "\n";
            cout << "A ⊇ B: " << (setOps.isSupersetOf(setB) ? "YES" : "NO") << "\n";
            pause();
            break;
        }
        }
    }
}

void module6Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 6: Relations ===\n";
        cout << "1. Add pair to relation\n";
        cout << "2. Display relation\n";
        cout << "3. Check properties\n";
        cout << "4. Compute transitive closure\n";
        cout << "5. Find equivalence classes\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string from, to;
            cout << "Enter first element: ";
            getline(cin, from);
            cout << "Enter second element: ";
            getline(cin, to);
            relations.addPair(from, to);
            cout << "Pair added!\n";
            pause();
            break;
        }
        case 2:
            relations.display();
            pause();
            break;
        case 3:
            relations.displayProperties();
            pause();
            break;
        case 4: {
            Relations<string> closure = relations.transitiveClosure();
            cout << "\nTransitive Closure:\n";
            closure.display();
            pause();
            break;
        }
        case 5: {
            vector<vector<string>> classes = relations.equivalenceClasses();
            cout << "\nEquivalence Classes:\n";
            for (size_t i = 0; i < classes.size(); i++) {
                cout << "Class " << (i + 1) << ": { ";
                for (size_t j = 0; j < classes[i].size(); j++) {
                    cout << classes[i][j];
                    if (j + 1 < classes[i].size()) cout << ", ";
                }
                cout << " }\n";
            }
            pause();
            break;
        }
        }
    }
}

void module7Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 7: Functions ===\n";
        cout << "1. Add mapping\n";
        cout << "2. Display function\n";
        cout << "3. Check properties\n";
        cout << "4. Apply function\n";
        cout << "5. Compute inverse\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string input, output;
            cout << "Enter input (domain): ";
            getline(cin, input);
            cout << "Enter output (codomain): ";
            getline(cin, output);
            functions.addMapping(input, output);
            cout << "Mapping added!\n";
            pause();
            break;
        }
        case 2:
            functions.display();
            pause();
            break;
        case 3:
            functions.displayProperties();
            pause();
            break;
        case 4: {
            string input;
            cout << "Enter input: ";
            getline(cin, input);
            try {
                string result = functions.apply(input);
                cout << "\nf(" << input << ") = " << result << "\n";
            }
            catch (...) {
                cout << "\nError: Input not in domain\n";
            }
            pause();
            break;
        }
        case 5: {
            Functions<string, string> inv = functions.inverse();
            cout << "\nInverse function:\n";
            inv.display();
            pause();
            break;
        }
        }
    }
}

void module8Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 8: Automated Proof & Verification ===\n";
        cout << "1. Prove prerequisite chain\n";
        cout << "2. Prove set equality\n";
        cout << "3. Prove relation property\n";
        cout << "4. Prove function property\n";
        cout << "5. Prove by contradiction\n";
        cout << "6. Prove by induction\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            int n;
            cout << "How many courses in chain? ";
            cin >> n;
            cin.ignore();

            vector<string> chain;
            for (int i = 0; i < n; i++) {
                string c;
                cout << "Course " << (i + 1) << ": ";
                getline(cin, c);
                chain.push_back(c);
            }
            proofVerifier.provePrerequisiteChain(chain);
            pause();
            break;
        }
        case 2: {
            string a, b;
            cout << "Enter set A: ";
            getline(cin, a);
            cout << "Enter set B: ";
            getline(cin, b);
            proofVerifier.proveSetEquality(a, b);
            pause();
            break;
        }
        case 3: {
            string rel, prop;
            cout << "Enter relation name: ";
            getline(cin, rel);
            cout << "Enter property (reflexive/symmetric/transitive): ";
            getline(cin, prop);
            proofVerifier.proveRelationProperty(rel, prop);
            pause();
            break;
        }
        case 4: {
            string func, prop;
            cout << "Enter function name: ";
            getline(cin, func);
            cout << "Enter property (injective/surjective/bijective): ";
            getline(cin, prop);
            proofVerifier.proveFunctionProperty(func, prop);
            pause();
            break;
        }
        case 5: {
            string stmt;
            cout << "Enter statement: ";
            getline(cin, stmt);
            proofVerifier.proveByContradiction(stmt);
            pause();
            break;
        }
        case 6: {
            string stmt;
            int n;
            cout << "Enter statement: ";
            getline(cin, stmt);
            cout << "Verify up to n=: ";
            cin >> n;
            proofVerifier.proveByInduction(stmt, n);
            pause();
            break;
        }
        }
    }
}

void module9Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 9: Consistency Checker ===\n";
        cout << "1. Add student enrollment\n";
        cout << "2. Add faculty assignment\n";
        cout << "3. Add prerequisite\n";
        cout << "4. Add course credits\n";
        cout << "5. Display enrollments\n";
        cout << "6. Display assignments\n";
        cout << "7. Run all checks\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            string student, course, time;
            cout << "Student ID: ";
            getline(cin, student);
            cout << "Course ID: ";
            getline(cin, course);
            cout << "Time slot: ";
            getline(cin, time);
            consistencyChecker.addEnrollment(student, course, time);
            cout << "Enrollment added!\n";
            pause();
            break;
        }
        case 2: {
            string faculty, course, room;
            cout << "Faculty ID: ";
            getline(cin, faculty);
            cout << "Course ID: ";
            getline(cin, course);
            cout << "Room ID: ";
            getline(cin, room);
            consistencyChecker.addAssignment(faculty, course, room);
            cout << "Assignment added!\n";
            pause();
            break;
        }
        case 3: {
            string course, prereq;
            cout << "Course: ";
            getline(cin, course);
            cout << "Prerequisite: ";
            getline(cin, prereq);
            consistencyChecker.addPrerequisite(course, prereq);
            cout << "Prerequisite added!\n";
            pause();
            break;
        }
        case 4: {
            string course;
            int credits;
            cout << "Course: ";
            getline(cin, course);
            cout << "Credits: ";
            cin >> credits;
            consistencyChecker.addCourseCredit(course, credits);
            cout << "Credits added!\n";
            pause();
            break;
        }
        case 5:
            consistencyChecker.displayEnrollments();
            pause();
            break;
        case 6:
            consistencyChecker.displayAssignments();
            pause();
            break;
        case 7:
            consistencyChecker.checkAll();
            pause();
            break;
        }
    }
}

void module10Menu() {
    while (true) {
        clearScreen();
        cout << "\n=== MODULE 10: Algorithmic Efficiency & Benchmarking ===\n";
        cout << "1. Test recursive Fibonacci\n";
        cout << "2. Test memoized Fibonacci\n";
        cout << "3. Test factorial\n";
        cout << "4. Test combinations\n";
        cout << "5. Test power set\n";
        cout << "6. Display all results\n";
        cout << "7. Clear results\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            int n;
            cout << "Enter n (recommend < 40): ";
            cin >> n;
            benchmark.testRecursiveFibonacci(n);
            pause();
            break;
        }
        case 2: {
            int n;
            cout << "Enter n: ";
            cin >> n;
            benchmark.testMemoizedFibonacci(n);
            pause();
            break;
        }
        case 3: {
            int n;
            cout << "Enter n: ";
            cin >> n;
            benchmark.testFactorial(n);
            pause();
            break;
        }
        case 4: {
            int n, r;
            cout << "Enter n: ";
            cin >> n;
            cout << "Enter r: ";
            cin >> r;
            benchmark.testCombinations(n, r);
            pause();
            break;
        }
        case 5: {
            int n;
            cout << "Enter set size (recommend < 20): ";
            cin >> n;
            benchmark.testPowerSet(n);
            pause();
            break;
        }
        case 6:
            benchmark.displayResults();
            pause();
            break;
        case 7:
            benchmark.clearResults();
            cout << "Results cleared!\n";
            pause();
            break;
        }
    }
}

int main() {
    while (true) {
        clearScreen();
        displayHeader();

        cout << "\n=== MAIN MENU ===\n";
        cout << "1.  Course & Scheduling Module\n";
        cout << "2.  Student Group Combination Module\n";
        cout << "3.  Induction & Strong Induction Module\n";
        cout << "4.  Logic & Inference Engine\n";
        cout << "5.  Set Operations Module\n";
        cout << "6.  Relations Module\n";
        cout << "7.  Functions Module\n";
        cout << "8.  Automated Proof & Verification Module\n";
        cout << "9.  Consistency Checker Module\n";
        cout << "10. Algorithmic Efficiency & Benchmarking\n";
        cout << "0.  Exit\n";
        cout << "\nChoice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 0:
            cout << "\nThank you for using UNIDISC ENGINE!\n";
            return 0;
        case 1: module1Menu(); break;
        case 2: module2Menu(); break;
        case 3: module3Menu(); break;
        case 4: module4Menu(); break;
        case 5: module5Menu(); break;
        case 6: module6Menu(); break;
        case 7: module7Menu(); break;
        case 8: module8Menu(); break;
        case 9: module9Menu(); break;
        case 10: module10Menu(); break;
        default:
            cout << "Invalid choice!\n";
            pause();
        }
    }

    return 0;
}