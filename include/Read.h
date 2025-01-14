#ifndef READ_H
#define READ_H

#include <Arduino.h>

#define CELSIUS 0
#define PERCENT 1
#define TESLA 2
#define VOLT 3
#define AMPERE 4
#define ADIMENTIONAL 5

template <typename T>
class Read
{
private:
    T value;
    uint8_t units;
protected:

public:
    Read(T value, uint8_t units) {
        this->value = value;
        this->units = units;
    }

    T getValue() {
        return value;
    }

    uint8_t getUnits() {
        return units;
    }

    Read operator-(const Read& other) const {
        if (this->units != other.units) {
            throw std::invalid_argument("Units must be the same for subtraction");
        }
        return Read(this->value - other.value, this->units);
    }

    Read operator+(const Read& other) const {
        if (this->units != other.units) {
            throw std::invalid_argument("Units must be the same for addition");
        }
        return Read(this->value + other.value, this->units);
    }

};

#endif // READ_H