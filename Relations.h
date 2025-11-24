#ifndef RELATIONS_H
#define RELATIONS_H

#include <vector>
#include <string>
#include <utility>

template <typename T>
class Relations {
private:
    std::vector<std::pair<T, T>> pairs;
    std::vector<T> domain;
    std::vector<T> codomain;

    bool isInDomain(const T& elem) const;
    bool isInCodomain(const T& elem) const;
    void addToDomain(const T& elem);
    void addToCodomain(const T& elem);

public:
    Relations();
    void addPair(const T& from, const T& to);
    void display() const;

    bool isReflexive() const;
    bool isSymmetric() const;
    bool isAntisymmetric() const;
    bool isTransitive() const;
    bool isEquivalenceRelation() const;
    bool isPartialOrder() const;

    Relations<T> compose(const Relations<T>& other) const;
    Relations<T> transitiveClosure() const;

    std::vector<std::vector<T>> equivalenceClasses() const;
    void displayProperties() const;
};

// Template implementations
template <typename T>
Relations<T>::Relations() {}

template <typename T>
bool Relations<T>::isInDomain(const T& elem) const {
    for (const T& d : domain) {
        if (d == elem) return true;
    }
    return false;
}

template <typename T>
bool Relations<T>::isInCodomain(const T& elem) const {
    for (const T& c : codomain) {
        if (c == elem) return true;
    }
    return false;
}

template <typename T>
void Relations<T>::addToDomain(const T& elem) {
    if (!isInDomain(elem)) domain.push_back(elem);
}

template <typename T>
void Relations<T>::addToCodomain(const T& elem) {
    if (!isInCodomain(elem)) codomain.push_back(elem);
}

template <typename T>
void Relations<T>::addPair(const T& from, const T& to) {
    pairs.push_back(std::make_pair(from, to));
    addToDomain(from);
    addToCodomain(to);
}

template <typename T>
void Relations<T>::display() const {
    std::cout << "Relation: { ";
    for (size_t i = 0; i < pairs.size(); i++) {
        std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ")";
        if (i + 1 < pairs.size()) std::cout << ", ";
    }
    std::cout << " }\n";
}

template <typename T>
bool Relations<T>::isReflexive() const {
    for (const T& elem : domain) {
        bool found = false;
        for (const auto& p : pairs) {
            if (p.first == elem && p.second == elem) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

template <typename T>
bool Relations<T>::isSymmetric() const {
    for (const auto& p : pairs) {
        bool found = false;
        for (const auto& q : pairs) {
            if (q.first == p.second && q.second == p.first) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

template <typename T>
bool Relations<T>::isAntisymmetric() const {
    for (const auto& p : pairs) {
        if (p.first != p.second) {
            for (const auto& q : pairs) {
                if (q.first == p.second && q.second == p.first) {
                    return false;
                }
            }
        }
    }
    return true;
}

template <typename T>
bool Relations<T>::isTransitive() const {
    for (const auto& p1 : pairs) {
        for (const auto& p2 : pairs) {
            if (p1.second == p2.first) {
                bool found = false;
                for (const auto& p3 : pairs) {
                    if (p3.first == p1.first && p3.second == p2.second) {
                        found = true;
                        break;
                    }
                }
                if (!found) return false;
            }
        }
    }
    return true;
}

template <typename T>
bool Relations<T>::isEquivalenceRelation() const {
    return isReflexive() && isSymmetric() && isTransitive();
}

template <typename T>
bool Relations<T>::isPartialOrder() const {
    return isReflexive() && isAntisymmetric() && isTransitive();
}

template <typename T>
Relations<T> Relations<T>::compose(const Relations<T>& other) const {
    Relations<T> result;
    for (const auto& p1 : pairs) {
        for (const auto& p2 : other.pairs) {
            if (p1.second == p2.first) {
                result.addPair(p1.first, p2.second);
            }
        }
    }
    return result;
}

template <typename T>
Relations<T> Relations<T>::transitiveClosure() const {
    Relations<T> result = *this;
    bool changed = true;

    while (changed) {
        changed = false;
        Relations<T> newPairs = result;

        for (const auto& p1 : result.pairs) {
            for (const auto& p2 : result.pairs) {
                if (p1.second == p2.first) {
                    bool found = false;
                    for (const auto& p3 : newPairs.pairs) {
                        if (p3.first == p1.first && p3.second == p2.second) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        newPairs.addPair(p1.first, p2.second);
                        changed = true;
                    }
                }
            }
        }
        result = newPairs;
    }

    return result;
}

template <typename T>
std::vector<std::vector<T>> Relations<T>::equivalenceClasses() const {
    std::vector<std::vector<T>> classes;
    std::vector<T> processed;

    for (const T& elem : domain) {
        bool alreadyProcessed = false;
        for (const T& p : processed) {
            if (p == elem) {
                alreadyProcessed = true;
                break;
            }
        }

        if (!alreadyProcessed) {
            std::vector<T> eqClass;
            eqClass.push_back(elem);
            processed.push_back(elem);

            for (const auto& pair : pairs) {
                if (pair.first == elem && pair.second != elem) {
                    bool found = false;
                    for (const T& p : processed) {
                        if (p == pair.second) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        eqClass.push_back(pair.second);
                        processed.push_back(pair.second);
                    }
                }
            }

            classes.push_back(eqClass);
        }
    }

    return classes;
}

template <typename T>
void Relations<T>::displayProperties() const {
    std::cout << "\n=== Relation Properties ===\n";
    std::cout << "Reflexive: " << (isReflexive() ? "YES" : "NO") << "\n";
    std::cout << "Symmetric: " << (isSymmetric() ? "YES" : "NO") << "\n";
    std::cout << "Antisymmetric: " << (isAntisymmetric() ? "YES" : "NO") << "\n";
    std::cout << "Transitive: " << (isTransitive() ? "YES" : "NO") << "\n";
    std::cout << "Equivalence Relation: " << (isEquivalenceRelation() ? "YES" : "NO") << "\n";
    std::cout << "Partial Order: " << (isPartialOrder() ? "YES" : "NO") << "\n";
}

#endif#pragma once
