#ifndef TRANSISTOR_H
#define TRANSISTOR_H

#include <iostream>
#include <string>

// Клас варіанту 18: транзистор (тип, коефіцієнт підсилення, максимальний струм)
class Transistor {
private:
    std::string type;    // тип (маркування)
    double gain;         // коефіцієнт підсилення
    double maxCurrent;   // максимальний струм, А

public:
    // Кидає std::invalid_argument, якщо дані некоректні
    Transistor(const std::string& type, double gain, double maxCurrent);

    std::string getType() const;
    double getGain() const;
    double getMaxCurrent() const;

    void setType(const std::string& value);
    void setGain(double value);
    void setMaxCurrent(double value);

    double power(double voltage) const;   // P = U * Imax, Вт

    bool operator<(const Transistor& other) const;    // порівняння за підсиленням
    bool operator==(const Transistor& other) const;   // однаковий тип
};

std::ostream& operator<<(std::ostream& os, const Transistor& t);

#endif
