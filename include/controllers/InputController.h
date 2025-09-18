#include <Arduino.h>
#include "ADS1X15.h"

class InputController
{
public:
    InputController(uint8_t address1, uint8_t address2, uint8_t address3, int intPin1, int intPin2, int intPin3);

    void begin();
    void ADS_request_all();
    int16_t *getValues();
    void SetSensorCalibrations(int sensorIndex, float rawHigh, float rawLow, float refHigh, float refLow);
    float getCalibratedValue(int sensorIndex);
    float *getAllCalibratedValues();
    bool handleConversion();

private:
    // Calibration variables for 12 sensors
    float rawHigh[12] = {0.0f};
    float rawLow[12] = {0.0f};
    float refHigh[12] = {0.0f};
    float refLow[12] = {0.0f};

    // Interrupt handlers
    static void adsReady_1();
    static void adsReady_2();
    static void adsReady_3();

    ADS1115 ads1;
    ADS1115 ads2;
    ADS1115 ads3;

    uint8_t address1;
    uint8_t address2;
    uint8_t address3;

    int intPin1; // GPIO pin for ADS1 interrupt
    int intPin2; // GPIO pin for ADS2 interrupt
    int intPin3; // GPIO pin for ADS3 interrupt

    //  two interrupt flags
    volatile bool RDY_1 = false;
    volatile bool RDY_2 = false;
    volatile bool RDY_3 = false;
    int16_t channel_1 = 0; //  channel from device 1
    int16_t channel_2 = 0; //  channel from device 2
    int16_t channel_3 = 0; //  channel from device 2

    //  array to hold the data.
    int16_t val[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

extern InputController inputController;