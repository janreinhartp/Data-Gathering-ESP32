#include <Arduino.h>
#include "Config.h"
#include "Controllers.h"

InputController inputController(ADS1115_ADDRESS1, ADS1115_ADDRESS2, ADS1115_ADDRESS3, INTERRUPT_PIN_1, INTERRUPT_PIN_2, INTERRUPT_PIN_3);

int16_t values[12] = {0};

void setup()
{
  Serial.begin(115200);
  inputController.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  inputController.handleConversion();
  int16_t *newValues = inputController.getValues();
  for (int i = 0; i < 12; ++i)
  {
    values[i] = newValues[i];
    Serial.println("Pin " + String(i) + " : " + String(values[i]));
    delay(100);
  }
}