#include <Arduino.h>
#include <Wire.h>

#include "PAX_GPIO.h"
#include "PAX_I2C.h"
#include "PAX_Temp.h"
#include "PAX_RTC.h"

union TwoBytes
{
    unsigned char   UCHAR[2];
    unsigned short  USHORT;
    short           SHORT;
};
