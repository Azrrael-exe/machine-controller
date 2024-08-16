#ifndef VOLT_H
#define VOLT_H

#include <Arduino.h>
#include "Read.h"

class Volt : public Read<float>
{
public:
    Volt(float value) : Read(value, VOLT) {}
};

#endif // READ_H