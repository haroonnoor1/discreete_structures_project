#ifndef STUDENTCOMBINATION_H
#define STUDENTCOMBINATION_H

#include <vector>
#include <string>

class StudentCombination {
private:
    std::vector<std::string> students;

    void generateCombinationsRecursive(int start, int k, std::vector<int>& current,
        std::vector<std::vector<int>>& results) const;
    unsigned long long factorialRecursive(int n) const;
    unsigned long long nCrRecursive(int n, int r) const;

public:
    StudentCombination();
    void addStudent(const std::string& name);
    void displayStudents() const;
    unsigned long long countCombinations(int groupSize) const;
    void generateGroups(int groupSize, std::vector<std::vector<std::string>>& groups,
        unsigned long long limit = 1000) const;
    void assignToSessions(int sessionSize, int numSessions);
    int getStudentCount() const { return students.size(); }
    void clearStudents() { students.clear(); }
};

#endif#pragma once
