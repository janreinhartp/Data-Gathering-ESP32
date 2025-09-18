#include "controllers/InputController.h"
#include <Arduino.h>
#include "Config.h"

// Static pointer to instance for ISR access
static InputController *instancePtr = nullptr; // Global pointer for the ISR

InputController::InputController(uint8_t address1, uint8_t address2, uint8_t address3, int intPin1, int intPin2, int intPin3)
    : ads1(address1), ads2(address2), ads3(address3),
      address1(address1), address2(address2), address3(address3), intPin1(intPin1), intPin2(intPin2), intPin3(intPin3)
{
    instancePtr = this; // Set the global instance pointer
}
void InputController::begin()
{
    Wire.begin();
    pinMode(intPin1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intPin1), adsReady_1, RISING);

    //  SETUP FIRST ADS1115
    ads1.begin();
    ads1.setGain(0);     //  0 == 6.144 volt, default
    ads1.setDataRate(7); //  0 = slow   4 = medium   7 = fast

    //  SET ALERT RDY PIN
    ads1.setComparatorThresholdHigh(0x8000);
    ads1.setComparatorThresholdLow(0x0000);
    ads1.setComparatorQueConvert(0);

    //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
    pinMode(intPin1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intPin1), adsReady_1, RISING);

    ads1.setMode(0);         //  0 == continuous mode
    ads1.readADC(channel_1); //  0 == default channel,  trigger first read

    pinMode(intPin2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intPin2), adsReady_2, RISING);
    //  SETUP SECOND ADS1115
    ads2.begin();
    ads2.setGain(0);     //  0 == 6.144 volt, default
    ads2.setDataRate(7); //  0 = slow   4 = medium   7 = fast
    //  SET ALERT RDY PIN
    ads2.setComparatorThresholdHigh(0x8000);
    ads2.setComparatorThresholdLow(0x0000);
    ads2.setComparatorQueConvert(0);

    //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
    pinMode(intPin2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intPin2), adsReady_2, RISING);
    ads2.setMode(0);         //  0 == continuous mode
    ads2.readADC(channel_2); //  0 == default channel,  trigger

    pinMode(intPin3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intPin3), adsReady_3, RISING);

    //  SETUP THIRD ADS1115
    ads3.begin();
    ads3.setGain(0);     //  0 == 6.144 volt, default
    ads3.setDataRate(7); //  0 = slow   4 = medium   7 = fast
    //  SET ALERT RDY PIN
    ads3.setComparatorThresholdHigh(0x8000);
    ads3.setComparatorThresholdLow(0x0000);
    ads3.setComparatorQueConvert(0);

    //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
    pinMode(intPin3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intPin3), adsReady_3, RISING);

    ads3.setMode(0);         //  0 == continuous mode
    ads3.readADC(channel_3); //  0 == default channel,  trigger first read
}

void InputController::adsReady_1()
{
    if (instancePtr)
    {
        instancePtr->RDY_1 = true;
        ;
    }
}

void InputController::adsReady_2()
{
    if (instancePtr)
    {
        instancePtr->RDY_2 = true;
        ;
    }
}

void InputController::adsReady_3()
{
    if (instancePtr)
    {
        instancePtr->RDY_3 = true;
        ;
    }
}

bool InputController::handleConversion()
{
    bool newData = false;
    if (RDY_1)
    {
        val[channel_1 + 0] = ads1.getValue();
        channel_1++;
        if (channel_1 > 3)
            channel_1 = 0;
        ads1.readADC(channel_1);
        RDY_1 = false;
        newData = true;
    }
    if (RDY_2)
    {
        val[channel_2 + 4] = ads2.getValue();
        channel_2++;
        if (channel_2 > 3)
            channel_2 = 0;
        ads2.readADC(channel_2);
        RDY_2 = false;
        newData = true;
    }
    if (RDY_3)
    {
        val[channel_3 + 8] = ads3.getValue();
        channel_3++;
        if (channel_3 > 3)
            channel_3 = 0;
        ads3.readADC(channel_3);
        RDY_3 = false;
        newData = true;
    }
    return newData;
}

int16_t *InputController::getValues()
{
    return this->val;
}

void InputController::SetSensorCalibrations(int sensorIndex, float rawHigh, float rawLow, float refHigh, float refLow)
{
    if (sensorIndex < 0 || sensorIndex >= 12)
    {
        Serial.println("Invalid sensor index");
        return;
    }
    this->rawHigh[sensorIndex] = rawHigh;
    this->rawLow[sensorIndex] = rawLow;
    this->refHigh[sensorIndex] = refHigh;
    this->refLow[sensorIndex] = refLow;
}

float InputController::getCalibratedValue(int sensorIndex)
{
    if (sensorIndex < 0 || sensorIndex >= 12)
    {
        Serial.println("Invalid sensor index");
        return 0.0f;
    }
    float rawValue = static_cast<float>(this->val[sensorIndex]);
    // Prevent division by zero
    if (rawHigh[sensorIndex] == rawLow[sensorIndex])
    {
        Serial.println("Invalid calibration data: rawHigh equals rawLow");
        return 0.0f;
    }
    // Linear interpolation formula
    float calibratedValue = refLow[sensorIndex] + (rawValue - rawLow[sensorIndex]) * (refHigh[sensorIndex] - refLow[sensorIndex]) / (rawHigh[sensorIndex] - rawLow[sensorIndex]);
    return calibratedValue;
}

float* InputController::getAllCalibratedValues()
{
    static float calibratedValues[12];
    for (int i = 0; i < 12; ++i)
    {
        calibratedValues[i] = getCalibratedValue(i);
    }
    return calibratedValues;
}