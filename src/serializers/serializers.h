#ifndef SERIALIZERS_H
#define SERIALIZERS_H

#include <Arduino.h>
#include <Read.h> 
#include <array>

template <typename T, size_t array_size = 6>
std::array<byte, array_size> readToBytes(Read<T>& readObject) {
    std::array<byte, array_size> bytes;
    bytes[0] = readObject.getSource();
    long value = long(readObject.getValue());
    bytes[1] = byte(value >> 24);
    bytes[2] = byte(value >> 16);
    bytes[3] = byte(value >> 8);
    bytes[4] = byte(value);
    bytes[5] = readObject.getUnits();
    return bytes;
}

template <typename T>
Read<T> readFromBytes(const std::array<byte, 6>& bytes) {
    uint8_t source = bytes[0];
    T value = (bytes[1] << 24) | (bytes[2] << 16) | (bytes[3] << 8) | bytes[4];
    uint8_t units = bytes[5];
    return Read(value, units, source);
}

template<size_t MAX_READS = 10>
class BytesSerializer {
private:
    std::array<byte, MAX_READS * 6> buffer;
    size_t currentSize = 0;
    uint8_t header;

public:
    BytesSerializer(uint8_t header) {
        this->header = header;
    }

    template <typename T>
    bool addRead(Read<T>& readObject) {
        if (currentSize + 6 > buffer.size()) {
            return false;
        }
        auto bytes = readToBytes(readObject);
        std::copy(bytes.begin(), bytes.end(), buffer.begin() + currentSize);
        currentSize += 6;
        return true;
    }

    void clear() {
        currentSize = 0;
    }

    std::array<byte, MAX_READS * 6> getBuffer() const {
        return buffer;
    }

    size_t getSize() const {
        return currentSize;
    }

    template<size_t N>
    static byte checkSum(const std::array<byte, N>& arr, size_t size) {
        long sum = 0;
        for (size_t i = 0; i < size && i < N; i++) {
            sum += arr[i];
        }
        return byte(sum & 0xFF);
    }

    uint8_t writeToStream(Stream& stream) const {
        uint8_t bytesWritten = 0;

        bytesWritten += stream.write(header);
        bytesWritten += stream.write(byte(currentSize));
        bytesWritten += stream.write(buffer.data(), currentSize);
        bytesWritten += stream.write(checkSum(buffer, currentSize));

        return bytesWritten;
    }

    bool readIncommingBuffer(Stream& stream) {
        if (stream.available() < 2) return false;  // Necesitamos al menos header y length

        uint8_t incomingByte = stream.read();
        if (incomingByte != header) return false;

        uint8_t expectedLength = stream.read();
        if (expectedLength > MAX_READS * 6) return false;  // Longitud inválida

        // Esperar hasta que todos los bytes estén disponibles
        unsigned long startTime = millis();
        while (stream.available() < expectedLength + 1) {  // +1 para el checksum
            if (millis() - startTime > 1000) return false;  // Timeout después de 1 segundo
            delay(1);  // Pequeña pausa para no saturar el CPU
        }

        // Leer los datos directamente en el buffer
        clear();  // Limpiar el buffer antes de leer nuevos datos
        for (size_t i = 0; i < expectedLength; i++) {
            buffer[i] = stream.read();
            currentSize++;
        }

        // Leer y verificar el checksum
        byte incomingCheckSum = stream.read();
        if (incomingCheckSum != checkSum(buffer, currentSize)) {
            clear();  // Limpiar el buffer si el checksum no coincide
            return false;
        }

        return true;
    }
};

#endif