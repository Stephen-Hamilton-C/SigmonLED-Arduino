#include "config.h"

namespace Config {
    const uint8_t LED_PIN = 8;
    const uint16_t LED_COUNT = 81;
    const EOrder LED_COLOR_ORDER = EOrder::GRB;
    const LEDColorCorrection LED_COLOR_CORRECTION = LEDColorCorrection::TypicalLEDStrip;

    const uint32_t CONNECTION_TIMEOUT = 180000;
    const uint32_t SERIAL_BAUD = 9600;
}
