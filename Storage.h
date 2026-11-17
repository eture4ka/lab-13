#ifndef STORAGE_H
#define STORAGE_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "TypeName.h"

// ============================================================================
// ЗАГАЛЬНИЙ ШАБЛОН: сховище значень будь-якого типу T.
// Вимоги до T: оператор < (для max) та оператор << (для print).
// ============================================================================
template <typename T>
class Storage {
private:
    std::vector<T> items;

public:
    Storage() {
        std::cout << "  [Storage<" << TypeName<T>::get() << ">] -> загальний шаблон\n";
    }

    void add(const T& value) { items.push_back(value); }

    std::size_t size() const { return items.size(); }

    const T& get(std::size_t index) const {
        if (index >= items.size())
            throw std::out_of_range("індекс " + std::to_string(index) + " поза межами (розмір "
                                    + std::to_string(items.size()) + ")");
        return items[index];
    }

    const T& max() const {
        if (items.empty()) throw std::logic_error("сховище порожнє");
        const T* best = &items[0];
        for (const T& v : items)
            if (*best < v) best = &v;
        return *best;
    }

    void print(const std::string& title) const {
        std::cout << "  " << title << ": ";
        for (std::size_t i = 0; i < items.size(); ++i)
            std::cout << (i ? ", " : "") << items[i];
        std::cout << '\n';
    }
};

// ============================================================================
// ЧАСТКОВА СПЕЦІАЛІЗАЦІЯ: сховище вказівників T* для будь-якого T.
// Особлива поведінка:
//   - не зберігає nullptr (попереджає користувача);
//   - порівнює та виводить ЗНАЧЕННЯ, на які вказують, а не адреси;
//   - не володіє об'єктами (не видаляє їх), лише посилається на них.
// ============================================================================
template <typename T>
class Storage<T*> {
private:
    std::vector<T*> items;

public:
    Storage() {
        std::cout << "  [Storage<" << TypeName<T*>::get()
                  << ">] -> часткова спеціалізація для вказівників\n";
    }

    bool add(T* ptr) {
        if (ptr == nullptr) {
            std::cout << "    ! Попередження: nullptr не додано до сховища\n";
            return false;
        }
        items.push_back(ptr);
        return true;
    }

    std::size_t size() const { return items.size(); }

    const T& get(std::size_t index) const {
        if (index >= items.size())
            throw std::out_of_range("індекс " + std::to_string(index) + " поза межами (розмір "
                                    + std::to_string(items.size()) + ")");
        return *items[index];
    }

    const T& max() const {
        if (items.empty()) throw std::logic_error("сховище порожнє");
        T* best = items[0];
        for (T* p : items)
            if (*best < *p) best = p;    // порівнюємо значення, а не адреси
        return *best;
    }

    void print(const std::string& title) const {
        std::cout << "  " << title << ":\n";
        for (std::size_t i = 0; i < items.size(); ++i)
            std::cout << "    " << i + 1 << ". [" << static_cast<const void*>(items[i]) << "] -> "
                      << *items[i] << '\n';
    }
};

#endif
