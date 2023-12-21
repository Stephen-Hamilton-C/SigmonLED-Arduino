#include "irhandler.h"
#include <IRremote.h>
#include "irmapping.h"

IRrecv* irReceiver;

IRHandler::IRHandler(LEDController* controller) {
    _controller = controller;

    irReceiver = new IRrecv(IR_PIN);
    irReceiver->start();
}

bool IRHandler::isIdle() {
    return IrReceiver.isIdle();
}

void IRHandler::printInput(const uint32_t input) {
    if(!ECHO) return;
    switch(input) {
        case IRIN_1:
            Serial.println("IR: 1");
            break;
        case IRIN_2:
            Serial.println("IR: 2");
            break;
        case IRIN_3:
            Serial.println("IR: 3");
            break;
        case IRIN_4:
            Serial.println("IR: 4");
            break;
        case IRIN_5:
            Serial.println("IR: 5");
            break;
        case IRIN_6:
            Serial.println("IR: 6");
            break;
        case IRIN_7:
            Serial.println("IR: 7");
            break;
        case IRIN_8:
            Serial.println("IR: 8");
            break;
        case IRIN_9:
            Serial.println("IR: 9");
            break;
        case IRIN_0:
            Serial.println("IR: 0");
            break;
        case IRIN_COLOR:
            Serial.println("IR: *");
            break;
        case IRIN_MODE:
            Serial.println("IR: #");
            break;
        case IRIN_LEFT:
            Serial.println("IR: <");
            break;
        case IRIN_RIGHT:
            Serial.println("IR: >");
            break;
        case IRIN_UP:
            Serial.println("IR: ^");
            break;
        case IRIN_DOWN:
            Serial.println("IR: v");
            break;
        case IRIN_OK:
            Serial.println("IR: OK");
            break;
        case IRIN_REPEAT:
            Serial.println("IR: REPEAT");
            break;
        default:
            Serial.print("IR: Unknown: ");
            Serial.println(input, HEX);
            break;
    }
}

void IRHandler::loop() {
    if(_colorEditor) {
        uint64_t now = millis();
        if(now >= _nextFlashTimestamp) {
            if(_colorFlash) {
                _nextFlashTimestamp = now + EDITOR_INTERMITTENT_FLASH_PAUSE;
                _controller->setColor(_currentEditColor);
            } else {
                _nextFlashTimestamp = now + EDITOR_INTERMITTENT_FLASH_OFF;
                _controller->setColor(CRGB::Black);
            }

            _colorFlash = !_colorFlash;
        }
    }

    if(irReceiver->decode()) {
        if(_blinking) {
            irReceiver->resume();
            return;
        }

        if(irReceiver->decodedIRData.decodedRawData == IRIN_REPEAT) {
            if(millis() - _lastDataTimestamp >= IR_TIMEOUT) {
                irReceiver->resume();
                return;
            }
        } else {
            _lastInput = irReceiver->decodedIRData.decodedRawData;
        }
        _lastDataTimestamp = millis();
        _lastInputRepeat = irReceiver->decodedIRData.decodedRawData == IRIN_REPEAT;
        printInput(irReceiver->decodedIRData.decodedRawData);
        handleInput();
        irReceiver->resume();
    }
}

void IRHandler::handleInput() {
    if(!_on) {
        if(_lastInputRepeat) return;

        _on = true;
        _controller->setBrightness(_onBrightness);
        return;
    }

    digitalWrite(LED_BUILTIN, LOW);
    switch(_lastInput) {
        case IRIN_1:
            // 1
            handleDigit(1);
            break;
        case IRIN_2:
            // 2
            handleDigit(2);
            break;
        case IRIN_3:
            // 3
            handleDigit(3);
            break;
        case IRIN_4:
            // 4
            handleDigit(4);
            break;
        case IRIN_5:
            // 5
            handleDigit(5);
            break;
        case IRIN_6:
            // 6
            handleDigit(6);
            break;
        case IRIN_7:
            // 7
            handleDigit(7);
            break;
        case IRIN_8:
            // 8
            handleDigit(8);
            break;
        case IRIN_9:
            // 9
            handleDigit(9);
            break;
        case IRIN_0:
            // 0
            handleDigit(10);
            break;
        case IRIN_COLOR:
            // COLOR
            if(_colorEditor) {
                editEnd();
            }
            handleModeSwitch();
            break;
        case IRIN_MODE:
            // MODE
            handleSelect();
            break;
        case IRIN_LEFT:
            // LEFT
            handleSwitchValueType(-1);
            break;
        case IRIN_RIGHT:
            // RIGHT
            handleSwitchValueType(1);
            break;
        case IRIN_UP:
            // UP
            handleValueIncrement(1);
            break;
        case IRIN_DOWN:
            // DOWN
            handleValueIncrement(-1);
            break;
        case IRIN_OK:
            // OK
            if(_colorEditor) {
                editEnd();
            } else if(!_lastInputRepeat) {
                _onBrightness = _controller->getBrightness();
                if(_onBrightness == 0) {
                    _controller->setBrightness(255);
                    break;
                }
                _controller->setBrightness(0);
                _on = false;
            }
            break;
        default:
            digitalWrite(LED_BUILTIN, HIGH);
            break;
    }
}

void IRHandler::handleDigit(const uint8_t digit) {
    if(digit == 1) {
        _incrementMagnitude = 1;
    } else {
        _incrementMagnitude = (digit / (float)10) * MAX_INCREMENT;
    }
}

void IRHandler::handleValueIncrement(const int8_t direction) {
    if(_colorEditor) {
        switch(_editorState) {
            case EditorState::HUE: {
                _colorHue += direction * _incrementMagnitude;
                CRGB color = CRGB::Black;
                color.setHSV(_colorHue, 255, 255);
                _controller->setColor(color);
                _currentEditColor = color;
                break;
            }
            case EditorState::SATURATION: {
                int16_t newColorSat = _colorSat + direction * _incrementMagnitude;
                if(newColorSat > 255) {
                    newColorSat = 255;
                } else if(newColorSat < 0) {
                    newColorSat = 0;
                }
                _colorSat = newColorSat;
                CRGB color = CRGB::Black;
                color.setHSV(_colorHue, _colorSat, 255);
                _controller->setColor(color);
                _currentEditColor = color;
                break;
            }
        }
        return;
    }

    switch(_currentType) {
        case ValueType::BRIGHTNESS: {
            int16_t brightness = _controller->getBrightness();
            brightness += direction * _incrementMagnitude;
            if(brightness > 255) {
                brightness = 255;
            } else if(brightness < 2) {
                brightness = 2;
            }
            _controller->setBrightness(brightness);
            break;
        }
        case ValueType::PALETTE_TYPE: {
            // Disable held inputs
            if(_lastInputRepeat) break;

            PaletteConfig config = _controller->getPaletteConfig();
            PaletteType type = config.type;
            if(type <= 0 && direction < 0) {
                type = (PaletteType)PALETTETYPE_MAX;
            } else if(type >= PALETTETYPE_MAX && direction > 0) {
                type = (PaletteType)0;
            } else {
                type = (PaletteType)(type + direction);
            }

            _controller->setPalette(type);
            break;
        }
        case ValueType::DELAY: {
            PaletteConfig config = _controller->getPaletteConfig();
            int32_t delay = config.delay;
            delay += direction * -_incrementMagnitude;
            if(delay > 65535) {
                delay = 65535;
            } else if(delay < 0) {
                delay = 0;
            }
            _controller->setPaletteDelay(delay);
            break;
        }
        case ValueType::STRETCH: {
            PaletteConfig config = _controller->getPaletteConfig();
            int16_t stretch = config.stretch;
            stretch += direction;
            if(stretch > 255) {
                stretch = 255;
            } else if(stretch < 0) {
                stretch = 0;
            }
            _controller->setPaletteStretch(stretch);
            break;
        }
    }
}

void IRHandler::handleSwitchValueType(const int8_t direction) {
    // Disable held inputs
    if(_lastInputRepeat) return;

    if(_colorEditor) {
        switch(_editorState) {
            case EditorState::HUE: {
                if(direction > 0) {
                    editSaturation();
                }
                break;
            }
            case EditorState::SATURATION: {
                if(direction > 0) {
                    editEnd();
                } else {
                    editHue();
                }
                break;
            }
        }
        return;
    }

    if(_controller->getMode() != LEDController::Mode::PALETTE) return;

    if(_currentType <= 0 && direction < 0) {
        _currentType = (ValueType)VALUETYPE_MAX;
    } else if(_currentType >= VALUETYPE_MAX && direction > 0) {
        _currentType = (ValueType)0;
    } else {
        _currentType = (ValueType)(_currentType + direction);
    }
    blink(((uint8_t)_currentType)+1, 300);
}

void IRHandler::handleSelect() {
    // Disable held inputs
    if(_lastInputRepeat) return;

    if(_controller->getMode() == LEDController::Mode::PALETTE) {
        PaletteConfig config = _controller->getPaletteConfig();
        _controller->setPaletteBlending(!config.blending);
    } else if(!_colorEditor) {
        editStart();
    } else {
        editEnd();
    }
}

void IRHandler::handleModeSwitch() {
    // Disable held inputs
    if(_lastInputRepeat) return;

    if(_controller->getMode() == LEDController::Mode::COLOR) {
        _controller->setMode(LEDController::Mode::PALETTE);
    } else if(_controller->getMode() == LEDController::Mode::PALETTE) {
        _controller->setMode(LEDController::Mode::COLOR);
        _controller->setColor(_controller->getColor());
        _currentType = ValueType::BRIGHTNESS;
    }
}

void IRHandler::blink(const uint8_t times, const uint16_t interval) {
    if(_blinking) return;

    _blinking = true;
    if(digitalRead(LED_BUILTIN)) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(interval);
    }
    for(uint8_t i = 0; i < times; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(interval / 2);
        digitalWrite(LED_BUILTIN, LOW);
        delay(interval / 2);
    }
    _blinking = false;
}

void IRHandler::editStart() {
    _colorEditor = true;
    _colorFlash = false;
    if(_controller->getBrightness() < 16) {
        _controller->setBrightness(16);
    }
    editHue();
}

void IRHandler::editHue() {
    _blinking = true;
    _editorState = EditorState::HUE;
    _controller->setColor(CRGB::Black);
    _controller->forceUpdate();
    delay(EDITOR_OFF_FLASH);
    _controller->distributePalette(RainbowColors_p);
    _controller->forceUpdate();
    delay(EDITOR_ON_FLASH);
    _blinking = false;

    CRGB color = CRGB::Black;
    color.setHSV(_colorHue, 255, 255);
    _currentEditColor = color;
    _controller->setColor(color);
}

void IRHandler::editSaturation() {
    _blinking = true;
    _editorState = EditorState::SATURATION;
    _controller->setColor(CRGB::Black);
    _controller->forceUpdate();
    delay(EDITOR_OFF_FLASH);
    CRGB color = CRGB::Black;
    color.setHSV(_colorHue, 255, 255);
    _controller->setGradient(color, CRGB::White);
    _controller->forceUpdate();
    delay(EDITOR_ON_FLASH);
    _blinking = false;

    color.setHSV(_colorHue, _colorSat, 255);
    _currentEditColor = color;
    _controller->setColor(color);
}

void IRHandler::editEnd() {
    CRGB color = CRGB::Black;
    color.setHSV(_colorHue, _colorSat, 255);
    _controller->setColor(color);
    _colorEditor = false;
}
