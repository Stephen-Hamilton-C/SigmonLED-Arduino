#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <FastLED.h>

namespace Config {
    /**
     * @brief Which pin your LED data wire is plugged into.
    */
    extern const uint8_t LED_PIN;
    /**
     * @brief How many LEDs are on your LED strip.
    */
    extern const uint16_t LED_COUNT;
    /**
     * @brief The chipset of your LED strip. Most common type is WS2801
    */
    // TODO: WS2811 and other chipsets need to fit in here somehow
    // const ESPIChipsets LED_TYPE = ESPIChipsets::WS2811; 
    /**
     * @brief The color order that your LED strip uses
    */
    extern const EOrder LED_COLOR_ORDER;
    /**
     * @brief The color correction to use for the LED strip
    */
    extern const LEDColorCorrection LED_COLOR_CORRECTION;

    /**
     * @brief How long to wait in milliseconds before timing out the connection.
    */
    extern const uint32_t CONNECTION_TIMEOUT;
    /**
     * @brief The desired baud rate for the hardware serial port
    */
    extern const uint32_t SERIAL_BAUD;
}

#endif
