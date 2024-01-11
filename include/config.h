#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <FastLED.h>

#define ECHO false

#define VERSION "3.1.0"

#define ENABLE_SERIAL_COMMANDS true
#define ENABLE_IR_INPUT false

/**
 * @brief What to send to serial after a connection times out.
 * If this is set to 0, ignore.
 */
#define TIMEOUT_MESSAGE "AT"

#define MESSAGE_BUFFER 128
/**
 * @brief Which pin your IR remote sensor is plugged into
 */
#define IR_PIN 7
/**
 * @brief Which pin your LED data wire is plugged into.
*/
#define LED_PIN 6
/**
 * @brief How many LEDs are on your LED strip.
*/
#define LED_COUNT 200 //81
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
 * @brief How long to wait in milliseconds before timing out the Serial connection.
*/
#define CONNECTION_TIMEOUT 180000

/**
 * @brief How long to wait for a response to command verification
 * before disregarding the command.
*/
#define MESSAGE_TIMEOUT 5000
/**
 * @brief The maximum time in milliseconds between IR pulses to ignore IRIN_REPEAT messages
*/
#define IR_TIMEOUT 200
/**
 * @brief The increment magnitude for certain IR inputs
*/
#define IR_INCREMENT 5
/**
 * @brief The desired baud rate for the hardware serial port
 * Send `AT+BAUD1` to go into 19200 baud mode on HM10 BLE modules.
 * It's recommended to set the baud on the module before connecting it to the Arduino.
 * Otherwise, HM10s default to 9600
*/
#define SERIAL_BAUD 9600 //19200

#endif
