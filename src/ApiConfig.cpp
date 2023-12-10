#include "ApiConfig.h"
#include "WebClient.h"
#include <stdlib.h>

char host_name[] = "api.openweathermap.org";
String weather_api = "https://api.openweathermap.org/data/2.5/weather";

String req_base = "?appid=" + String(API_KEY) + "&units=metric";

String query1 = "&lat=" + String(GDA_LAT) + "&lon=" + String(GDA_LON);
String query2 = "&lat=" + String(WAR_LAT) + "&lon=" + String(WAR_LON);
String query3 = "&lat=" + String(KRA_LAT) + "&lon=" + String(KRA_LON);

/*API calls*/
String requestGda = HTTP_METHOD + weather_api + req_base + query1 + " HTTP/1.1";
String requestWaw = HTTP_METHOD + weather_api + req_base + query2 + " HTTP/1.1";
String requestKra = HTTP_METHOD + weather_api + req_base + query3 + " HTTP/1.1";
