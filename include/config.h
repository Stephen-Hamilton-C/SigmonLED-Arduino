#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <FastLED.h>

/**
 * @brief Which pin your LED data wire is plugged into.
*/
#define LED_PIN 6
/**
 * @brief How many LEDs are on your LED strip.
*/
#define LED_COUNT 8 //81
/**
 * @brief The chipset of your LED strip. Most common type is WS2811
*/
#define LED_TYPE WS2811
/**
 * @brief The color order that your LED strip uses
*/
#define LED_COLOR_ORDER EOrder::GRB
/**
 * @brief The color correction to use for the LED strip
*/
#define LED_COLOR_CORRECTION LEDColorCorrection::TypicalLEDStrip

/**
 * @brief How long to wait in milliseconds before timing out the connection.
*/
#define CONNECTION_TIMEOUT 180000
/**
 * @brief The desired baud rate for the hardware serial port
 * For HM10 BLE modules, to go into 115200 baud mode, send `AT+BAUD4`.
 * It's recommended to set the baud on the module before connecting it to the Arduino.
 * Otherwise, HM10s default to 9600
*/
#define SERIAL_BAUD 115200 //9600 

#endif