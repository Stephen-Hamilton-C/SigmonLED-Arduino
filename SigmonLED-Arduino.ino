#include <FastLED.h>

//Constants
#define LED_PIN 3
#define NUM_LEDS 8 //300
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

//Timer
unsigned long delayStart = 0;
/**
 * @brief Ignores the next delay on the mode state machine. This allows setting changes to instantly take effect
 */
bool delayBypass = false;

//LED settings
CRGB leds[NUM_LEDS];
uint8_t currentColor[3]{255, 255, 255};
uint8_t brightness = 16;

//Stored number while decoding hex input
uint8_t serialNumber = 0;

//Custom Palette
uint8_t paletteRed = 0;
uint8_t paletteGreen = 0;
uint8_t paletteBlue = 0;
uint8_t paletteIndexColorsMade = 0;
uint8_t paletteColorsMade = 0;
CRGB paletteBuffer[16];
CRGBPalette16 customPalette;

//Palette settings
unsigned int delayTime = 10;
uint8_t paletteStretch = 3;
CRGBPalette16 currentPalette;
TBlendType currentBlending;

/**
 * @brief The mode that the LEDs are in.
 * REDGREENBLUE: one singular static color across the entire strip.
 * PALETTE: have a 16-color palette pulse across the strip.
 * SOLIDPALETTE: have a 16-color palette change color across the entire strip.
 * SLEEP: Put the system into a low-power mode and turn off the LEDs.
 */
enum MODE {
	REDGREENBLUE,
	PALETTE,
	SOLIDPALETTE,
	SLEEP
};
/**
 * @brief The MODE the LEDs are currently in
 */
MODE currentMode = REDGREENBLUE;

/**
 * @brief What set of characters to be listening to.
 * COMMAND: Listen for a character that matches a command.
 * PALETTTECOMMAND: Listen for arguments for the palette command.
 * CREATEPALETTECOMMAND: Listen for arguments for creating a custom palette.
 * NUMBER: Listen for hexadecimal characters for later use
 */
enum SERIALSTATE {
	COMMAND,
	PALETTECOMMAND,
	CREATEPALETTECOMMAND,
	NUMBER
};
/**
 * @brief The SERIALSTATE the system is currently in
 */
SERIALSTATE currentState = COMMAND;

/**
 * @brief The purpose of the currently cached serialNumber.
 * STORERED: Store the number as a custom palette color for the red channel.
 * STOREGREEN: Store the number as a custom palette color for the green channel.
 * STOREBLUE: Store the number as a custom palette color for the blue channel.
 * RED: Set the red channel for static color mode
 * GREEN: Set the green channel for static color mode
 * BLUE: Set the blue channel for static color mode
 * BRIGHT: Set the brightness
 * DELAY: Set the delay timer
 * STRETCH: Set the paletteStretch
 */
enum SERIALNUMPURPOSE {
	STORERED,
	STOREGREEN,
	STOREBLUE,
	RED,
	GREEN,
	BLUE,
	BRIGHT,
	DELAY,
	STRETCH
};
SERIALNUMPURPOSE serialNumPurpose = RED;

/**
 * @brief The current digits place when intaking a hexadecimal number.
 * HUNDREDS: Hundreds place.
 * TENS: Tens place.
 * ONES: Ones place.
 * FIN: Done with this number. Use SERIALNUMPURPOSE to store the currently cached number
 */
enum SERIALNUMSTATE {
	HUNDREDS,
	TENS,
	ONES,
	FIN
};
/**
 * @brief The current SERIALNUMSTATE in parsing the current number
 */
SERIALNUMSTATE currentNumState = FIN;

/**
 * @brief Converts a hexadecimal character to an integer
 */
int hexToInt(char& hexChar) {
	switch (hexChar) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': return 10;
		case 'B': return 11;
		case 'C': return 12;
		case 'D': return 13;
		case 'E': return 14;
		case 'F': return 15;
		default: return 0;
	}
}

/**
 * @brief Makes the next calculation for the serialNumber based on the currentNumState
 * 
 * @param hexChar The next hexadecimal number that came in
 */
void ReadSerialHex(char& hexChar) {
	uint8_t rxInt = hexToInt(hexChar);

	switch (currentNumState) {
		case HUNDREDS:
			serialNumber += rxInt * 256;
			currentNumState = TENS;
			break;
		case TENS:
			serialNumber += rxInt * 16;
			currentNumState = ONES;
			break;
		case ONES:
			serialNumber += rxInt;
			currentNumState = FIN;
			break;
	}
}

/**
 * @brief Prepares variables to read the next number
 * 
 * @param purpose The purpose of this number
 * @param numState How many digits the number is. Defaults to the TENS place
 */
void ResetSerialNum(SERIALNUMPURPOSE purpose, SERIALNUMSTATE numState = TENS) {
	currentState = NUMBER;
	currentNumState = numState;
	serialNumber = 0;
	serialNumPurpose = purpose;
}

/**
 * @brief Goes into static color and sets colors to white
 * 
 */
void Wake() {
	delayTime = 10;
	currentMode = REDGREENBLUE;
	currentColor[0] = 255;
	currentColor[1] = 255;
	currentColor[2] = 255;
	brightness = 255;
}

void handleCommand(char& rxChar){
	switch (rxChar) {
		//Go into static color mode and set the red channel
		case 'r': {
			currentMode = REDGREENBLUE;
			ResetSerialNum(RED);
			break;
		}
		//Go into static color mode and set the green channel
		case 'g': {
			currentMode = REDGREENBLUE;
			ResetSerialNum(GREEN);
			break;
		}
		//Go into static color mode and set the blue channel
		case 'b': {
			currentMode = REDGREENBLUE;
			ResetSerialNum(BLUE);
			break;
		}
		//Set the paletteStretch setting
		case 's': {
			//Palette Stretch (color index increase per loop)
			//Take in only one HEX char. Set the incremental to the received number plus one
			//The range of the incremental is 1 - 16, an F is 15
			ResetSerialNum(STRETCH, ONES);
			break;
		}
		//Go into palette mode and listen for arguments
		case 'p': {
			currentState = PALETTECOMMAND;
			currentMode = PALETTE;
			break;
		}
		//Go into solid palette mode and listen for arguments
		case 'P': {
			currentState = PALETTECOMMAND;
			currentMode = SOLIDPALETTE;
			break;
		}
		//Set the blending setting to LINEARBLEND
		case 'l': {
			currentBlending = LINEARBLEND;
			delayBypass = true;
			break;
		}
		//Set the blending setting to NOBLEND
		case 'n': {
			currentBlending = NOBLEND;
			delayBypass = true;
			break;
		}
		//Prepare to receive a custom palette
		case 'C': {
			memset(paletteBuffer, 0, sizeof paletteBuffer);
			paletteIndexColorsMade = 0;
			paletteColorsMade = 0;
			currentState = CREATEPALETTECOMMAND;
			break;
		}
		//Set the brightness
		case 'B': {
			ResetSerialNum(BRIGHT);
			break;
		}
		//Set the delay
		case 'd': {
			ResetSerialNum(DELAY, HUNDREDS);
			break;
		}
		//Go to sleep
		case 'S': {
			delayTime = 10;
			brightness = 0;
			currentMode = SLEEP;
			break;
		}
		//Wake up
		case 'W': {
			Wake();
			delayBypass = true;
			break;
		}
		//Unable to recognize command
		default:
			Serial.print("Unrecognized Command: ");
			Serial.println(rxChar);
			break;
	}
}

/**
 * @brief Receive arguments for creating a palette
 */
void handleCreatePaletteArgs(char& rxChar){
	//If not all colors are received
	if (paletteColorsMade < 16) {
		//Get another number, add it to the paletteBuffer
		if (paletteIndexColorsMade < 3) {
			switch (rxChar) {
				case 'r': {
					//Prepare to store next number to red channel
					ResetSerialNum(STORERED);
					break;
				}
				case 'g': {
					//Prepare to store next number to green channel
					ResetSerialNum(STOREGREEN);
					break;
				}
				case 'b': {
					//Prepare to store next number to blue channel
					ResetSerialNum(STOREBLUE);
					break;
				}
			}
		} else {
			//All colors received, store this set into buffer
			paletteIndexColorsMade = 0;
			paletteBuffer[paletteColorsMade] = CRGB(paletteRed, paletteGreen, paletteBlue);
			paletteColorsMade++;
		}
	} else {
		//All colors have been received, create the custom palette
		customPalette = CRGBPalette16(paletteBuffer[0], paletteBuffer[1], paletteBuffer[2], paletteBuffer[3],
									paletteBuffer[4], paletteBuffer[5], paletteBuffer[6], paletteBuffer[7],
									paletteBuffer[8], paletteBuffer[9], paletteBuffer[10], paletteBuffer[11],
									paletteBuffer[12], paletteBuffer[13], paletteBuffer[14], paletteBuffer[15]);

		//Update currentPalete to be the new customPalette. If we are not in SolidPaletteMode, then set current mode to Palette mode
		currentPalette = customPalette;
		if (currentMode != SOLIDPALETTE) {
			currentMode = PALETTE;
		}

		delayBypass = true;
		currentState = COMMAND;
	}
}

/**
 * @brief Receive arguments for palette mode (which palette to select)
 */
void handlePaletteArgs(char& rxChar){
	switch (rxChar) {
		//Rainbox stripe
		case 'R':
			currentPalette = RainbowStripeColors_p;
			break;
		//Cloud
		case 'c':
			currentPalette = CloudColors_p;
			break;
		//Party
		case 'p':
			currentPalette = PartyColors_p;
			break;
		//Ocean
		case 'o':
			currentPalette = OceanColors_p;
			break;
		//Lava
		case 'l':
			currentPalette = LavaColors_p;
			break;
		//Forest
		case 'f':
			currentPalette = ForestColors_p;
			break;
		//Currently stored custom palette
		case 'C':
			currentPalette = customPalette;
			break;
		//Rainbow
		default:
			currentPalette = RainbowColors_p;
			break;
	}
	currentState = COMMAND;
	delayBypass = true;
}

/**
 * @brief Acts on a fully complete serialNumber
 */
void storeFinishedNumber(){
	switch (serialNumPurpose) {
		//Store the number as the red channel for a custom palette
		case STORERED:
			paletteRed = serialNumber;
			paletteIndexColorsMade++;
			currentState = CREATEPALETTECOMMAND;
			break;
		//Store the number as the green channel for a custom palette
		case STOREGREEN:
			paletteGreen = serialNumber;
			paletteIndexColorsMade++;
			currentState = CREATEPALETTECOMMAND;
			break;
		//Store the number as the blue channel for a custom palette
		case STOREBLUE:
			paletteBlue = serialNumber;
			paletteIndexColorsMade++;
			currentState = CREATEPALETTECOMMAND;
			break;
		//Store the number as the red channel for static color mode
		case RED:
			currentColor[0] = serialNumber;
			delayBypass = true;
			currentState = COMMAND;
			break;
		//Store the number as the green channel for static color mode
		case GREEN:
			currentColor[1] = serialNumber;
			delayBypass = true;
			currentState = COMMAND;
			break;
		//Store the number as the blue channel for static color mode
		case BLUE:
			currentColor[2] = serialNumber;
			delayBypass = true;
			currentState = COMMAND;
			break;
		//Use the number for setting the brightness
		case BRIGHT:
			brightness = serialNumber;
			delayBypass = true;
			currentState = COMMAND;
			break;
		//Use the number for setting the delay
		case DELAY:
			delayTime = serialNumber;
			delayBypass = true;
			currentState = COMMAND;
			break;
		//Use the number for setting the palette stretching
		case STRETCH:
			paletteStretch = serialNumber + 1;
			delayBypass = true;
			currentState = COMMAND;
			break;
	}
}

/**
 * @brief Processes the next serial character if available
 */
void ReadSerial() {
	if (Serial.available()) {
		char rxChar = Serial.read();

		//Ignore what may have been said and listen to commands
		if (rxChar == 'x') {
			currentState = COMMAND;
			return;
		}

		switch (currentState) {
			case COMMAND: {
				handleCommand(rxChar);
				break;
			}
			//Receive arguments for creating a palette
			case CREATEPALETTECOMMAND: {
				handleCreatePaletteArgs(rxChar);
				break;
			}
			//Receive arguments for palette mode (which palette to select)
			case PALETTECOMMAND: {
				handlePaletteArgs(rxChar);
				break;
			}
			//Receive a number
			case NUMBER: {
				ReadSerialHex(rxChar);

				//If done reading the current number
				if (currentNumState == FIN) {
					storeFinishedNumber();
				}
				break;
			}
		}
	}
}

/**
 * @brief Mode state machine function when in RGB mode (static color mode)
 */
void RGBMode() {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i].setRGB(currentColor[0], currentColor[1], currentColor[2]);
	}
}

/**
 * @brief Mode state machine function when in palette mode
 */
void PaletteMode(uint8_t colorIndex) {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
		colorIndex += paletteStretch;
		//colorIndex max is 16
		//May want to try to find a way to let it take numbers smaller than 1
	}
}

/**
 * @brief Mode state machine function when in solid palette mode
 */
void SolidPaletteMode(uint8_t colorIndex) {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
	}
	colorIndex += paletteStretch;
}

/**
 * @brief Arduino function that runs at startup
 */
void setup() {
	delay(3000); //Wait 3 seconds so everything has time to power up
	//Init bluetooth receive and LEDs
	Serial.begin(9600);
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	Wake();
	Serial.println("READY:");

	//Start timers
	delayStart = millis();
}

/**
 * @brief Arduino function that runs repeatedly
 */
void loop() {
	//Read commands
	ReadSerial();

	//Set the brightness
	FastLED.setBrightness(brightness);

	//Timer Source: https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html#using
	if (delayBypass || (millis() - delayStart) >= delayTime) {
		//Reset timer and override
		delayStart = millis();
		delayBypass = false;

		//Set the start index for palette modes
		static uint8_t startIndex = 0;
		startIndex++;

		//Change the LEDs based on which mode we're in
		switch (currentMode) {
			case REDGREENBLUE:
				RGBMode();
				break;
			case PALETTE:
				PaletteMode(startIndex);
				break;
			case SOLIDPALETTE:
				SolidPaletteMode(startIndex);
				break;
		}

		//Update the LED strip
		FastLED.show();
	}
}
