#ifndef DISPLAY_H
#define DISPLAY_H

#include "Main.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

extern Adafruit_SSD1306 display;

/* Initialize the display */
extern void Display_InitScreen();
extern void Display_InitIO();
uint8_t Display_Init(void);

/* Clear Display */
extern void Display_Clear();

/* Set Text Style */
extern void Display_InitText();

/* Connection messages */
extern void Display_WiFiMessage();
extern void Display_ApiMessage();
extern void Display_FetchData();
extern void Display_SuccessMessage();
extern void Display_FailedMessage();

/* Display formatted data */
void Display_ShowData();
void Display_print(String);



#endif /* DISPLAY_H */