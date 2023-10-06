#include "PAX_Includes.h"

struct I2C_Info I2C_Table[I2C_DEVICES] =
{//     Channel Mux Address Chip            Description
    {   I2C3,  -1,  0x70,   "TCA9548",      "I2C Multiplexer"       },  // Uses I2C3_MUX_RST_N
//  {   I2C3,   0,  0x00,   "SX1509",       "GPIO Expander"         },
    {   I2C3,   0,  0x21,   "AD7997/8",     "A/D Converter"         },
    {   I2C3,   0,  0x60,   "TLC59116F",    "LED Driver"            },  // Uses I2C3ARSTN
    {   I2C3,   1,  0x48,   "PCT2075",      "Temperature Sensor"    },  // Uses I2C3BRSTN
    {   I2C4,  -1,  0x68,   "RV-4162-C7",   "Real-time Clock"       }   // Uses RTC_IRQ
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
        wire->beginTransmission(I2C_Table[DEV_MUX].Addr);
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

bool IIC::Write(unsigned char devidx,unsigned char * bytes,unsigned int count)
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

bool IIC::RequestBytes(unsigned char devidx,unsigned int count)
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

bool IIC::ReadBytes(unsigned char devidx,unsigned char * bytes,unsigned int count)
{
    return(RequestBytes(devidx,count) && GetTwoWire(devidx)->readBytes(bytes,count) == count);
}

inline unsigned short SwapBytes(unsigned short value)
{
    return((value << 8) | (value >> 8));
}

bool IIC::ReadWords(unsigned char devidx,unsigned short * values,unsigned int count)
{
unsigned int idx;

    if(ReadBytes(devidx,(unsigned char *) values,count*2))
    {
        for(idx=0;idx<count;idx++)
        {
            values[idx] = SwapBytes(values[idx]);
        }
        return(true);
    }
    else Serial.println("Failed to read words");
    return(false);
}

bool IIC::ReadRegister(unsigned char devidx,unsigned char regidx,unsigned short * value)
{
    if(SelectRegister(devidx,regidx))
    {
        return(ReadWords(devidx,value,1));
    }
    else Serial.println("Failed to select word register");
    return(false);
}

bool IIC::ReadRegister(unsigned char devidx,unsigned char regidx,unsigned char * value)
{
    if(SelectRegister(devidx,regidx))
    {
        return(ReadBytes(devidx,value,1));
    }
    else Serial.println("Failed to select byte register");
    return(false);
}

int IIC::ScanAll(int channel)
{
TwoWire *   wire = channel == I2C4 ? &Wire1 : &Wire;
int         addr,count;

    Serial.print("Scanning I2C");
    Serial.print(channel + 1);
    Serial.println("...");

    switch(channel)
    {
    case 0 :
    case 1 :    Serial.println("Channel Not Active");   return(0);
    case 2 :    wire = &Wire;                           break;
    case 3 :    wire = &Wire1;                          break;
    }

    for(count=0,addr=1;addr<127;addr++)
    {
        wire->beginTransmission(addr);
        if(wire->endTransmission() == 0)
        {
            Serial.print("Device found at address ");
            Serial.println(addr,HEX);
            count++;
        }
    }
    switch(count)
    {
    case 0 :
        Serial.println("No devices found");
        break;
    case 1 :
        Serial.println("Just one device found");
        break;
    default :    
        Serial.print("Total of ");
        Serial.print(count);
        Serial.println(" devices found");
        break;
    }
    return(count);
}

void IIC::LocateDevices(void)
{
    for(unsigned char devidx=0;devidx<I2C_DEVICES;devidx++)
    {
        Serial.print(I2C_Table[devidx].Desc);    Serial.print(" (");
        Serial.print(I2C_Table[devidx].Chip);    Serial.print(") ");
        if(Close(Open(devidx)) == false)
        {
            Serial.print("NOT ");
        }
        Serial.println("Found");
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
