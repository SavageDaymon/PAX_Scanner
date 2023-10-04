#include "PAX_Includes.h"

inline float Get_Temp(short temp)       {    return(float(temp & TEMP_Mask) / TEMP_Convert);    }
inline float Get_OS_Temp(short temp)    {    return(float(temp & TEMP_OS_Mask) / TEMP_Convert); }
inline short Get_OS_Temp(float temp)    {    return(short(temp * TEMP_Convert));                }

bool TempSensor::Initialize(void)
{
    if(SetShutoff(MAX_TEMP))
    {
        return(SetRestart(RESTART_TEMP));
    }
    return(false);
}

bool TempSensor::ReadCurrent(float & temp)
{
TwoBytes    two;

    if(I2C.ReadRegister(DEV_TEMP,TS_TREG,&two.USHORT) == false)
    {
        Serial.println("Failed to read current temperature register!");
        CurrentTemp = temp = 0.0;
        return(false);
    }
    CurrentTemp = temp = Get_Temp(two.SHORT);
    return(true);
}

bool TempSensor::SetShutoff(float temp)
{
    return(I2C.WriteRegister(DEV_TEMP,TS_SHUT,Get_OS_Temp(ShutoffTemp = temp)));
}

bool TempSensor::ReadShutoff(float & temp)
{
TwoBytes    two;

    if(I2C.ReadRegister(DEV_TEMP,TS_SHUT,&two.USHORT) == false)
    {
        Serial.println("Failed to read shutoff temperature register!");
        ShutoffTemp = temp = 0.0;
        return(false);
    }
    ShutoffTemp = temp = Get_OS_Temp(two.SHORT);
    return(true);
}

bool TempSensor::SetRestart(float temp)
{
    return(I2C.WriteRegister(DEV_TEMP,TS_HYST,Get_OS_Temp(RestartTemp = temp)));
}

bool TempSensor::ReadRestart(float & temp)
{
TwoBytes    two;

    if(I2C.ReadRegister(DEV_TEMP,TS_HYST,&two.USHORT) == false)
    {
        Serial.println("Failed to read restart temperature register!");
        RestartTemp = temp = 0.00;
        return(false);
    }
    RestartTemp = temp = Get_OS_Temp(two.SHORT);
    return(true);
}
