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
    uint8_t id;
public:
    Sensor(uint8_t id) {
        this->id = id;
    }

    virtual T read() = 0;

    virtual R getRead() = 0;
    
    void takeSample() {
        T value = read();
        buffer.push(value);
    }

    uint8_t getId() {
        return this->id;
    }
};

#endif // ABSTRACT_SENSOR_H