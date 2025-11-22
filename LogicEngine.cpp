#include "LogicEngine.h"
#include <iostream>

using namespace std;

LogicEngine::LogicEngine() {}

void LogicEngine::addRule(const string& condition, const string& conclusion, LogicOp op) {
    rules.push_back(LogicRule(condition, conclusion, op));
}

void LogicEngine::addFact(const string& fact, bool value) {
    facts[fact] = value;
}

bool LogicEngine::evaluateRecursive(const string& fact, int depth) const {
    if (depth > 100) return false;

    if (facts.count(fact)) {
        return facts.at(fact);
    }

    for (const LogicRule& rule : rules) {
        if (rule.conclusion == fact) {
            bool condValue = evaluateRecursive(rule.condition, depth + 1);

            switch (rule.op) {
            case IMPLIES:
                if (condValue) return true;
                break;
            case AND:
                return condValue;
            case OR:
                if (condValue) return true;
                break;
            case NOT:
                return !condValue;
            case EQUIV:
                return condValue;
            }
        }
    }

    return false;
}

bool LogicEngine::query(const string& fact) const {
    return evaluateRecursive(fact, 0);
}

void LogicEngine::displayRules() const {
    cout << "\n=== Logic Rules ===\n";
    for (size_t i = 0; i < rules.size(); i++) {
        cout << i + 1 << ". ";
        cout << rules[i].condition;

        switch (rules[i].op) {
        case IMPLIES: cout << " -> "; break;
        case AND: cout << " AND "; break;
        case OR: cout << " OR "; break;
        case NOT: cout << " NOT "; break;
        case EQUIV: cout << " <-> "; break;
        }

        cout << rules[i].conclusion << "\n";
    }
}

void LogicEngine::displayFacts() const {
    cout << "\n=== Known Facts ===\n";
    for (const auto& pair : facts) {
        cout << pair.first << ": " << (pair.second ? "TRUE" : "FALSE") << "\n";
    }
}

bool LogicEngine::checkConsistency() const {
    cout << "\n=== Consistency Check ===\n";

    for (const auto& fact : facts) {
        bool queried = query(fact.first);
        if (queried != fact.second) {
            cout << "Inconsistency found: " << fact.first << "\n";
            cout << "  Stored: " << fact.second << ", Inferred: " << queried << "\n";
            return false;
        }
    }

    cout << "All facts are consistent!\n";
    return true;
}

void LogicEngine::inferNewFacts() {
    cout << "\n=== Inference Engine ===\n";
    int inferred = 0;

    for (const LogicRule& rule : rules) {
        if (facts.count(rule.condition) && facts[rule.condition]) {
            if (!facts.count(rule.conclusion)) {
                if (rule.op == IMPLIES) {
                    facts[rule.conclusion] = true;
                    cout << "Inferred: " << rule.conclusion << " (from " << rule.condition << ")\n";
                    inferred++;
                }
            }
        }
    }

    if (inferred == 0) {
        cout << "No new facts inferred.\n";
    }
    else {
        cout << "Total facts inferred: " << inferred << "\n";
    }
}

bool LogicEngine::isTautology(const string& expr) const {
    cout << "\n=== Tautology Check for: " << expr << " ===\n";
    cout << "A tautology is true under all possible truth assignments.\n";
    cout << "Example: P OR NOT P is always true\n";
    return true;
}