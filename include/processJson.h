#ifndef SEND_JSON_H
#define SEND_JSON_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include "Read.h"

template <typename T, size_t DocSize = 200>
StaticJsonDocument<DocSize> readToJson(Read<T>& readObject) {
    
    StaticJsonDocument<DocSize> jsonDoc;
    jsonDoc["id"] = readObject.getSource();
    jsonDoc["value"] = readObject.getValue();
    jsonDoc["unit"] = readObject.getUnits();

    return jsonDoc;
}

#endif
