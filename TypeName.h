#ifndef TYPE_NAME_H
#define TYPE_NAME_H

#include <string>

class Transistor;

// Допоміжний шаблон: повертає назву типу T у вигляді рядка.

// 1) Загальний (основний) шаблон — для всіх типів, про які нічого не відомо
template <typename T>
struct TypeName {
    static std::string get() { return "невідомий тип"; }
};

// 2) Повні спеціалізації — для конкретних типів
template <> struct TypeName<int>         { static std::string get() { return "int"; } };
template <> struct TypeName<double>      { static std::string get() { return "double"; } };
template <> struct TypeName<std::string> { static std::string get() { return "std::string"; } };
template <> struct TypeName<Transistor>  { static std::string get() { return "Transistor"; } };

// 3) Часткова спеціалізація — для БУДЬ-ЯКОГО вказівника T*.
//    Працює рекурсивно: TypeName<Transistor**> -> "Transistor**"
template <typename T>
struct TypeName<T*> {
    static std::string get() { return TypeName<T>::get() + "*"; }
};

#endif
