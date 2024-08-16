#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <Arduino.h>

template <typename T, size_t Size>
class CircularBuffer {
private:
    T buffer[Size];
    size_t head = 0;
    size_t tail = 0;
    bool is_full = false;

public:
    void push(T item) {
        buffer[head] = item;
        
        if (is_full) {
            tail = (tail + 1) % Size;
        }

        head = (head + 1) % Size;
        is_full = head == tail;
    }

    T pop() {
        if (empty()) {
            return T(); // Retorna un valor por defecto en lugar de lanzar una excepción
        }

        T item = buffer[tail];
        is_full = false;
        tail = (tail + 1) % Size;

        return item;
    }

    T& operator[](size_t index) {
        return buffer[(tail + index) % Size];
    }

    const T& operator[](size_t index) const {
        return buffer[(tail + index) % Size];
    }

    bool empty() const {
        return (!is_full && (head == tail));
    }

    bool full() const {
        return is_full;
    }

    size_t size() const {
        if (is_full) {
            return Size;
        }
        if (head >= tail) {
            return head - tail;
        }
        return Size + head - tail;
    }

    T mean() const {
        if (empty()) {
            return T(); // Retorna un valor por defecto en lugar de lanzar una excepción
        }

        T sum = T();
        size_t count = size();
        for (size_t i = 0; i < count; ++i) {
            sum += buffer[(tail + i) % Size];
        }
        return sum / static_cast<T>(count);
    }

    void clear() {
        head = 0;
        tail = 0;
        is_full = false;
    }
};

#endif