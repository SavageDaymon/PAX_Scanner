#include "PAX_Includes.h"

IIC         I2C;
HotPins     GPIO;
TempSensor  Temp;
RTC         Time;

char ucs(char ch)
{
    return((ch >= 'a' && ch <= 'z') ? (ch - ('a' - 'A')) : ch);
}

void PAX_Startup(void)
{
    delay(5000);

    Serial.println("====================================");
    Serial.println("PAX Scanner 0288");
    Serial.println("====================================");

	GPIO.SetupPins();

    GPIO.DoToggle(LEDOUT,HIGH,250,LOW);

	Serial.println(F("Enabling Power Rails"));
    GPIO.DoToggle(POWEREN,LOW,4000,HIGH);
	GPIO.SetPinHigh(LEDOUT);

	Serial.println(F("Reseting I2C Multiplexer"));
    GPIO.DoToggle(I2C3_MUX_RST_N,LOW,50,HIGH);

	Serial.println("Enabling LED Driver");
    GPIO.DoToggle(I2C3A_RST_N,LOW,50,HIGH);

	Serial.println("Enabling Temperature Sensor");
    GPIO.DoToggle(I2C3B_RST_N,LOW,50,HIGH);

	delay(125);
}

inline float ConvertCtoF(float temp)
{
    return(temp * 9.0/5.0 + 32.0);
}

void DisplayTemperature(void)
{
float   temp;

    Temp.ReadCurrent(temp);
    Serial.print("PAX Temperature: ");
    Serial.print(temp);
    Serial.print(" C (");
    Serial.print(ConvertCtoF(temp));
    Serial.println(" F)");
}

void DisplayTime(void)
{
RTC_Time    rtime;

    if(Time.ReadTime(rtime))
    {
        Time.DisplayTime(rtime);
    }
}

void CheckForCommands(void)
{
char    buffer[80];
int     bytes = Serial.available();

    if(bytes)
    {
        Serial.readBytes(buffer,bytes);
        switch(ucs(*buffer))
        {
        case 'I' :
            DisplayTime();
            DisplayTemperature();
            break;
        case '1' :  I2C.ScanAll(I2C1);  break;
        case '2' :  I2C.ScanAll(I2C2);  break;
        case '3' :  I2C.ScanAll(I2C3);  break;
        case '4' :  I2C.ScanAll(I2C4);  break;
        }
    }
}

void setup(void)
{
	Serial.begin(9600);
    PAX_Startup();
    I2C.Startup();
    Temp.Initialize();
}

void loop(void)
{
int io[IO_COUNT];

    GPIO.ReadPins(io);
    GPIO.CheckPins(io);
    CheckForCommands();
    delay(50);
}
