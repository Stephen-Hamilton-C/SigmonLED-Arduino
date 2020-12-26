#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    8 //300
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
int currentColor[3] {255, 255, 255};
int brightness = 16;
int delayTime = 10;
int lastDelayTime = 0;
int serialNumber = 0;

CRGBPalette16 currentPalette;
TBlendType currentBlending;

enum MODE {
  REDGREENBLUE,
  PALATTE,
  SLEEP
};
MODE currentMode = REDGREENBLUE;

enum SERIALSTATE {
  COMMAND,
  BRIGHTCOMMAND,
  DELAYCOMMAND,
  PALATTECOMMAND,
  BLENDCOMMAND,
  NUMBER
};
SERIALSTATE currentState = COMMAND;

enum SERIALNUMPURPOSE {
  RED,
  GREEN,
  BLUE,
  BRIGHT,
  DELAY
};
SERIALNUMPURPOSE serialNumPurpose = RED;

enum SERIALNUMSTATE {
  THOUSANDS,
  HUNDREDS,
  TENS,
  ONES,
  FIN
};
SERIALNUMSTATE currentNumState = FIN;

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  Wake();
  Serial.println("Setup Finished");
  Serial.print("\nREADY:");
}

int charToInt(char inChar) {
  switch (inChar) {
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    default: return 0;
  }
}

void ReadSerialNum(int rxInt){
  switch(currentNumState){
    case THOUSANDS:
      serialNumber = 1000 * rxInt;
      currentNumState = HUNDREDS;
      Serial.print("\nHundreds");
      break;
    case HUNDREDS:
      serialNumber += 100 * rxInt;
      currentNumState = TENS;
      Serial.print("\nTens");
      break;
    case TENS:
      serialNumber += 10 * rxInt;
      currentNumState = ONES;
      Serial.print("\nOnes");
      break;
    case ONES:
      serialNumber += rxInt;
      currentNumState = FIN;
      Serial.print("\nFin");
      break;
  }
}

void Wake(){
  delayTime = 50;
  currentMode = REDGREENBLUE;
  currentColor[0] = 255;
  currentColor[1] = 255;
  currentColor[2] = 255;
  brightness = 255;
}

void ReadSerial() {
  if (Serial.available()) {
    char rxChar = Serial.read();
    //Serial.print("RX: ");
    //Serial.println(rxChar);

    if (rxChar == 'x') { //Reset
      currentState = COMMAND;
      delayTime = lastDelayTime;
      Serial.print("\nREADY:");
      return;
    }

    switch (currentState) {
      case COMMAND: {
          lastDelayTime = delayTime;
          delayTime = 0;
          switch (rxChar) {
            case 'r': {
                currentState = NUMBER;
                currentNumState = HUNDREDS;
                serialNumber = 0;
                serialNumPurpose = RED;
                Serial.print("\nSuccess");
                Serial.print("\nHundreds");
                break;
              }
            case 'g': {
                currentState = NUMBER;
                currentNumState = HUNDREDS;
                serialNumber = 0;
                serialNumPurpose = GREEN;
                Serial.print("\nSuccess");
                Serial.print("\nHundreds");
                break;
              }
            case 'b': {
                currentState = NUMBER;
                currentNumState = HUNDREDS;
                serialNumber = 0;
                serialNumPurpose = BLUE;
                Serial.print("\nSuccess");
                Serial.print("\nHundreds");
                break;
              }
            case 'p': {
                currentState = PALATTECOMMAND;
                Serial.print("\nSuccess");
                break;
              }
            case 'B': {
                currentState = NUMBER;
                currentNumState = HUNDREDS;
                serialNumber = 0;
                serialNumPurpose = BRIGHT;
                Serial.print("\nSuccess");
                Serial.print("\nHundreds");
                break;
              }
            case 'd': {
                currentState = NUMBER;
                currentNumState = THOUSANDS;
                serialNumPurpose = DELAY;
                Serial.print("\nSuccess");
                Serial.print("\nThousands");
                break;
              }
            case 'S': {
                delayTime = 1000;
                brightness = 0;
                currentMode = SLEEP;
                Serial.print("\nSuccess");
                break;
            }
            case 'W': {
                Wake();
                Serial.print("\nSuccess");
                break;
            }
            default:
              Serial.print("\nUnrecognized Command");
              Serial.print("\nREADY:");
              break;
          }
          break;
        }
      case NUMBER: {
        ReadSerialNum(charToInt(rxChar));
        if(currentNumState == FIN){
          switch(serialNumPurpose){
            case RED:
              currentColor[0] = serialNumber;
              break;
            case GREEN:
              currentColor[1] = serialNumber;
              break;
            case BLUE:
              currentColor[2] = serialNumber;
              break;
            case BRIGHT:
              brightness = serialNumber;
              break;
            case DELAY:
              lastDelayTime = serialNumber;
              break;
          }
          delayTime = lastDelayTime;
          currentState = COMMAND;
          Serial.print("\nREADY:");
        }
        break;
      }
      case PALATTECOMMAND: {
          switch (rxChar) {
            case 'R': {
                currentPalette = RainbowStripeColors_p;
                Serial.print("\nSuccess");
                break;
              }
            case 'c': {
                currentPalette = CloudColors_p;
                Serial.print("\nSuccess");
                break;
              }
            case 'p': {
                currentPalette = PartyColors_p;
                Serial.print("\nSuccess");
                break;
              }
            case 'o': {
                currentPalette = OceanColors_p;
                Serial.print("\nSuccess");
                break;
              }
            case 'l': {
                currentPalette = LavaColors_p;
                Serial.print("\nSuccess");
                break;
              }
            case 'f': {
                currentPalette = ForestColors_p;
                Serial.print("\nSuccess");
                break;
              }
            default: {
                currentPalette = RainbowColors_p;
                Serial.print("\nSuccess");
                break;
              }
          }
          currentState = BLENDCOMMAND;
          break;
        }
      case BLENDCOMMAND: {
          switch (rxChar) {
            case 'l': {
                currentBlending = LINEARBLEND;
                break;
              }
            default: {
                currentBlending = NOBLEND;
                break;
              }
          }
          currentMode = PALATTE;
          currentState = COMMAND;
          delayTime = lastDelayTime;
          Serial.print("\nREADY:");
          break;
        }
    }
  }
}

void RGBMode() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(currentColor[0], currentColor[1], currentColor[2]);
  }
}

void PalatteMode(uint8_t colorIndex) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
    colorIndex += 3;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  ReadSerial();

  static uint8_t startIndex = 0;
  startIndex++;

  switch (currentMode) {
    case REDGREENBLUE:
      RGBMode();
      break;
    case PALATTE:
      PalatteMode(startIndex);
      break;
  }

  FastLED.setBrightness(brightness);
  FastLED.show();
  FastLED.delay(delayTime);
}
