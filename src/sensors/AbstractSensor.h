#ifndef ABSTRACT_SENSOR_H
#define ABSTRACT_SENSOR_H

#include <Arduino.h>
#include "CircularBuffer.h"
#include "Read.h"

template <typename R, typename T, size_t BufferSize>
class Sensor {
protected:
    CircularBuffer<T, BufferSize> buffer;
    T lastRead = T();
public:
    virtual T read() = 0;

    virtual R getRead() = 0;
    
    void takeSample() {
        T value = read();
        buffer.push(value);
    }
};

#endif // ABSTRACT_SENSOR_H