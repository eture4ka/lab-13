#include "StorageTransistor.h"
#include <iomanip>

using namespace std;

// Методи повної спеціалізації визначаються БЕЗ "template <>",
// бо Storage<Transistor> вже конкретний клас, а не шаблон.
// Тому їх, на відміну від шаблонів, можна винести в .cpp файл.

Storage<Transistor>::Storage() {
    cout << "  [Storage<Transistor>] -> повна спеціалізація для транзисторів\n";
}

bool Storage<Transistor>::add(const Transistor& t) {
    if (findByType(t.getType())) {
        cout << "    ! Попередження: транзистор \"" << t.getType() << "\" вже є, не додано\n";
        return false;
    }
    items.push_back(t);
    return true;
}

bool Storage<Transistor>::add(const string& type, double gain, double maxCurrent) {
    try {
        return add(Transistor(type, gain, maxCurrent));
    } catch (const invalid_argument& e) {
        cout << "    ! Попередження: \"" << type << "\" не додано: " << e.what() << '\n';
        return false;
    }
}

size_t Storage<Transistor>::size() const { return items.size(); }

const Transistor& Storage<Transistor>::get(size_t index) const {
    if (index >= items.size())
        throw out_of_range("індекс " + to_string(index) + " поза межами (розмір "
                           + to_string(items.size()) + ")");
    return items[index];
}

const Transistor& Storage<Transistor>::max() const {
    if (items.empty()) throw logic_error("сховище порожнє");
    const Transistor* best = &items[0];
    for (const Transistor& t : items)
        if (*best < t) best = &t;
    return *best;
}

const Transistor* Storage<Transistor>::findByType(const string& type) const {
    for (const Transistor& t : items)
        if (t.getType() == type) return &t;
    return nullptr;
}

double Storage<Transistor>::totalCurrent() const {
    double sum = 0;
    for (const Transistor& t : items) sum += t.getMaxCurrent();
    return sum;
}

void Storage<Transistor>::print(const string& title) const {
    cout << "  " << title << ":\n"
         << "    +----+-----------+----------+-----------+\n"
         << "    | №  | Тип       | Підсил.  | Imax, А   |\n"
         << "    +----+-----------+----------+-----------+\n";
    for (size_t i = 0; i < items.size(); ++i)
        cout << "    | " << left << setw(2) << i + 1 << " | " << setw(9) << items[i].getType()
             << " | " << right << setw(8) << fixed << setprecision(1) << items[i].getGain()
             << " | " << setw(9) << setprecision(2) << items[i].getMaxCurrent() << " |\n";
    cout << "    +----+-----------+----------+-----------+\n";
}

void Storage<Transistor>::printPower(double voltage) const {
    cout << "  Максимальна потужність при U = " << voltage << " В:\n";
    for (const Transistor& t : items)
        cout << "    " << left << setw(9) << t.getType() << right << setw(10)
             << fixed << setprecision(2) << t.power(voltage) << " Вт\n";
}
