#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "WebClient.h"
#include "JsonParser.h"
#include "Display.h"
#include <ctime>
#include "IndoorSensors.h"
#include "Common.h"
#include  <map>

#define Nameof(x) #x


#define REQUEST_INTERVAL 600


typedef enum
{
  A,
  B,
  C,
  NOT_PRESSED,
} ButtonType_t;

typedef enum
{
  INFO,
  TEMPERATURE,
  AROUND,
  INDOOR,
  INDOOR_TEMP_PRECISE,
  VISIBLE_LIGHT_SENSOR,
  LIGHT,
  ERROR,
} DataType_t;

extern String location;
extern String real_temperature;
extern String feelslike_temperature;
extern String pressure;
extern String humidity;
extern String indoor_humidity;
extern String indoor_pressure;
extern String indoor_temperature;
extern String spectrum;
extern String light;

extern bool BME_ACTIVE;
extern bool AMS_ACTIVE;
extern bool BH_ACTIVE;

extern void OnButtonPress(ButtonType_t btn);
extern void Display_ShowData(DataType_t data);

#endif /* MAIN_H */
