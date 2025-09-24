#include <Arduino.h>
#include "HX711.h"

class ScaleController
{
public:
    ScaleController(int DataPin, int ClockPin, float calibrationFactor);
    void begin();
    void tare();
    float getWeight();
    void setCalibrationFactor(float factor);

private:
    int DataPin;
    int ClockPin;
    float calibrationFactor = 1.0; // Adjust this factor based on your calibration
    long readRawData();
    HX711 scale;
};
extern ScaleController scaleController;