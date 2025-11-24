#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <vector>
#include <string>
#include <algorithm>

template <typename T>
class SetOperations {
private:
    std::vector<T> elements;

    void generatePowerSetRecursive(int index, std::vector<T>& current,
        std::vector<std::vector<T>>& result) const;

public:
    SetOperations();
    void addElement(const T& elem);
    void removeElement(const T& elem);
    bool contains(const T& elem) const;
    void display() const;

    SetOperations<T> unionWith(const SetOperations<T>& other) const;
    SetOperations<T> intersectionWith(const SetOperations<T>& other) const;
    SetOperations<T> differenceWith(const SetOperations<T>& other) const;
    SetOperations<T> symmetricDifference(const SetOperations<T>& other) const;

    bool isSubsetOf(const SetOperations<T>& other) const;
    bool isSupersetOf(const SetOperations<T>& other) const;
    bool isProperSubsetOf(const SetOperations<T>& other) const;

    std::vector<std::vector<T>> powerSet() const;
    int cardinality() const { return elements.size(); }
    bool isEmpty() const { return elements.empty(); }
    void clear() { elements.clear(); }

    std::vector<T> getElements() const { return elements; }
};

// Template implementation must be in header
template <typename T>
SetOperations<T>::SetOperations() {}

template <typename T>
void SetOperations<T>::addElement(const T& elem) {
    if (!contains(elem)) {
        elements.push_back(elem);
    }
}

template <typename T>
void SetOperations<T>::removeElement(const T& elem) {
    elements.erase(std::remove(elements.begin(), elements.end(), elem), elements.end());
}

template <typename T>
bool SetOperations<T>::contains(const T& elem) const {
    return std::find(elements.begin(), elements.end(), elem) != elements.end();
}

template <typename T>
void SetOperations<T>::display() const {
    std::cout << "{ ";
    for (size_t i = 0; i < elements.size(); i++) {
        std::cout << elements[i];
        if (i + 1 < elements.size()) std::cout << ", ";
    }
    std::cout << " }\n";
}

template <typename T>
SetOperations<T> SetOperations<T>::unionWith(const SetOperations<T>& other) const {
    SetOperations<T> result;
    for (const T& elem : elements) result.addElement(elem);
    for (const T& elem : other.elements) result.addElement(elem);
    return result;
}

template <typename T>
SetOperations<T> SetOperations<T>::intersectionWith(const SetOperations<T>& other) const {
    SetOperations<T> result;
    for (const T& elem : elements) {
        if (other.contains(elem)) result.addElement(elem);
    }
    return result;
}

template <typename T>
SetOperations<T> SetOperations<T>::differenceWith(const SetOperations<T>& other) const {
    SetOperations<T> result;
    for (const T& elem : elements) {
        if (!other.contains(elem)) result.addElement(elem);
    }
    return result;
}

template <typename T>
SetOperations<T> SetOperations<T>::symmetricDifference(const SetOperations<T>& other) const {
    SetOperations<T> result;
    result = unionWith(other).differenceWith(intersectionWith(other));
    return result;
}

template <typename T>
bool SetOperations<T>::isSubsetOf(const SetOperations<T>& other) const {
    for (const T& elem : elements) {
        if (!other.contains(elem)) return false;
    }
    return true;
}

template <typename T>
bool SetOperations<T>::isSupersetOf(const SetOperations<T>& other) const {
    return other.isSubsetOf(*this);
}

template <typename T>
bool SetOperations<T>::isProperSubsetOf(const SetOperations<T>& other) const {
    return isSubsetOf(other) && cardinality() < other.cardinality();
}

template <typename T>
void SetOperations<T>::generatePowerSetRecursive(int index, std::vector<T>& current,
    std::vector<std::vector<T>>& result) const {
    result.push_back(current);

    for (int i = index; i < (int)elements.size(); i++) {
        current.push_back(elements[i]);
        generatePowerSetRecursive(i + 1, current, result);
        current.pop_back();
    }
}

template <typename T>
std::vector<std::vector<T>> SetOperations<T>::powerSet() const {
    std::vector<std::vector<T>> result;
    std::vector<T> current;
    generatePowerSetRecursive(0, current, result);
    return result;
}

#endif