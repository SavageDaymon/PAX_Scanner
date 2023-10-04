#ifndef PAX_GPIO
#define PAX_GPIO

#define RESERVED        2

#define IO_COUNT        55
#define I2C3_MUX_RST_N  1
#define I2C3A_RST_N     42
#define I2C3B_RST_N     43
#define LEDOUT          13
#define POWEREN         41

class HotPins
{
  public :

    void    SetupPins(void);
    void    DoToggle(int pin,int first,int ms, int second);
    void    SetPinLow(int pin);
    void    SetPinHigh(int pin);
    void    ReadPins(int * array);
    void    CheckPins(int * array);
};

#endif //  PAX_GPIO
