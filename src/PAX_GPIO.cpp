#include "PAX_Includes.h"

int     sensor[IO_COUNT];

struct
{
	const char *	Name;
	int			    Type;

} IO_Info[IO_COUNT] =	{	//	Name				Type				Pin
							{    "SPIA0",			OUTPUT	    },	//	D0   --  RX1 CS1   CRX2  --          PMW   P1-2  SPIA0
							{    "I2C3_MUX_RST_N",	OUTPUT	    },	//	D1   --  TX1 MISO1 CTX2  --          PMW   P1-3  I2C3_MUX_RST_N
							{    "MC1INTR",			INPUT	    },	//	D2   --  --  --    --    OUT2        PMW   P1-4  MC1INTR
							{    "MC2PSCMP",		INPUT	    },	//	D3   --  --  --    --    LRCLK2      PMW   P1-5  MC2PSCMP
							{    "MC3PSCMP",		INPUT	    },	//	D4   --  --  --    --    BCLK2       PMW   P1-6  MC3PSCMP
							{    "MC4RSTN",			INPUT	    },	//	D5   --  --  --    --    IN2         PMW   P1-7  MC4RSTN
							{    "MC3INTRN",		INPUT	    },	//	D6   --  --  --    --    OUT1D       PMW   P1-8  MC3INTRN
							{    "MC4TRGTR",		INPUT	    },	//	D7   --  RX2 --    --    OUT1A       PMW   P1-9  MC4TRGTR
							{    "MC4INTR",			INPUT	    },	//	D8   --  TX2 --    --    IN1         PMW   P1-10 MC4INTR
							{    "LBTNSIGN",		INPUT	    },	//	D9   --  --  --    --    OUT1C       PMW   P1-11 LBTNSIGN
							{    "ECSPI2 SS0",		RESERVED    },	//	D10  --  --  CS    --    MQSR        PMW   P1-12 ECSPI2 SS0
							{    "ECSPI2 MOSI",		RESERVED    },	//	D11  --  --  MOSI  CTX1  --          PMW   P1-13 ECSPI2 MOSI
							{    "ECSPI2 MISO",		RESERVED    },	//	D12  --  --  MISO  --    MQSL        PMW   P1-14 ECSPI2 MISO
							{    "ECSPI2 SCLK",		RESERVED    },	//	D13  LED --  SCK   --    --          PMW   P2-14 ECSPI2 SCLK
							{    "SHUTTLEENTER",	INPUT  	    },	//	D14  A0  TX3 --    --    S/PDIF OUT  PMW   P2-13 SHUTTLEENTER
							{    "STAGEEXIT",		INPUT	    },	//	D15  A1  RX3 --    --    S/PDIF IN   PMW   P2-12 STAGEEXIT
							{    "I2C4 SCL",		RESERVED	},	//	D16  A2  RX4 --    --    SCL1        --    P2-11 I2C4 SCL
							{    "I2C4 SDA",		RESERVED    },	//	D17  A3  TX4 --    --    SDA1        --    P2-10 I2C4 SDA
							{    "I2C3 SDA",		RESERVED	},	//	D18  A4  --  --    --    SDA         PMW   P2-9  I2C3 SDA
							{    "I2C3 SCL",		RESERVED	},	//	D19  A5  --  --    --    SCL         PMW   P2-8  I2C3 SCL
							{    "STAGETRANS",		INPUT	    },	//	D20  A6  TX5 --    --    LRCLK1      --    P2-7  STAGETRANS
							{    "STAGEOVRSHT",		INPUT	    },	//	D21  A7  RX5 --    --    BCLK1       --    P2-6  STAGEOVRSHT
							{    "STAGEEND",		INPUT	    },	//	D22  A8  --  --    CTX1  --          PMW   P2-5  STAGEEND
							{    "STAGEENTER",		INPUT	    },	//	D23  A9  --  --    CRX1  MCLK1       PMW   P2-4  STAGEENTER
							{    "RBTNSIGN",		INPUT	    },	//	D24  A10 TX6 --    --    SCL2        PMW   P1-16 RBTNSIGN
							{    "MC2INTRN",		INPUT	    },	//	D25  A11 RX6 --    --    SDA2        PMW   P1-17 MC2INTRN
							{    "INFEEDROLLSGTST", INPUT	    },	//	D26  A12 --  MOSI1 --    --          --    P1-18 INFEEDROLLSGTST
							{    "INSERTSGTST",		INPUT	    },	//	D27  A13 --  SCK1  --    --          --    P1-19 INSERTSGTST
							{    "PUSHDWNSGTST",	INPUT	    },	//	D28  --  RX7 --    --    --          PMW   P1-20 PUSHDWNSGTST
							{    "EXITROLLSGTST",	INPUT	    },	//	D29  --  TX7 --    --    --          PMW   P1-21 EXITROLLSGTST
							{    "EJECTSGTST",		INPUT	    },	//	D30  --  --  --    CRX3  --          --    P1-22 EJECTSGTST
							{    "GATESGTST",		INPUT	    },	//	D31  --  --  --    CTX3  --          --    P1-23 GATESGTST
							{    "INFEEDEXIT",		INPUT	    },	//	D32  --  --  --    --    --          --    P1-24 INFEEDEXIT
							{    "MC1TRGTR",		INPUT	    },	//	D33  --  --  --    --    MCLK2       PMW   P2-24 MC1TRGTR
							{    "OUTFEEDTRAY",		INPUT	    },	//	D34  --  RX8 --    --    --          --    P2-23 OUTFEEDTRAY
							{    "INFEEDTRAY",		INPUT	    },	//	D35  --  TX8 --    --    --          --    P2-22 INFEEDTRAY
							{    "SPIA3",			OUTPUT	    },	//	D36  --  --  CS    --    --          PMW   P2-21 SPIA3
							{    "SPIA2",			OUTPUT	    },	//	D37  --  --  CS    --    --          PMW   P2-20 SPIA2
							{    "SPIA1",			OUTPUT	    },	//	D38  A14 --  CS1   --    IN1         --    P2-19 SPIA1
							{    "SHUTTLEACC",		INPUT	    },	//	D39  A15 --  MISO1 --    OUT1A       --    P2-18 SHUTTLEACC
							{    "MC1RSTN",			INPUT	    },	//	D40  A16 --  --    --    --          --    P2-17 MC1RSTN
							{    "POWEREN",		    OUTPUT	    },	//	D41  A17 --  --    --    --          --    P2-16 POWEREN
							{    "I2C3ARSTN",		OUTPUT	    },	//	D42  --  --  --    --    --          --    uSD-1 I2C3ARSTN
							{    "I2C3BRSTN",		OUTPUT	    },	//	D43  --  --  --    --    --          --    uSD-2 I2C3BRSTN
							{    "MAINCOVER",		INPUT	    },	//	D44  --  --  --    --    --          --    uSD-3 MAINCOVER
							{    "INPUTSP1",		INPUT	    },	//	D45  --  --  --    --    --          --    uSD-4 INPUTSP1
							{    "INPUTSP2",		INPUT	    },	//	D46  --  --  --    --    --          --    uSD-5 INPUTSP2
							{    "LHSIDEPLATE",		INPUT	    },	//	D47  --  --  --    --    --          --    uSD-6 LHSIDEPLATE
							{    "RHSIDEPLATE",		INPUT	    },	//	D48  --  --  --    --    --          --    Mem1-1 RHSIDEPLATE
							{    "MC5M1SGTST",		INPUT	    },	//	D49  --  --  --    --    --          --    Mem1-2 MC5M1SGTST
							{    "MC5M2SGTST",		INPUT	    },	//	D50  --  --  --    --    --          --    Mem1-3 MC5M2SGTST
							{    "MC5M3SGTST",		INPUT	    },	//	D51  --  --  --    --    --          --    Mem1-4 MC5M3SGTST
							{    "MC5INTR",		    INPUT	    },	//	D52  --  --  --    --    --          --    Mem2-1 MC5INTR
							{    "MC5PSCMP",		INPUT	    },	//	D53  --  --  --    --    --          --    Mem2-2 MC5PSCMP
							{    "SPARE",		    INPUT	    },	//	D54  --  --  --    --    --          --    Mem2-3 SPARE
						};

void HotPins::SetPinLow(int pin)
{
    digitalWrite(pin, LOW);
}

void HotPins::SetPinHigh(int pin)
{
    digitalWrite(pin, HIGH);
}

void HotPins::ReadPins(int * array)
{
    for(int pin=0;pin<IO_COUNT;pin++)
    {
        switch(IO_Info[pin].Type)
        {
        case INPUT :      array[pin] = digitalRead(pin);  break;
        case RESERVED :
        case OUTPUT :     array[pin] = 0;                 break;
        }
    }
}

void HotPins::SetupPins(void)
{
    for(int pin=0;pin<IO_COUNT;pin++)
    {
        switch(IO_Info[pin].Type)
        {
        case INPUT :
        case OUTPUT :
            pinMode(pin,IO_Info[pin].Type);
            break;
        case RESERVED :
            break;
        }
    }

	ReadPins(sensor);                                           // Read Initial Input Pin States
}

void HotPins::CheckPins(int * array)
{
	for(int pin=0;pin<IO_COUNT;pin++)
	{
        if(IO_Info[pin].Type == INPUT)
        {
    		if(sensor[pin] != array[pin])
		    {
    			sensor[pin] = array[pin];
			    Serial.print('D');
			    Serial.print(pin);
			    Serial.print('(');
			    Serial.print(IO_Info[pin].Name);
			    Serial.println(')');
		    }
        }
	}
}

void HotPins::DoToggle(int pin,int first,int ms, int second)
{
    digitalWrite(pin,first);
    delay(ms);
    digitalWrite(pin,second);
}

