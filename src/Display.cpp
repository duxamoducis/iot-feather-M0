#include "Display.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);


uint8_t Display_Init(void){

  Display_InitScreen();
  Display_Clear();
  Display_InitIO();
  Display_InitText();

  return 0;
}

void Display_InitScreen()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.display();
}

void Display_InitIO()
{
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
}

void Display_print(String text){
    Display_Clear();
    display.println(text);
    display.display();
}

void Display_Clear()
{
  display.clearDisplay();
  display.display();
  display.setCursor(0, 0);
}

void Display_InitText()
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void Display_WiFiMessage()
{
  Display_Clear();
  display.println("WiFi connection...");
  display.display();
}

void Display_ApiMessage()
{
  Display_Clear();
  display.println("Host connection...");
  display.display();
}
void Display_FetchData()
{
  display.println("Fetching data...");
  display.display();
}

void Display_SuccessMessage()
{
  display.println("Response OK");
  display.display();
}

void Display_FailedMessage()
{
  Display_Clear();
  display.println("Request failed.");
  display.display();
}