#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include "Read.h"

class Temperature : public Read<float>
{
public:
    Temperature(float value) : Read(value, CELSIUS) {}
    Temperature(Read<float> read) : Read(read.getValue(), read.getUnits()) {}
};

#endif // READ_H