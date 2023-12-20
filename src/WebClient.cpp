#include "WebClient.h"
#include "Display.h"
#include "String.h"


int city = 0;
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;
bool req_error = false;

String publicIP = "";
String lat = "";
String lon = "";

int port = 80;

int status = WL_IDLE_STATUS;

WiFiClient client;

void PrintWiFiStatus();


void WiFiSetup()
{
  WiFi.setPins(WIFI_SHIELD_PINS);

  /* Check if shield is present */
  if (WiFi.status() == WL_NO_SHIELD)
  {
    #if DEBUG_PRINT_STATUS == 1u
    Serial.println("WiFi Shield not present!");
    #endif
    while (true)
    {
      /* Infinite loop, do not continue if no shield */
    }
  }

  /* Attempt to initialize connection */
  if (WiFi.status() != WL_CONNECTED)
  {
    #if DEBUG_PRINT_STATUS == 1u
    Serial.println("\nAttempting connection to: ");
    Serial.println(ssid);
    #endif
    Display_WiFiMessage();

    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  #if DEBUG_PRINT_STATUS == 1u
  Serial.println("\nConnected to:");
  #endif
  display.println("WiFi connected.");
  display.display();
  PrintWiFiStatus();
}

void PrintWiFiStatus()
{
  long rssi = WiFi.RSSI();
#if DEBUG_PRINT_STATUS == 1u
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Signal (RSSI): ");
  Serial.print(rssi);
  Serial.println("dBm");
#endif

}


void RequestProcess(String request, String location){
  
  client.println(request); 
 
  #if DEBUG_PRINT_REQUESTS == 1u
  Serial.print("DEBUG_" + location + ": ");
  Serial.println(request);
  #endif

}

void ApiRequest(int i)
{
  city = i;
  String requestCurrent = HTTP_METHOD + weather_api + req_base + "&lat=" + lat + "&lon=" + lon + " HTTP/1.1";
  client.setTimeout(10000); /* 10s connection and request timeout */
  #if DEBUG_PRINT_STATUS == 1u
  Serial.println("\nAttempting connection...");
  #endif
  Display_ApiMessage();

  if (client.connect(host_name, HTTP_PORT))
  {
    #if DEBUG_PRINT_STATUS == 1u
    Serial.println("\nConnected to " + String(host_name));
    #endif
    Display_FetchData();
    /* City order */
    if(city == 1)
    {
      RequestProcess(requestGda, "DEBUG_GDA: ");

    }
    else if (city == 2)
    {
      RequestProcess(requestWaw, "DEBUG_WAR: ");

    }
    else if (city == 3)
    {
      RequestProcess(requestKra, "DEBUG_KRA: ");
    }
    else if (city == 4){
      RequestProcess(requestCurrent, "DEBUG_Current: ");
      city = 0;

    }
    else;

    client.println("Host: " + String(host_name));
    client.println("Connection: close");
    client.println();
   

    /* Error handling */
    if (client.println() == 0)
    {
      #if DEBUG_PRINT_STATUS == 1u
      Serial.println("Request failed.");
      #endif
      req_error = true;
      return;
    }

    char res_status[32] = {0};
    char http_200[] = "HTTP/1.1 200 OK";
    client.readBytesUntil('\r', res_status, sizeof(res_status));
    if (strcmp(res_status, http_200) != 0)
    {
      #if DEBUG_PRINT_STATUS == 1u
      Serial.print("Unhandled response: ");
      Serial.println(res_status);
      #endif
      req_error = true;
      return;
    }

    char end_of_headers[] = "\r\n\r\n";
    if (!client.find(end_of_headers))
    {
      #if DEBUG_PRINT_STATUS == 1u
      Serial.println("Response invalid.");
      #endif
      req_error = true;
      return;
    }
  }
  else
  {
    #if DEBUG_PRINT_STATUS == 1u
    Serial.println("Connection failed.");
    #endif
    req_error = true;
  }
}
/*
  Get IPv4 adress from exnternal API and assign it to publicIP
*/
void IpRequest(){
  client.connect("wtfismyip.com", 80);
  client.println("GET /text HTTP/1.1");
  client.println("Host: wtfismyip.com");
  client.println("Connection: close");
  client.println();
  bool ipStart = false;
  int newLineCount = 0; // Variable to count the number of newline characters
  while(client.connected()) {
    while(client.available()) {
      char c = client.read();
      if(c == '\n'){
        newLineCount++; // Increment the count when a newline character is encountered
        if(newLineCount == 8){ // Start writing only when IPv4 adress appear
          ipStart = true; // Start recording after the 8th newline characten
        }
      }
      if(ipStart && c!='\n'){
        publicIP += c; // Append each character of the adress to the publicIP variable
      }
    }
  }
  client.stop();
}
/*
  Get longitude and latitude from given IP adress
*/
void GeoRequest(){
  String geo_request = "GET /json/" + publicIP + " HTTP/1.1";
  client.connect("ip-api.com", HTTP_PORT);
  
  #if DEBUG_PRINT_REQUESTS == 1u
  Serial.println("DRUKUJE API:");
  Serial.println(geo_request);
  #endif

  client.println(geo_request);
  client.println("Host: ip-api.com");
  client.println("Connection: close");
  client.println();

  String buffer = "";
  bool latFound = false;
  bool lonFound = false;

  while(client.connected()) {
    while(client.available()) {
      char ch = client.read();
      buffer += ch; // Append each character to the buffer variable

      if (buffer.endsWith("lat\":")) {
        latFound = true;
        buffer = ""; // Reset the buffer
      } else if (buffer.endsWith("lon\":")) {
        lonFound = true;
        buffer = ""; // Reset the buffer
      }

      if ((latFound && lat.length() < 7) && ch != ':' ) {
        lat += ch;
      } else if (lonFound && lon.length() < 7 && ch != ':') {
        lon += ch;
      }
      // DEBUG
      //Serial.print(ch);
    }
  }
  /*DEBUG*/
  /*
  Serial.print("lat: ");
  Serial.print(lat);
  Serial.print("lon: ");
  Serial.print(lon);

  Serial.print("current_lat: ");
    client.stop();

    // Print the public IP
    Serial.print("Public IP: ");
    Serial.println(publicIP);*/

}





