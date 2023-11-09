#ifndef INDOORSENSORS_H
#define INDOORSENSORS_H

#include "Main.h"

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MCP9808.h>
#include <Adafruit_AS726x.h>
#include <BH1750.h>

extern Adafruit_BME280 bme;
//extern Adafruit_MCP9808 mcp;
extern Adafruit_AS726x ams;
extern BH1750 bh;


extern void BME280_Init();
extern float BME280_temperature();
extern float BME280_pressure();
extern float BME280_humidity();
extern void BME280_Read();

extern void MCP9808_Init();
extern float MCP9808_temperature();
extern void MCP9808_Read();

extern void AS7262_Init();
extern float AS7262_sensorvalue();
extern void AS7262_Read();

extern void BH1750_Init();
extern float BH_light();
extern void BH1750_Read();

#endif /* INDOORSENSORS_H */