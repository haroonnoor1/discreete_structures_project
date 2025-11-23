#ifndef INDUCTIONVERIFIER_H
#define INDUCTIONVERIFIER_H

#include <vector>
#include <string>
#include <unordered_map>

class InductionVerifier {
private:
    std::unordered_map<std::string, std::vector<std::string>> prereqMap;

    bool verifyChainRecursive(const std::string& current, const std::string& target,
        std::vector<std::string>& chain, int depth) const;
    bool canTakeCourseRecursive(const std::string& course,
        const std::vector<std::string>& completed,
        std::vector<std::string>& missing, int depth) const;

public:
    InductionVerifier();
    void addPrerequisite(const std::string& course, const std::string& prereq);
    bool verifyPrerequisiteChain(const std::string& course, std::vector<std::string>& chain) const;
    bool canTakeCourse(const std::string& course, const std::vector<std::string>& completed,
        std::vector<std::string>& missing) const;
    void displayPrerequisites() const;
    void proveByInduction(int n) const;
    void proveByStrongInduction(int n) const;
};

#endif#pragma once
