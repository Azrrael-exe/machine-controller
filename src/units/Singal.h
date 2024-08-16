#ifndef SIGNAL_H
#define SIGNAL_H

#include <Arduino.h>
#include "Read.h"

class Signal : public Read<float>
{
public:
    Signal(float value) : Read(value, PERCENT) {}
};

#endif // READ_H