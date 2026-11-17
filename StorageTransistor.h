#ifndef STORAGE_TRANSISTOR_H
#define STORAGE_TRANSISTOR_H

#include "Storage.h"
#include "Transistor.h"

// ============================================================================
// ПОВНА СПЕЦІАЛІЗАЦІЯ: Storage<Transistor>.
// Усі параметри шаблону задано (T = Transistor), тому це звичайний клас
// зі своїм набором методів, специфічних для транзисторів:
//   - додавання з перевіркою даних і забороною дублікатів за типом;
//   - виведення у вигляді таблиці;
//   - пошук за типом, сумарний струм, потужність при заданій напрузі.
// ============================================================================
template <>
class Storage<Transistor> {
private:
    std::vector<Transistor> items;

public:
    Storage();

    bool add(const Transistor& t);
    bool add(const std::string& type, double gain, double maxCurrent);

    std::size_t size() const;
    const Transistor& get(std::size_t index) const;
    const Transistor& max() const;                      // найбільше підсилення
    const Transistor* findByType(const std::string& type) const;
    double totalCurrent() const;

    void print(const std::string& title) const;
    void printPower(double voltage) const;
};

#endif
