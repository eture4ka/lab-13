#include "Transistor.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

Transistor::Transistor(const string& t, double g, double i) : type("?"), gain(1), maxCurrent(1) {
    setType(t);
    setGain(g);
    setMaxCurrent(i);
}

string Transistor::getType() const { return type; }
double Transistor::getGain() const { return gain; }
double Transistor::getMaxCurrent() const { return maxCurrent; }

void Transistor::setType(const string& value) {
    if (value.empty()) throw invalid_argument("тип транзистора не може бути порожнім");
    type = value;
}

void Transistor::setGain(double value) {
    if (value <= 0 || value > 10000) {
        ostringstream msg;
        msg << "коефіцієнт підсилення " << value << " некоректний (0 < h <= 10000)";
        throw invalid_argument(msg.str());
    }
    gain = value;
}

void Transistor::setMaxCurrent(double value) {
    if (value <= 0 || value > 100) {
        ostringstream msg;
        msg << "струм " << value << " А некоректний (0 < I <= 100)";
        throw invalid_argument(msg.str());
    }
    maxCurrent = value;
}

double Transistor::power(double voltage) const { return voltage * maxCurrent; }

bool Transistor::operator<(const Transistor& other) const { return gain < other.gain; }
bool Transistor::operator==(const Transistor& other) const { return type == other.type; }

ostream& operator<<(ostream& os, const Transistor& t) {
    os << left << setw(9) << t.getType() << right
       << " (h = " << fixed << setprecision(1) << t.getGain()
       << ", Imax = " << setprecision(2) << t.getMaxCurrent() << " А)";
    return os;
}
