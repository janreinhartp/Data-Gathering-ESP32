#include "controllers/ScaleController.h"
#include <Arduino.h>
#include "HX711.h"


static ScaleController *instancePtr = nullptr; // Global pointer for the ISR

ScaleController::ScaleController(int DataPin, int ClockPin, float calibrationFactor)
    : DataPin(DataPin), ClockPin(ClockPin), calibrationFactor(calibrationFactor)
{
    instancePtr = this; // Set the global instance pointer
}

void ScaleController::begin()
{
    scale.begin(DataPin, ClockPin);
    scale.set_scale(calibrationFactor); // Set the calibration factor
    scale.tare();                       // Reset the scale to 0
}

void ScaleController::tare()
{
    scale.tare(); // Reset the scale to 0
}

float ScaleController::getWeight()
{
    return scale.get_units(10); // Get the weight in grams (average of 10 readings)
}

void ScaleController::setCalibrationFactor(float factor)
{
    calibrationFactor = factor;
    scale.set_scale(calibrationFactor);
}

long ScaleController::readRawData()
{
    return scale.read(); // Read raw data from HX711
}