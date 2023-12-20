#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "Main.h"
#include <SPI.h>
#include <WiFi101.h>
#include "WifiConfig.h"
#include "ApiConfig.h"

#define HTTP_PORT 80

/* WiFi Client */
extern WiFiClient client;
extern bool req_error;

/*  Current latitude and longtitude*/
extern String lat;
extern String lon;

/* Setup WiFi */
extern void WiFiSetup();

/* Printing WiFi Status */
extern void PrintWiFiStatus();

/* API Call */
extern void ApiRequest(int i);
extern void IpRequest();
extern void GeoRequest();

#endif /* WEBCLIENT_H */