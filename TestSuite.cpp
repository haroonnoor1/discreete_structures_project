//#include <iostream>
//#include <cassert>
//#include <vector>
//#include <string>
//#include "CourseGraph.h"
//#include "StudentCombination.h"
//#include "InductionVerifier.h"
//#include "LogicEngine.h"
//#include "SetOperations.h"
//#include "Relations.h"
//#include "Functions.h"
//#include "ConsistencyChecker.h"
//
//using namespace std;
//
//int testsPassed = 0;
//int testsFailed = 0;
//
//void reportTest(const string& testName, bool passed) {
//    if (passed) {
//        cout << "✓ " << testName << " PASSED\n";
//        testsPassed++;
//    }
//    else {
//        cout << "✗ " << testName << " FAILED\n";
//        testsFailed++;
//    }
//}
//
//// Module 1 Tests
//void testCourseGraph() {
//    cout << "\n=== Testing Module 1: Course Graph ===\n";
//
//    CourseGraph g;
//    g.addCourse("CS101");
//    g.addCourse("CS102");
//    g.addCourse("CS201");
//
//    reportTest("Add courses", g.getCourseCount() == 3);
//
//    g.addPrereq("CS101", "CS201");
//    reportTest("Cycle detection (no cycle)", !g.hasCycle());
//
//    g.addPrereq("CS201", "CS101");
//    reportTest("Cycle detection (has cycle)", g.hasCycle());
//
//    CourseGraph g2;
//    g2.addCourse("A");
//    g2.addCourse("B");
//    g2.addCourse("C");
//    g2.addPrereq("A", "B");
//    g2.addPrereq("B", "C");
//
//    unsigned long long count = g2.countSequences();
//    reportTest("Count sequences", count == 1); // Only one valid ordering: A->B->C
//}
//
//// Module 2 Tests
//void testStudentCombination() {
//    cout << "\n=== Testing Module 2: Student Combinations ===\n";
//
//    StudentCombination sc;
//    sc.addStudent("Alice");
//    sc.addStudent("Bob");
//    sc.addStudent("Charlie");
//    sc.addStudent("David");
//
//    reportTest("Add students", sc.getStudentCount() == 4);
//
//    unsigned long long c42 = sc.countCombinations(2);
//    reportTest("C(4,2) = 6", c42 == 6);
//
//    unsigned long long c43 = sc.countCombinations(3);
//    reportTest("C(4,3) = 4", c43 == 4);
//
//    unsigned long long c44 = sc.countCombinations(4);
//    reportTest("C(4,4) = 1", c44 == 1);
//
//    vector<vector<string>> groups;
//    sc.generateGroups(2, groups, 10);
//    reportTest("Generate C(4,2) groups", groups.size() == 6);
//}
//
//// Module 3 Tests
//void testInductionVerifier() {
//    cout << "\n=== Testing Module 3: Induction Verifier ===\n";
//
//    InductionVerifier iv;
//    iv.addPrerequisite("CS201", "CS101");
//    iv.addPrerequisite("CS301", "CS201");
//
//    vector<string> completed = { "CS101", "CS201" };
//    vector<string> missing;
//
//    bool canTake = iv.canTakeCourse("CS301", completed, missing);
//    reportTest("Can take course with prerequisites", canTake);
//
//    vector<string> incomplete = { "CS101" };
//    missing.clear();
//    bool cannotTake = iv.canTakeCourse("CS301", incomplete, missing);
//    reportTest("Cannot take course without prerequisites", !cannotTake);
//}
//
//// Module 4 Tests
//void testLogicEngine() {
//    cout << "\n=== Testing Module 4: Logic Engine ===\n";
//
//    LogicEngine le;
//    le.addFact("ProfX_teaches_CS101", true);
//    le.addRule("ProfX_teaches_CS101", "Lab_must_be_LabA", IMPLIES);
//
//    reportTest("Query known fact", le.query("ProfX_teaches_CS101"));
//    reportTest("Inference works", le.query("Lab_must_be_LabA"));
//}
//
//// Module 5 Tests
//void testSetOperations() {
//    cout << "\n=== Testing Module 5: Set Operations ===\n";
//
//    SetOperations<string> setA;
//    setA.addElement("a");
//    setA.addElement("b");
//    setA.addElement("c");
//
//    reportTest("Add elements to set", setA.cardinality() == 3);
//    reportTest("Set contains element", setA.contains("b"));
//    reportTest("Set doesn't contain element", !setA.contains("d"));
//
//    SetOperations<string> setB;
//    setB.addElement("b");
//    setB.addElement("c");
//    setB.addElement("d");
//
//    SetOperations<string> unionSet = setA.unionWith(setB);
//    reportTest("Union size", unionSet.cardinality() == 4);
//
//    SetOperations<string> intersectionSet = setA.intersectionWith(setB);
//    reportTest("Intersection size", intersectionSet.cardinality() == 2);
//
//    SetOperations<string> differenceSet = setA.differenceWith(setB);
//    reportTest("Difference size", differenceSet.cardinality() == 1);
//
//    SetOperations<string> smallSet;
//    smallSet.addElement("x");
//    smallSet.addElement("y");
//    vector<vector<string>> ps = smallSet.powerSet();
//    reportTest("Power set size 2^n", ps.size() == 4); // {}, {x}, {y}, {x,y}
//}
//
//// Module 6 Tests
//void testRelations() {
//    cout << "\n=== Testing Module 6: Relations ===\n";
//
//    Relations<string> rel;
//    rel.addPair("a", "a");
//    rel.addPair("b", "b");
//    rel.addPair("c", "c");
//
//    reportTest("Reflexive relation", rel.isReflexive());
//
//    Relations<string> symRel;
//    symRel.addPair("a", "b");
//    symRel.addPair("b", "a");
//    symRel.addPair("a", "a");
//    symRel.addPair("b", "b");
//
//    reportTest("Symmetric relation", symRel.isSymmetric());
//
//    Relations<string> transRel;
//    transRel.addPair("a", "b");
//    transRel.addPair("b", "c");
//    transRel.addPair("a", "c");
//    transRel.addPair("a", "a");
//    transRel.addPair("b", "b");
//    transRel.addPair("c", "c");
//
//    reportTest("Transitive relation", transRel.isTransitive());
//}
//
//// Module 7 Tests
//void testFunctions() {
//    cout << "\n=== Testing Module 7: Functions ===\n";
//
//    Functions<string, string> func;
//    func.addMapping("student1", "CS101");
//    func.addMapping("student2", "CS102");
//    func.addMapping("student3", "CS103");
//
//    reportTest("Function is valid", func.isFunction());
//    reportTest("Function is injective", func.isInjective());
//
//    Functions<string, string> notInjective;
//    notInjective.addMapping("s1", "CS101");
//    notInjective.addMapping("s2", "CS101");
//
//    reportTest("Detect non-injective", !notInjective.isInjective());
//
//    try {
//        string result = func.apply("student1");
//        reportTest("Apply function", result == "CS101");
//    }
//    catch (...) {
//        reportTest("Apply function", false);
//    }
//}
//
//// Module 9 Tests
//void testConsistencyChecker() {
//    cout << "\n=== Testing Module 9: Consistency Checker ===\n";
//
//    ConsistencyChecker cc;
//    cc.addEnrollment("S1", "CS101", "MWF9");
//    cc.addEnrollment("S1", "CS102", "MWF10");
//    cc.addEnrollment("S2", "CS101", "MWF9");
//
//    cc.addAssignment("Prof1", "CS101", "Room101");
//    cc.addAssignment("Prof2", "CS102", "Room102");
//
//    cc.addPrerequisite("CS201", "CS101");
//    cc.addCourseCredit("CS101", 3);
//    cc.addCourseCredit("CS102", 3);
//
//    bool noTimeConflicts = cc.checkTimeConflicts();
//    reportTest("No time conflicts", noTimeConflicts);
//
//    ConsistencyChecker cc2;
//    cc2.addEnrollment("S1", "CS101", "MWF9");
//    cc2.addEnrollment("S1", "CS102", "MWF9"); // Conflict!
//
//    bool hasConflict = !cc2.checkTimeConflicts();
//    reportTest("Detect time conflict", hasConflict);
//}
//
//// Stress Tests
//void stressTestCourseGraph() {
//    cout << "\n=== Stress Testing Module 1 ===\n";
//
//    CourseGraph g;
//    for (int i = 0; i < 50; i++) {
//        g.addCourse("Course" + to_string(i));
//    }
//
//    for (int i = 0; i < 40; i++) {
//        g.addPrereq("Course" + to_string(i), "Course" + to_string(i + 1));
//    }
//
//    reportTest("Large course graph (50 courses)", g.getCourseCount() == 50);
//    reportTest("Large graph has no cycle", !g.hasCycle());
//}
//
//void stressTestCombinations() {
//    cout << "\n=== Stress Testing Module 2 ===\n";
//
//    StudentCombination sc;
//    for (int i = 0; i < 20; i++) {
//        sc.addStudent("Student" + to_string(i));
//    }
//
//    unsigned long long c10 = sc.countCombinations(10);
//    reportTest("C(20,10) computation", c10 == 184756);
//}
//
//int main() {
//    cout << "╔════════════════════════════════════════════════════════════╗\n";
//    cout << "║              UNIDISC ENGINE TEST SUITE                     ║\n";
//    cout << "╚════════════════════════════════════════════════════════════╝\n";
//
//    testCourseGraph();
//    testStudentCombination();
//    testInductionVerifier();
//    testLogicEngine();
//    testSetOperations();
//    testRelations();
//    testFunctions();
//    testConsistencyChecker();
//
//    cout << "\n=== STRESS TESTS ===\n";
//    stressTestCourseGraph();
//    stressTestCombinations();
//
//    cout << "\n╔════════════════════════════════════════════════════════════╗\n";
//    cout << "║                    TEST SUMMARY                            ║\n";
//    cout << "╚════════════════════════════════════════════════════════════╝\n";
//    cout << "Tests Passed: " << testsPassed << "\n";
//    cout << "Tests Failed: " << testsFailed << "\n";
//    cout << "Total Tests:  " << (testsPassed + testsFailed) << "\n";
//
//    if (testsFailed == 0) {
//        cout << "\n✓ ALL TESTS PASSED!\n";
//        return 0;
//    }
//    else {
//        cout << "\n✗ SOME TESTS FAILED\n";
//        return 1;
//    }
//}