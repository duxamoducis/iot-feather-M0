#include "IndoorSensors.h"

Adafruit_BME280 bme;

Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

sensors_event_t temp_event,
    pressure_event, humidity_event;

bool BME_ACTIVE = false;

//Adafruit_MCP9808 mcp;
//bool MCP_ACTIVE = false;
Adafruit_AS726x ams;
bool AMS_ACTIVE = false;
uint16_t sensorValues[AS726x_NUM_CHANNELS];


BH1750 bh;
bool BH_ACTIVE = false;
//float lux = bh.readLightLevel();

void BME280_Init()
{
     
    if (!bme.begin())
    {
        BME_ACTIVE = false;
        Serial.println();
        Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    }
    else
    {
        BME_ACTIVE = true;
        Serial.println();
        Serial.println("BME280 sensor is active!");
    }
}

float BME280_temperature()
{
    if (BME_ACTIVE)
    {
        bme_temp
            ->getEvent(&temp_event);
        return temp_event.temperature;
    }
    else
        return .0;
}

float BME280_pressure()
{
    if (BME_ACTIVE)
    {
        bme_pressure->getEvent(&pressure_event);
        return pressure_event.pressure;
    }
    else
        return .0;
}

float BME280_humidity()
{
    if (BME_ACTIVE)
    {

        bme_humidity->getEvent(&humidity_event);
        return humidity_event.relative_humidity;
    }
    else
        return .0;
}

void BME280_Read()
{
    BME280_Init();
    indoor_humidity = String(BME280_humidity());
    indoor_humidity.concat("%");
    indoor_temperature = String(BME280_temperature());
    indoor_temperature.concat(" *C");
    indoor_pressure = String(BME280_pressure());
    indoor_pressure.concat(" hPa");

    Serial.println("INDOOR MEASUREMENTS - BME280");
    Serial.println("Temperature:");
    Serial.println(BME280_temperature());
    Serial.println("Humidity:");
    Serial.println(BME280_humidity());
    Serial.println("Pressure:");
    Serial.println(BME280_pressure());
    Serial.println();
}
/*
void MCP9808_Init()
{
    if (!mcp.begin(0x18))
    {
        Serial.println(F("Could not find a valid MCP9808 sensor, check wiring!"));
    }
    else
    {
        mcp.setResolution(3);
        MCP_ACTIVE = true;
        Serial.println("MCP9808 sensor is active!");
    }
}

float MCP9808_temperature()
{
    if (MCP_ACTIVE)
    {
        mcp.wake();
        float temperature = mcp.readTempC();
        mcp.shutdown_wake(1);
        return temperature;
    }
    else
        return .0;
}
void MCP9808_Read()
{
    indoor_humidity = String();
    indoor_temperature = String(MCP9808_temperature());
    indoor_temperature.concat(" *C");
    indoor_pressure = String();
}
*/
void AS7262_Init()
{
     
    if (!ams.begin())
    {
        AMS_ACTIVE = false;
        Serial.println();
        Serial.println(F("Could not find a valid AS7262 sensor, check wiring!"));
    }
    else
    {
        AMS_ACTIVE = true;
        Serial.println();
        Serial.println("AS7262 sensor is active!");
    }
}
float AS7262_sensorvalue()
{
    if (AMS_ACTIVE)
    {
        //read the device temperature
        uint8_t temp = ams.readTemperature();

        //ams.drvOn(); //uncomment this if you want to use the driver LED for readings
        ams.startMeasurement(); //begin a measurement

        //wait till data is available
        bool rdy = false;
        while(!rdy){
        delay(5);
        rdy = ams.dataReady();
        }
        //ams.drvOff(); //uncomment this if you want to use the driver LED for readings

        //read the values!
        ams.readRawValues(sensorValues);
        //ams.readCalibratedValues(calibratedValues);

        Serial.print("Temp: "); Serial.print(temp);
        Serial.print(" Violet: "); Serial.print(sensorValues[AS726x_VIOLET]);
        Serial.print(" Blue: "); Serial.print(sensorValues[AS726x_BLUE]);
        Serial.print(" Green: "); Serial.print(sensorValues[AS726x_GREEN]);
        Serial.print(" Yellow: "); Serial.print(sensorValues[AS726x_YELLOW]);
        Serial.print(" Orange: "); Serial.print(sensorValues[AS726x_ORANGE]);
        Serial.print(" Red: "); Serial.print(sensorValues[AS726x_RED]);
        Serial.println();
        return temp;
    }
    else
    {   
        return 0;
    }
}


void AS7262_Read()
{
    AS7262_Init();
    indoor_temperature = String(AS7262_sensorvalue());
    indoor_temperature.concat(" *C");
    spectrum = "V:";
    spectrum.concat(sensorValues[AS726x_VIOLET]);
    spectrum.concat(" B:");
    spectrum.concat(sensorValues[AS726x_BLUE]);
    spectrum.concat(" G:");
    spectrum.concat(sensorValues[AS726x_GREEN]);
    spectrum.concat("\nY:");
    spectrum.concat(sensorValues[AS726x_YELLOW]);
    spectrum.concat(" O:");
    spectrum.concat(sensorValues[AS726x_ORANGE]);
    spectrum.concat(" R:");
    spectrum.concat(sensorValues[AS726x_RED]);

}


void BH1750_Init()
{
     
    if (!bh.begin())
    {
        BH_ACTIVE = false;
        Serial.println();
        Serial.println(F("Could not find a valid BH1750 sensor, check wiring!"));
    }
    else
    {
        BH_ACTIVE = true;
        Serial.println();
        Serial.println("BH1750 sensor is active!");
    }
}


float BH_light()
{
    if (BH_ACTIVE)
    {

        float lux = bh.readLightLevel();
        return lux;
    }
    else
        return .0;
}

void BH1750_Read()
{
    BH1750_Init();
    light = String(BH_light());
    light.concat(" lx");

    Serial.println("INDOOR MEASUREMENTS - BH1750");
    Serial.println("Light:");
    Serial.print(BH_light());
    Serial.println(" lx");
    Serial.println();
    
}
