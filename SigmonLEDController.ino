#include <FastLED.h>

//Make the colorIndex incremental be changable. Call it "Palette Stretch"

#define LED_PIN 3
#define NUM_LEDS 8 //300
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

unsigned long delayStart = 0;
bool delayBypass = false;

CRGB leds[NUM_LEDS];
int currentColor[3]{255, 255, 255};
int brightness = 16;
int delayTime = 10;
int serialNumber = 0;

int paletteRed = 0;
int paletteGreen = 0;
int paletteBlue = 0;
int paletteIndexColorsMade = 0;
int paletteColorsMade = 0;
CRGB paletteBuffer[16];
CRGBPalette16 customPalette;

CRGBPalette16 currentPalette;
TBlendType currentBlending;

enum MODE
{
	REDGREENBLUE,
	PALETTE,
	SOLIDPALETTE,
	SLEEP
};
MODE currentMode = REDGREENBLUE;

enum SERIALSTATE
{
	COMMAND,
	BRIGHTCOMMAND,
	DELAYCOMMAND,
	PALETTECOMMAND,
	CREATEPALETTECOMMAND,
	NUMBER
};
SERIALSTATE currentState = COMMAND;

enum SERIALNUMPURPOSE
{
	STORERED,
	STOREGREEN,
	STOREBLUE,
	RED,
	GREEN,
	BLUE,
	BRIGHT,
	DELAY
};
SERIALNUMPURPOSE serialNumPurpose = RED;

enum SERIALNUMSTATE
{
	HUNDREDS,
	TENS,
	ONES,
	FIN
};
SERIALNUMSTATE currentNumState = FIN;

int hexToInt(char hexChar)
{
	switch (hexChar)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		return 0;
	}
}

void ReadSerialHex(char hexChar)
{
	int rxInt = hexToInt(hexChar);

	switch (currentNumState)
	{
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

void ResetSerialNum(SERIALNUMPURPOSE purpose, SERIALNUMSTATE numState = TENS)
{
	currentState = NUMBER;
	currentNumState = numState;
	serialNumber = 0;
	serialNumPurpose = purpose;
}

void Wake()
{
	delayTime = 10;
	currentMode = REDGREENBLUE;
	currentColor[0] = 255;
	currentColor[1] = 255;
	currentColor[2] = 255;
	brightness = 255;
}

void ReadSerial()
{
	if (Serial.available())
	{
		char rxChar = Serial.read();
		//Serial.print("RX: ");
		//Serial.println(rxChar);

		if (rxChar == 'x')
		{ //Reset
			currentState = COMMAND;
			//Serial.println("READY:");
			Serial.println("Reset");
			return;
		}

		switch (currentState)
		{
		case COMMAND:
		{
			//Serial.println("COMMAND");
			switch (rxChar)
			{
			case 'r':
			{
				currentMode = REDGREENBLUE;
				ResetSerialNum(RED);
				//Serial.println("Red");
				break;
			}
			case 'g':
			{
				currentMode = REDGREENBLUE;
				ResetSerialNum(GREEN);
				//Serial.println("Green");
				break;
			}
			case 'b':
			{
				currentMode = REDGREENBLUE;
				ResetSerialNum(BLUE);
				//Serial.println("Blue");
				break;
			}
			case 'p':
			{
				currentState = PALETTECOMMAND;
				currentMode = PALETTE;
				//Serial.println("Palatte");
				break;
			}
			case 'P':
			{
				currentState = PALETTECOMMAND;
				currentMode = SOLIDPALETTE;
				break;
			}
			case 'l':
			{
				currentBlending = LINEARBLEND;
				delayBypass = true;
				//Serial.println("Linear Blend");
				break;
			}
			case 'n':
			{
				currentBlending = NOBLEND;
				delayBypass = true;
				//Serial.println("No Blend");
				break;
			}
			case 'C':
			{
				//Serial.println("Create");
				memset(paletteBuffer, 0, sizeof paletteBuffer);
				paletteIndexColorsMade = 0;
				paletteColorsMade = 0;
				currentState = CREATEPALETTECOMMAND;
				Serial.println(String(CREATEPALETTECOMMAND));
				Serial.println(String(currentState));
				break;
			}
			case 'B':
			{
				currentState = NUMBER;
				ResetSerialNum(BRIGHT);
				//Serial.println("Brightness");
				break;
			}
			case 'd':
			{
				currentState = NUMBER;
				ResetSerialNum(DELAY, HUNDREDS);
				//Serial.println("Delay");
				break;
			}
			case 'S':
			{
				delayTime = 10;
				brightness = 0;
				currentMode = SLEEP;
				//Serial.println("Sleep");
				break;
			}
			case 'W':
			{
				Wake();
				delayBypass = true;
				//Serial.println("Wake");
				break;
			}
			default:
				Serial.println("Unrecognized Command: " + rxChar);
				//Serial.println("READY:");
				break;
			}
			break;
		}
		case CREATEPALETTECOMMAND:
		{
			//Serial.println("CREATEPALETTE");
			if (paletteColorsMade < 16)
			{
				//Get another number, add it to the paletteBuffer
				if (paletteIndexColorsMade < 3)
				{
					switch (rxChar)
					{
					case 'r':
					{
						//Serial.println("RedC");
						ResetSerialNum(STORERED);
						break;
					}
					case 'g':
					{
						//Serial.println("GreC");
						ResetSerialNum(STOREGREEN);
						break;
					}
					case 'b':
					{
						//Serial.println("BluC");
						ResetSerialNum(STOREBLUE);
						break;
					}
					}
				}
				else
				{
					paletteIndexColorsMade = 0;
					paletteBuffer[paletteColorsMade] = CRGB(paletteRed, paletteGreen, paletteBlue);
					paletteColorsMade++;
					//Serial.println("indo" + String(paletteColorsMade));
				}
			}
			else
			{
				customPalette = CRGBPalette16(paletteBuffer[0], paletteBuffer[1], paletteBuffer[2], paletteBuffer[3],
											  paletteBuffer[4], paletteBuffer[5], paletteBuffer[6], paletteBuffer[7],
											  paletteBuffer[8], paletteBuffer[9], paletteBuffer[10], paletteBuffer[11],
											  paletteBuffer[12], paletteBuffer[13], paletteBuffer[14], paletteBuffer[15]);

				//Update currentPalete to be the new customPalette. If we are not in SolidPaletteMode, then set current mode to Palette mode
				currentPalette = customPalette;
				if (currentMode != SOLIDPALETTE)
				{
					currentMode = PALETTE;
				}

				delayBypass = true;
				currentState = COMMAND;
				//Serial.println("pado");
			}
			break;
		}
		case PALETTECOMMAND:
		{
			Serial.println("PALETTE");
			switch (rxChar)
			{
			case 'R':
			{
				currentPalette = RainbowStripeColors_p;
				//Serial.println("RainbowStripe");
				break;
			}
			case 'c':
			{
				currentPalette = CloudColors_p;
				//Serial.println("Cloud");
				break;
			}
			case 'p':
			{
				currentPalette = PartyColors_p;
				//Serial.println("Party");
				break;
			}
			case 'o':
			{
				currentPalette = OceanColors_p;
				//Serial.println("Ocean");
				break;
			}
			case 'l':
			{
				currentPalette = LavaColors_p;
				//Serial.println("Lava");
				break;
			}
			case 'f':
			{
				currentPalette = ForestColors_p;
				//Serial.println("Forest");
				break;
			}
			case 'C':
			{
				//Go to custom palette
				currentPalette = customPalette;
				//Serial.println("Custom");
				break;
			}
			default:
			{
				currentPalette = RainbowColors_p;
				//Serial.println("Rainbow");
				break;
			}
			}
			currentState = COMMAND;
			delayBypass = true;
			break;
		}
		case NUMBER:
		{
			//Serial.println("NUMBER");
			ReadSerialHex(rxChar);
			if (currentNumState == FIN)
			{
				Serial.print("num:");
				Serial.println(serialNumber);
				switch (serialNumPurpose)
				{
				case STORERED:
					paletteRed = serialNumber;
					paletteIndexColorsMade++;
					currentState = CREATEPALETTECOMMAND;
					//Serial.println("StoreRed");
					break;
				case STOREGREEN:
					paletteGreen = serialNumber;
					paletteIndexColorsMade++;
					currentState = CREATEPALETTECOMMAND;
					//Serial.println("StoreGreen");
					break;
				case STOREBLUE:
					paletteBlue = serialNumber;
					paletteIndexColorsMade++;
					currentState = CREATEPALETTECOMMAND;
					//Serial.println("StoreBlue");
					break;
				case RED:
					currentColor[0] = serialNumber;
					//Serial.println("Red");
					delayBypass = true;
					currentState = COMMAND;
					break;
				case GREEN:
					currentColor[1] = serialNumber;
					//Serial.println("Gree");
					delayBypass = true;
					currentState = COMMAND;
					break;
				case BLUE:
					currentColor[2] = serialNumber;
					//Serial.println("Blue");
					delayBypass = true;
					currentState = COMMAND;
					break;
				case BRIGHT:
					brightness = serialNumber;
					//Serial.println("Brig");
					delayBypass = true;
					currentState = COMMAND;
					break;
				case DELAY:
					delayTime = serialNumber;
					//Serial.println("Dela");
					delayBypass = true;
					currentState = COMMAND;
					break;
				}
			}
			break;
		}
		}
	}
}

void RGBMode()
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		leds[i].setRGB(currentColor[0], currentColor[1], currentColor[2]);
	}
}

void PaletteMode(uint8_t colorIndex)
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
		colorIndex += 3;
		//ColorIndex max is 16
	}
}

void SolidPaletteMode(uint8_t colorIndex)
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
	}
	colorIndex += 1;
}

void setup()
{
	// put your setup code here, to run once:
	delay(3000);
	Serial.begin(9600);
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	Wake();
	Serial.println("Setup Finished");
	Serial.println("READY:");

	delayStart = millis();
}

void loop()
{
	// put your main code here, to run repeatedly:

	ReadSerial();

	FastLED.setBrightness(brightness);

	//Timer Source: https://www.forward.com.au/pfod/ArduinoProgramming/TimingDelaysInArduino.html#using
	if (delayBypass || (millis() - delayStart) >= delayTime)
	{
		delayStart = millis();
		delayBypass = false;

		static uint8_t startIndex = 0;
		startIndex++;

		switch (currentMode)
		{
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

		FastLED.show();
		//FastLED.delay(delayTime);
	}
}
