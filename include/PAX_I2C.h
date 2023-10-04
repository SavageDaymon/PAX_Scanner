#ifndef PAX_I2C
#define PAX_I2C

#define MUX_ADDRESS     0x70
#define MUX_CHANNELS    4

class IIC
{
  public :

    void        Startup(void);
    void        LocateDevices(void);
    void        SelectMuxChannel(unsigned int devidx);
    TwoWire *   Open(unsigned int devidx);
    bool        Close(TwoWire * wire);
    bool        Write(unsigned char devidx,unsigned char * bytes,int count);
    bool        WriteRegister(unsigned char devidx,unsigned char regidx,unsigned short value);
    bool        ReadRegister(unsigned char devidx,unsigned char regidx,unsigned short * value);
    bool        SelectRegister(unsigned char devidx,unsigned char regidx);
    bool        RequestBytes(unsigned char devidx,int count);
};

enum
{
    DEV_MUX,
//  DEV_EXP,
    DEV_A2D,
    DEV_LED,
    DEV_TEMP,
    DEV_RTC,

    I2C_DEVICES
};

enum
{
    I2C1,
    I2C2,
    I2C3,
    I2C4,
};

struct I2C_Info
{
    int             Chan;
    int             Mux;
    int             Addr;
    const char *    Chip;
    const char *    Desc;

};

extern IIC              I2C;
extern struct I2C_Info  I2C_Table[I2C_DEVICES];

#endif //  PAX_I2C
