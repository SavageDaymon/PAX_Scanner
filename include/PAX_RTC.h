#ifndef PAX_RTC
#define PAX_RTC

enum RTC_Registers
{                             // Register
    RTCReg_Decimals,          // 00
    RTCReg_Seconds,           // 01
    RTCReg_Minutes,           // 02
    RTCReg_Hours,             // 03
    RTCReg_Day,               // 04
    RTCReg_Date,              // 05
    RTCReg_MonthCentury,      // 06
    RTCReg_Years,             // 07
    RTCReg_FreqComp,          // 08
    RTCReg_Watchdog,          // 09
    RTCReg_MonthAlarm,        // 0A
    RTCReg_DateAlarm,         // 0B
    RTCReg_HourAlarm,         // 0C
    RTCReg_MinuteAlarm,       // 0D
    RTCReg_SecondAlarm,       // 0E
    RTCReg_Flags,             // 0F

    RTC_RegisterCount
};

struct RTC_Time
{
    int     Month;
    int     Day;
    int     Year;
    int     Hour;
    int     Minute;
    int     Second;
    int     Millis;
};

struct RTC_Detail
{
    int             Dec10ths;
    int             Dec100ths;
    int             OscStopped;
    int             Seconds;
    int             OscFailIntEnable;
    int             Minutes;
    int             Hours;
    int             FreqDiv;
    int             Day;
    int             Date;
    int             Century;
    int             Month;
    int             Years;
    int             OUT;
    int             Calibration;
    int             FreqComp;
    int             WatchdogDiv;
    int             WatchdogMult;
    int             AlarmFlagEnable;
    int             ClockOutEnable;
    int             MonthAlarm;
    int             AlarmRepeatMode;
    int             DateAlarm;
    int             HourAlarm;
    int             MinuteAlarm;
    int             SecondAlarm;
    int             WatchdogTimerFailed;
    int             AlarmFlagSet;
    int             OscFailed;

    void    Load(unsigned char * regs);
};

class RTC
{
  public :

    bool    ReadTime(RTC_Time & rtime);
    void    DisplayTime(RTC_Time & rtime);
};

extern RTC       Time;

#endif //  PAX_RTC
