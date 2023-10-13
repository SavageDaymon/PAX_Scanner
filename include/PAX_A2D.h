#ifndef PAX_A2D
#define PAX_A2D

#define A2D_MAX_CHANNELS            8

#define A2D_ADDRESS_REG_MASK        0x0F

#define A2D_ADDRESS_CMD_CVT_NONE    0x00
#define A2D_ADDRESS_CMD_CVT_ALL     0x70
#define A2D_ADDRESS_CMD_CVT_CH1     0x80
#define A2D_ADDRESS_CMD_CVT_CH2     0x90
#define A2D_ADDRESS_CMD_CVT_CH3     0xA0
#define A2D_ADDRESS_CMD_CVT_CH4     0xB0
#define A2D_ADDRESS_CMD_CVT_CH5     0xC0
#define A2D_ADDRESS_CMD_CVT_CH6     0xD0
#define A2D_ADDRESS_CMD_CVT_CH7     0xE0
#define A2D_ADDRESS_CMD_CVT_CH8     0xF0

#define A2D_CONFIG_DONTCARE         0xF000
#define A2D_CONFIG_ALL_CHANNELS     0x0FF0
#define A2D_CONFIG_I2C_FILTER       0x0008
#define A2D_CONFIG_ALERT            0x0004
#define A2D_CONFIG_BUSY             0x0002
#define A2D_CONFIG_POLARITY         0x0001

#define ADC_CHANNEL_ID_INFEEDCARD	0
#define ADC_CHANNEL_ID_GATECARD		1
#define ADC_CHANNEL_ID_OUTFEEDCARD	2
#define ADC_CHANNEL_ID_SHUTTLECARD	3
#define ADC_CHANNEL_ID_INPUTSP3		4
#define ADC_CHANNEL_ID_INPUTSP4		5
#define ADC_CHANNEL_ID_DCDCVIN		6
#define ADC_CHANNEL_ID_BOTCOVER		7

enum A2D_Registers
{
    A2DR_ConversionResult,
    A2DR_AlertStatus,
    A2DR_Configuration,
    A2DR_CycleTimer,
    A2DR_DataLow_CH1,
    A2DR_DataHigh_CH1,
    A2DR_Hysteresis_CH1,
    A2DR_DataLow_CH2,
    A2DR_DataHigh_CH2,
    A2DR_Hysteresis_CH2,
    A2DR_DataLow_CH3,
    A2DR_DataHigh_CH3,
    A2DR_Hysteresis_CH3,
    A2DR_DataLow_CH4,
    A2DR_DataHigh_CH4,
    A2DR_Hysteresis_CH4,
};

struct A2D_RANGE
{
    unsigned short  low;
    unsigned short  high;
    unsigned short  hysteresis;
};

struct A2D_Channel
{
    unsigned short  value;
};

class A2D_Converter
{
  public :

    A2D_Channel Values[A2D_MAX_CHANNELS];

    bool    Initialize(void);
    bool    Configure(void);
    void    OutputValue(unsigned short idx);
    void    OutputValues(void);
    bool    PerformConversions(void);
    bool    GetRawValue(unsigned short idx,unsigned short & adc_value);
    bool    SetWindows(A2D_RANGE * a2d_ranges);

    float   ConvertToVoltage(unsigned short adc_value);
};

extern A2D_Converter    A2D;

#endif //  PAX_A2D
