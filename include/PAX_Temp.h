#ifndef PAX_TEMP
#define PAX_TEMP

enum TemperatureSensorRegisters
{
    TS_TREG,    // 00 - Temperature Register
    TS_CREG,    // 01 - Configuration Register
    TS_HYST,    // 02 - Hysteresis Register
    TS_SHUT,    // 03 - Overtemperature Shutdown Register
    TS_TIDLE,   // 04 - Idle Register
};

struct ControlRegister
{
    unsigned char   Reserved    : 3;
    unsigned char   OS_Queue    : 2;
    unsigned char   OS_Polarity : 1;
    unsigned char   OS_OpMode   : 1;
    unsigned char   ShutDown    : 1;
};

#define TEMP_Convert        256.0
#define TEMP_Mask           0xFFE0
#define TEMP_OS_Mask        0xFF80

#define MAX_TEMP            38
#define RESTART_TEMP        35

#define SETPOINT_HEX_TO_DEGC            (0.5f)
#define TEMP_PCT2075_I2C_DEVICE_ADDRESS (0X48)

class TempSensor
{
    float   CurrentTemp;
    float   ShutoffTemp;
    float   RestartTemp;

  public :

    bool    Initialize(void);
    bool    ReadCurrent(float & temp);
    bool    SetShutoff(float temp);
    bool    ReadShutoff(float & temp);
    bool    SetRestart(float temp);
    bool    ReadRestart(float & temp);
};

extern TempSensor       Temp;

#endif //  PAX_TEMP
