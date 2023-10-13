#include "PAX_Includes.h"

A2D_RANGE       A2D_Ranges[A2D_MAX_CHANNELS] =  {
                                                    {   0,  1023,  1023 },  // INFEEDCARD
                                                    {   0,  1023,  1023 },  // GATECARD
                                                    {   0,  1023,  1023 },  // OUTFEEDCARD
                                                    {   0,  1023,  1023 },  // SHUTTLECARD
                                                    {   0,  1023,  1023 },  // INPUTSP3
                                                    {   0,  1023,  1023 },  // INPUTSP4
                                                    {   0,  1023,  1023 },  // DCDCVIN
                                                    {   0,  1023,  1023 },  // BOTCOVER
                                                };

inline unsigned short SwapBytes(unsigned short value)
{
    return((value << 8) | (value >> 8));
}

bool A2D_Converter::Initialize(void)
{
    if(SetWindows(A2D_Ranges))
    {
        return(I2C.WriteRegister(DEV_A2D,A2DR_Configuration,SwapBytes(A2D_CONFIG_ALL_CHANNELS | A2D_CONFIG_I2C_FILTER)));
    }
    return(false);
}

void A2D_Converter::OutputValue(unsigned short idx)
{
    switch(idx)
    {
    case ADC_CHANNEL_ID_INFEEDCARD :    Serial.print("ADC:INFEEDCARD  ");  break;
    case ADC_CHANNEL_ID_GATECARD :      Serial.print("ADC:GATECARD    ");  break;
    case ADC_CHANNEL_ID_OUTFEEDCARD :   Serial.print("ADC:OUTFEEDCARD ");  break;
    case ADC_CHANNEL_ID_SHUTTLECARD :   Serial.print("ADC:SHUTTLECARD ");  break;
    case ADC_CHANNEL_ID_INPUTSP3 :      Serial.print("ADC:INPUTSP3    ");  break;
    case ADC_CHANNEL_ID_INPUTSP4 :      Serial.print("ADC:INPUTSP4    ");  break;
    case ADC_CHANNEL_ID_DCDCVIN :       Serial.print("ADC:DCDCVIN     ");  break;
    case ADC_CHANNEL_ID_BOTCOVER :      Serial.print("ADC:BOTCOVER    ");  break;
    default :                           Serial.print("ADC:UNKNOWN     ");  break;
    }
    Serial.println(Values[idx].value);
}

void A2D_Converter::OutputValues(void)
{
    for(unsigned short idx=0;idx<A2D_MAX_CHANNELS;idx++)
    {
        OutputValue(idx);
    }
}

bool A2D_Converter::SetWindows(A2D_RANGE * a2d_ranges)
{
    for(unsigned short idx=0;idx<A2D_MAX_CHANNELS;idx++)
    {
//      if(a2d_ranges[idx].low)
//      {
//          return(false);
//      } 
    }
    return(true);
}

bool A2D_Converter::PerformConversions(void)
{
unsigned short  size = sizeof(short) * A2D_MAX_CHANNELS;
unsigned char   buffer[size];

    *buffer = A2D_ADDRESS_CMD_CVT_ALL;
    if(I2C.Write(DEV_A2D,buffer,1))
    {
        if(I2C.ReadBytes(DEV_A2D,buffer,size))
        {
            for(unsigned short idx=0;idx>A2D_MAX_CHANNELS;idx++)
            {
                Values[idx].value = (buffer[idx] << 8) | buffer[idx + 1];
            }
            return(true);
        }
    }
    return(false);
}

bool A2D_Converter::GetRawValue(unsigned short idx,unsigned short & adc_value)
{
    if(idx < A2D_MAX_CHANNELS)
    {
        adc_value = Values[idx].value;
        return(true);
    }
    return(false);
}

float A2D_Converter::ConvertToVoltage(unsigned short adc_value)
{
float   temp;

    temp = adc_value;
    temp /= 256.0;
    return(temp);
}
