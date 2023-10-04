#include "PAX_Includes.h"

struct I2C_Info I2C_Table[I2C_DEVICES] =
{//     Channel Mux Address Chip            Description
    {   I2C3,  -1,  0x70,   "TCA9548",      "I2C Multiplexer"       },  // Uses I2C3_MUX_RST_N
//  {   I2C3,   0,  0x00,   "SX1509",       "GPIO Expander"         },
    {   I2C3,   0,  0x21,   "AD7997/8",     "A/D Converter"         },
    {   I2C3,   0,  0x60,   "TLC59116F",    "LED Driver"            },  // Uses I2C3ARSTN
    {   I2C3,   1,  0x48,   "PCT2075",      "Temperature Sensor"    },  // Uses I2C3BRSTN
    {   I2C4,  -1,  0x48,   "RV-4162-C7",   "Real-time Clock"       }   // Uses RTC_IRQ
};

TwoWire * GetTwoWire(unsigned int devidx)
{
    if(I2C_Table[devidx].Chan == I2C4)
    {
        return(&Wire1);
    }
    return(&Wire);
}

TwoWire * IIC::Open(unsigned int devidx)
{
I2C_Info *  info = &I2C_Table[devidx];
TwoWire *   wire = GetTwoWire(devidx);

    if(info->Mux != -1)
    {
        wire->beginTransmission(MUX_ADDRESS);
        wire->write(1 << info->Mux);
        wire->endTransmission();
    }
    wire->beginTransmission(I2C_Table[devidx].Addr);
    return(wire);
}

bool IIC::Close(TwoWire * wire)
{
    return(wire->endTransmission() == 0);
}

bool IIC::Write(unsigned char devidx,unsigned char * bytes,int count)
{
TwoWire *   wire;

    wire = Open(devidx);
    wire->write(bytes,count);
    return(Close(wire));
}

bool IIC::SelectRegister(unsigned char devidx,unsigned char regidx)
{
    return(Write(devidx,&regidx,1));
}

bool IIC::WriteRegister(unsigned char devidx,unsigned char regidx,unsigned short value)
{
TwoBytes        reg;
unsigned char   buffer[16];

    reg.USHORT = value;

    buffer[0] = regidx;
    buffer[1] = reg.UCHAR[1];
    buffer[2] = reg.UCHAR[0];
    return(Write(devidx,buffer,3));
}

#define MAX_LOOPS       16

bool IIC::RequestBytes(unsigned char devidx,int count)
{
TwoWire *   wire = GetTwoWire(devidx);

    wire->requestFrom(I2C_Table[devidx].Addr,count);
    for(int loops=0;wire->available() == 0;loops++)
    {
        if(loops > MAX_LOOPS)
        {
            Serial.println("Failed to read I2C register");
            return(false);
        }
        delay(10);
    }
    return(true);
}

bool IIC::ReadRegister(unsigned char devidx,unsigned char regidx,unsigned short * value)
{
TwoWire *       wire = GetTwoWire(devidx);
TwoBytes        two;

    if(SelectRegister(devidx,regidx))
    {
        if(RequestBytes(devidx,2))
        {
            two.UCHAR[1] = wire->read();
            two.UCHAR[0] = wire->read();
            *value = two.USHORT;
            return(true);
        }
        else Serial.println("Failed to read I2C register");
    }
    else Serial.println("Failed to select I2C register");
    *value = 0;
    return(false);
}

void IIC::LocateDevices(void)
{
I2C_Info * tbl;

    for(unsigned char devidx=0;devidx<I2C_DEVICES;devidx++)
    {
        tbl = &I2C_Table[devidx];
        switch(tbl->Chan)
        {
        case I2C3 :
        case I2C4 :
            Serial.print(tbl->Desc);    Serial.print(" (");
            Serial.print(tbl->Chip);    Serial.print(") ");
            if(Close(Open(devidx)) == false)
            {
                Serial.print("NOT ");
            }
            Serial.println("Found");
            break;
        }
    }
}

void IIC::Startup(void)
{
	Serial.println("Initializing I2C Driver(s)");
    Wire.begin();
    Wire1.begin();
    LocateDevices();
    delay(10000);
}
