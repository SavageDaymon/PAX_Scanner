#include "PAX_Includes.h"

IIC         I2C;
HotPins     GPIO;
TempSensor  Temp;

void PAX_Startup(void)
{
    delay(5000);

    Serial.println("====================================");
    Serial.println("PAX Scanner 0256");
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

void setup(void)
{
	Serial.begin(9600);
    PAX_Startup();
    I2C.Startup();
    Temp.Initialize();
}

#define MAX_CYCLE   50

void loop(void)
{
int         io[IO_COUNT];
float       temp;
static int  cycle = 0;

    GPIO.ReadPins(io);
    GPIO.CheckPins(io);

    cycle++; cycle %= MAX_CYCLE;
    if(cycle == 0)
    {
        Temp.ReadCurrent(temp);
        Serial.print("PAX Temperature: ");
        Serial.print(temp);
        Serial.print(" C (");
        Serial.print(temp*9/5+32);
        Serial.println(" F)");
    }

    delay(50);
}
