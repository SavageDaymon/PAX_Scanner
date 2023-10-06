#include "PAX_Includes.h"

unsigned char GetBitField(unsigned char byte,unsigned char lowbit,unsigned char highbit)
{
unsigned char  value;

    value = byte >> lowbit;
    value &= ((1 << (highbit - lowbit + 1)) - 1);
    return(value);
}

unsigned char BCD(unsigned char value)
{
    return((value >> 4) * 10 + (value & 0x0F));
}

void RTC_Detail::Load(unsigned char * regs)
{
    Dec10ths             = BCD( GetBitField(regs[RTCReg_Decimals],4,7));
    Dec100ths            = BCD( GetBitField(regs[RTCReg_Decimals],0,3));
    OscStopped           =      GetBitField(regs[RTCReg_Seconds ],7,7);
    Seconds              = BCD( GetBitField(regs[RTCReg_Seconds ],0,6));
    OscFailIntEnable     =      GetBitField(regs[RTCReg_Minutes ],7,7);
    Minutes              = BCD( GetBitField(regs[RTCReg_Minutes ],0,6));
    Hours                = BCD( GetBitField(regs[RTCReg_Hours   ],0,5));
    FreqDiv              =      GetBitField(regs[RTCReg_Day     ],4,7);
    Day                  =      GetBitField(regs[RTCReg_Day     ],0,2);
    Date                 = BCD( GetBitField(regs[RTCReg_Date    ],0,5));
    Century              =      GetBitField(regs[RTCReg_MonthCentury],6,7);
    Month                = BCD( GetBitField(regs[RTCReg_MonthCentury],0,4));
    Years                = BCD( GetBitField(regs[RTCReg_Years   ],0,7));
    OUT                  =      GetBitField(regs[RTCReg_FreqComp],7,7);
    Calibration          =      GetBitField(regs[RTCReg_FreqComp],5,5);
    FreqComp             =      GetBitField(regs[RTCReg_FreqComp],0,4);
    WatchdogDiv          =      GetBitField(regs[RTCReg_Watchdog],7,7) << 2 |
                                GetBitField(regs[RTCReg_Watchdog],0,1);
    WatchdogMult         =      GetBitField(regs[RTCReg_Watchdog],2,6);
    AlarmFlagEnable      =      GetBitField(regs[RTCReg_MonthAlarm],7,7);
    ClockOutEnable       =      GetBitField(regs[RTCReg_MonthAlarm],6,6);
    MonthAlarm           = BCD( GetBitField(regs[RTCReg_MonthAlarm],0,4));
    AlarmRepeatMode      =      GetBitField(regs[RTCReg_DateAlarm  ],6,6) << 4 |
                                GetBitField(regs[RTCReg_DateAlarm  ],7,7) << 3 |
                                GetBitField(regs[RTCReg_HourAlarm  ],7,7) << 2 |
                                GetBitField(regs[RTCReg_MinuteAlarm],7,7) << 1 |
                                GetBitField(regs[RTCReg_SecondAlarm],7,7);
    DateAlarm            = BCD( GetBitField(regs[RTCReg_DateAlarm],0,5));
    HourAlarm            = BCD( GetBitField(regs[RTCReg_HourAlarm],0,5));
    MinuteAlarm          = BCD( GetBitField(regs[RTCReg_MinuteAlarm],0,6));
    SecondAlarm          = BCD( GetBitField(regs[RTCReg_SecondAlarm],0,6));
    WatchdogTimerFailed  =      GetBitField(regs[RTCReg_Flags],7,7);
    AlarmFlagSet         =      GetBitField(regs[RTCReg_Flags],6,6);
    OscFailed            =      GetBitField(regs[RTCReg_Flags],2,2);
}

bool RTC::ReadTime(RTC_Time & rtime)
{
unsigned char   raw[16];
RTC_Detail      detail;

    if(I2C.ReadBytes(DEV_RTC,raw,16))
    {
        detail.Load(raw);
        rtime.Month    = detail.Month;
        rtime.Day      = detail.Date;
        rtime.Year     = 2000 + (detail.Century * 100) + detail.Years;
        rtime.Hour     = detail.Hours;
        rtime.Minute   = detail.Minutes;
        rtime.Second   = detail.Seconds;
        rtime.Millis   = (detail.Dec10ths * 100) + (detail.Dec100ths * 10);
        return(true);
    }
    return(false);
}

void DisplayDoubleDigits(int value)
{
    if(value < 10)  Serial.print("0");
    Serial.print(value);
}

void RTC::DisplayTime(RTC_Time & rtime)
{
    DisplayDoubleDigits(rtime.Hour);    Serial.print(":");
    DisplayDoubleDigits(rtime.Minute);  Serial.print(":");
    DisplayDoubleDigits(rtime.Second);  Serial.print(" ");
    DisplayDoubleDigits(rtime.Month);   Serial.print("/");
    DisplayDoubleDigits(rtime.Day);     Serial.print("/");
    Serial.println(rtime.Year);
}
