#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include "Read.h"

class Temperature : public Read<float>
{
public:
    Temperature(float value, uint8_t source) : Read(value, CELSIUS, source) {}
    Temperature(Read<float> read) : Read(read.getValue(), CELSIUS, read.getSource()) {}
};

#endif // READ_H