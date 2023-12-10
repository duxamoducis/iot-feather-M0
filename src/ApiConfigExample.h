#ifndef APICONFIG_H
#define APICONFIG_H

#include "Main.h"

/*
 * Example configuration file to access OpenWeather API
 * API_KEY: Key to access the API calls
 * API call to get CITY_LAT, CITY_LON: Geograpical coordinates of target city
 *    See:
 *         https://api.openweathermap.org/data/2.5/weather?q={city name}&appid={API key}
 * 
 *    See:  https://openweathermap.org/api/geocoding-api#direct_name
 *          https://openweathermap.org/current#geo
 *
 */

#define API_KEY "API_KEY"

/* LONDON */
//#define CITY_LAT 51.5085
//#define CITY_LON -0.1257

/* GDANSK*/
#define GDA_LAT 54.3521
#define GDA_LON 18.6464
/* WARSZAWA */
#define WAR_LAT 52.2298
#define WAR_LON 21.0118
/*KRAKOW*/
#define KRA_LAT 50.0833
#define KRA_LON 19.9167

#define HTTP_METHOD "GET "

extern char host_name[];
extern String weather_api;
extern String req_base;


extern String query1;
extern String query2;

extern String requestWaw;
extern String requestGda;
extern String requestKra;


#endif /* APICONFIG_H */
