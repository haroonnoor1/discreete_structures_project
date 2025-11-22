#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <string>
#include <vector>
#include <map>

enum LogicOp { AND, OR, IMPLIES, NOT, EQUIV };

class LogicRule {
public:
    std::string condition;
    std::string conclusion;
    LogicOp op;

    LogicRule(const std::string& cond, const std::string& concl, LogicOp operation)
        : condition(cond), conclusion(concl), op(operation) {}
};

class LogicEngine {
private:
    std::vector<LogicRule> rules;
    std::map<std::string, bool> facts;

    bool evaluateRecursive(const std::string& fact, int depth) const;
    bool checkTautologyRecursive(int index, std::map<std::string, bool>& assignment,
        const std::vector<std::string>& vars) const;

public:
    LogicEngine();
    void addRule(const std::string& condition, const std::string& conclusion, LogicOp op);
    void addFact(const std::string& fact, bool value);
    bool query(const std::string& fact) const;
    void displayRules() const;
    void displayFacts() const;
    bool checkConsistency() const;
    void inferNewFacts();
    bool isTautology(const std::string& expr) const;
};

#endif#pragma once
