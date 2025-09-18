#pragma once

#include <Arduino.h>

// HARDWARE CONFIGURATION
#define ADS1115_ADDRESS1 0x48
#define ADS1115_ADDRESS2 0x49
#define ADS1115_ADDRESS3 0x4A

#define INTERRUPT_PIN_1 3  // GPIO pin for ADS1 interrupt
#define INTERRUPT_PIN_2 1  // GPIO pin for ADS2 interrupt
#define INTERRUPT_PIN_3 0  // GPIO pin for ADS3 interrupt

#define MAC_ADDRESS_SENDER {0x20, 0x6E, 0xF1, 0x6C, 0x33, 0x18}
#define MAC_ADDRESS_RECEIVER {0x10, 0x51, 0xDB, 0x75, 0xD2, 0x48}

#define S1_RAW_REF_HIGH 32767
#define S1_RAW_REF_LOW -32768
#define S1_REF_HIGH 10.0
#define S1_REF_LOW -10.0

#define S2_RAW_REF_HIGH 32767
#define S2_RAW_REF_LOW -32768
#define S2_REF_HIGH 10.0
#define S2_REF_LOW -10.0

#define S3_RAW_REF_HIGH 32767
#define S3_RAW_REF_LOW -32768
#define S3_REF_HIGH 10.0
#define S3_REF_LOW -10.0    

#define S4_RAW_REF_HIGH 32767
#define S4_RAW_REF_LOW -32768
#define S4_REF_HIGH 10.0
#define S4_REF_LOW -10.0    

#define S5_RAW_REF_HIGH 32767
#define S5_RAW_REF_LOW -32768
#define S5_REF_HIGH 10.0
#define S5_REF_LOW -10.0    

#define S6_RAW_REF_HIGH 32767
#define S6_RAW_REF_LOW -32768
#define S6_REF_HIGH 10.0
#define S6_REF_LOW -10.0    

#define S7_RAW_REF_HIGH 32767
#define S7_RAW_REF_LOW -32768
#define S7_REF_HIGH 10.0
#define S7_REF_LOW -10.0    

#define S8_RAW_REF_HIGH 32767
#define S8_RAW_REF_LOW -32768
#define S8_REF_HIGH 10.0
#define S8_REF_LOW -10.0    

#define S9_RAW_REF_HIGH 32767
#define S9_RAW_REF_LOW -32768
#define S9_REF_HIGH 10.0
#define S9_REF_LOW -10.0    

#define S10_RAW_REF_HIGH 32767
#define S10_RAW_REF_LOW -32768
#define S10_REF_HIGH 10.0
#define S10_REF_LOW -10.0    

#define S11_RAW_REF_HIGH 32767
#define S11_RAW_REF_LOW -32768
#define S11_REF_HIGH 10.0
#define S11_REF_LOW -10.0    

#define S12_RAW_REF_HIGH 32767
#define S12_RAW_REF_LOW -32768
#define S12_REF_HIGH 10.0
#define S12_REF_LOW -10.0    

// DEFAULT CONFIGURATION