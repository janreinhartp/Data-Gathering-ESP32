#include <Arduino.h>
#include "Config.h"
#include "Controllers.h"

InputController inputController(ADS1115_ADDRESS1, ADS1115_ADDRESS2, ADS1115_ADDRESS3, INTERRUPT_PIN_1, INTERRUPT_PIN_2, INTERRUPT_PIN_3);

int16_t values[12] = {0};
float valuesf[12] = {0.0f};
void setSensorCalibrations()
{
  inputController.SetSensorCalibrations(0, S1_RAW_REF_HIGH, S1_RAW_REF_LOW, S1_REF_HIGH, S1_REF_LOW);
  inputController.SetSensorCalibrations(1, S2_RAW_REF_HIGH, S2_RAW_REF_LOW, S2_REF_HIGH, S2_REF_LOW);
  inputController.SetSensorCalibrations(2, S3_RAW_REF_HIGH, S3_RAW_REF_LOW, S3_REF_HIGH, S3_REF_LOW);
  inputController.SetSensorCalibrations(3, S4_RAW_REF_HIGH, S4_RAW_REF_LOW, S4_REF_HIGH, S4_REF_LOW);
  inputController.SetSensorCalibrations(4, S5_RAW_REF_HIGH, S5_RAW_REF_LOW, S5_REF_HIGH, S5_REF_LOW);
  inputController.SetSensorCalibrations(5, S6_RAW_REF_HIGH, S6_RAW_REF_LOW, S6_REF_HIGH, S6_REF_LOW);
  inputController.SetSensorCalibrations(6, S7_RAW_REF_HIGH, S7_RAW_REF_LOW, S7_REF_HIGH, S7_REF_LOW);
  inputController.SetSensorCalibrations(7, S8_RAW_REF_HIGH, S8_RAW_REF_LOW, S8_REF_HIGH, S8_REF_LOW);
  inputController.SetSensorCalibrations(8, S9_RAW_REF_HIGH, S9_RAW_REF_LOW, S9_REF_HIGH, S9_REF_LOW);
  inputController.SetSensorCalibrations(9, S10_RAW_REF_HIGH, S10_RAW_REF_LOW, S10_REF_HIGH, S10_REF_LOW);
  inputController.SetSensorCalibrations(10, S11_RAW_REF_HIGH, S11_RAW_REF_LOW, S11_REF_HIGH, S11_REF_LOW);
  inputController.SetSensorCalibrations(11, S12_RAW_REF_HIGH, S12_RAW_REF_LOW, S12_REF_HIGH, S12_REF_LOW);
}

void setup()
{
  Serial.begin(115200);
  inputController.begin();
  setSensorCalibrations();
}

void loop()
{
  // put your main code here, to run repeatedly:
  bool isReady = inputController.handleConversion();
  
  if(!isReady) {
    return;
  }

  int16_t *newValues = inputController.getValues();
  Serial.println("Raw Sensor Values:");
  for (int i = 0; i < 12; ++i)
  {
    values[i] = newValues[i];
    Serial.println("Pin " + String(i) + " : " + String(values[i]));
    delay(10);
  }

  float *newFloatValues = inputController.GetCalibratedValues();
  Serial.println("Calibrated Sensor Values:");
  for (int i = 0; i < 12; ++i)
  {
    valuesf[i] = newFloatValues[i];
    Serial.println("Pin " + String(i) + " : " + String(valuesf[i]));
    delay(10);
  }

  delay(1000);
}

