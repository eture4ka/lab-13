#include <iostream>
#include <stdexcept>
#include <string>
#include "Transistor.h"
#include "TypeName.h"
#include "Storage.h"
#include "StorageTransistor.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void header(const string& text) { cout << "\n========== " << text << " ==========\n"; }

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    cout << "Лабораторна робота. Варіант 18: Транзистор (тип, підсилення, макс. струм)\n";

    // ------------------------------------------------------------------------
    header("1. Загальний шаблон Storage<T>");

    Storage<int> gains;
    gains.add(200);
    gains.add(110);
    gains.add(40);
    gains.add(1500);
    gains.print("Коефіцієнти підсилення");
    cout << "  Найбільший: " << gains.max() << '\n';

    Storage<double> currents;
    currents.add(0.1);
    currents.add(1.5);
    currents.add(33.0);
    currents.print("Максимальні струми, А");
    cout << "  Найбільший: " << currents.max() << " А\n";

    Storage<string> types;
    types.add("KT315B");
    types.add("BC547");
    types.add("IRF540N");
    types.print("Типи");
    cout << "  Останній за алфавітом: " << types.max() << '\n';

    try {
        cout << "  Звернення до gains.get(10):\n";
        gains.get(10);
    } catch (const out_of_range& e) {
        cout << "    ! Виняток: " << e.what() << '\n';
    }

    // ------------------------------------------------------------------------
    header("2. Часткова спеціалізація Storage<T*>");

    Transistor t1("KT315B", 200, 0.1);
    Transistor t2("KT815", 40, 1.5);
    Transistor t3("2N3055", 20, 15);

    Storage<Transistor*> pointers;
    pointers.add(&t1);
    pointers.add(&t2);
    pointers.add(nullptr);             // спеціалізація не прийме nullptr
    pointers.add(&t3);
    pointers.print("Вказівники на транзистори");
    cout << "  Найбільше підсилення (порівнюються об'єкти, а не адреси): " << pointers.max() << '\n';

    cout << "\n  Змінюємо оригінальний об'єкт t2: setGain(350)\n";
    t2.setGain(350);
    cout << "  Сховище зберігає вказівники, тому бачить зміну:\n";
    cout << "  Елемент 2: " << pointers.get(1) << '\n';
    cout << "  Новий максимум: " << pointers.max() << '\n';

    cout << "\n  Та сама часткова спеціалізація працює для будь-якого T*:\n";
    double i1 = 0.5, i2 = 12.0;
    Storage<double*> currentPtrs;
    currentPtrs.add(&i1);
    currentPtrs.add(&i2);
    currentPtrs.print("Вказівники на струми");
    cout << "  Найбільше значення: " << currentPtrs.max() << '\n';

    // ------------------------------------------------------------------------
    header("3. Повна спеціалізація Storage<Transistor>");

    Storage<Transistor> stock;
    stock.add("KT315B", 200, 0.1);
    stock.add("BC547", 110, 0.1);
    stock.add("2N3055", 20, 15);
    stock.add("IRF540N", 1500, 33);
    cout << "  Перевірка даних:\n";
    stock.add("", 100, 1);                 // порожній тип
    stock.add("BAD", 100, -5);             // від'ємний струм
    stock.add("KT315B", 300, 0.2);         // дублікат за типом
    stock.add(t2);                         // додавання готового об'єкта

    stock.print("Склад транзисторів");
    cout << "  Найбільше підсилення: " << stock.max() << '\n';
    cout << "  Сумарний максимальний струм: " << stock.totalCurrent() << " А\n";

    for (const char* name : {"2N3055", "BD139"}) {
        const Transistor* found = stock.findByType(name);
        cout << "  Пошук \"" << name << "\": ";
        if (found) cout << *found << '\n';
        else cout << "не знайдено\n";
    }
    stock.printPower(12);

    // ------------------------------------------------------------------------
    header("4. Спеціалізації шаблону TypeName<T>");
    cout << "  TypeName<int>          = " << TypeName<int>::get() << "   (повна)\n"
         << "  TypeName<Transistor>   = " << TypeName<Transistor>::get() << "   (повна)\n"
         << "  TypeName<double*>      = " << TypeName<double*>::get() << "   (часткова)\n"
         << "  TypeName<Transistor**> = " << TypeName<Transistor**>::get() << "   (часткова, двічі)\n"
         << "  TypeName<float>        = " << TypeName<float>::get() << "   (загальний шаблон)\n";

    cout << "\nПрограму завершено.\n";
    return 0;
}
