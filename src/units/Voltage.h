#ifndef VOLT_H
#define VOLT_H

#include <Arduino.h>
#include "Read.h"

class Volt : public Read<float>
{
public:
    Volt(float value, uint8_t source) : Read(value, VOLT, source) {}
    Volt(Read<float> read) : Read(read.getValue(), VOLT, read.getSource()){}
};

#endif