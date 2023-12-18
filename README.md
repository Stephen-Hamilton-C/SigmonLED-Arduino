# WARNING
**This readme is out of date!**
These instructions only apply to legacy v2 versions of SigmonLED-Arduino.

This will be rewritten soon!

# SigmonLED-Arduino

This code turns your Arduino into a WS2811 LED controller. Controlled using UART, although it was designed for HM-10 BLE modules.

Originally created as a Christmas gift for my sister

See [SigmonLED-App](https://github.com/Stephen-Hamilton-C/SigmonLED-App) for an Android app and [SigmonLED-Desktop](https://github.com/Stephen-Hamilton-C/SigmonLED-Desktop) for a desktop application that can control this over Bluetooth.

## Setup
You'll need an Arduino, LED strip, and a serial interface, preferably an HM-10 BLE module, though other methods should theoretically work.

By default, the LED mode is WS2811, so any LED strip with a WS2811 or similar chip will work just fine.
Otherwise, you'll need to change the LED_TYPE constant in [config.h](https://github.com/Stephen-Hamilton-C/blob/main/include/config.h).

1. Download the [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension for VS Code.
2. Plug the LED's VCC to 5V, GND to ground, and IN (or data) to digital 6 or other PWM pin.
3. If digital 6 is not available to you, you will need to change the `LED_PIN` constant in [config.h](https://github.com/Stephen-Hamilton-C/blob/main/include/config.h).
4. Put in the amount of LEDs on your strip in the `LED_COUNT` constant in [config.h](https://github.com/Stephen-Hamilton-C/blob/main/include/config.h).
5. Plug the Arduino into your computer via USB and upload the code. 
   - Make sure digital 1 and 0 are unplugged before uploading!

## Commands
Commands are given with standard ASCII chars, but their arguments are typically in binary.
All commands **must** be terminated with a `\n` character. Unfortunately, this also means that any binary argument sent as `10` will register as the end of the command. So no color can be exactly `10`.

- `l` (1 binary arg): Sets the linear blending mode for palettes.
  - `0`: No linear blending.
  - `1`: Enable linear blending.
  - Note: Any data sent that is not `0` is considered to be `1`.
- `b` (1 binary arg): Sets the palette brightness.
  - Any byte from 0 - 255.
- `c` (3 binary args): Sets the color of the entire strip.
  - The next three bytes are the red, green, and blue channels respectively.
- `C` (48 binary args): Upload custom palette.
  - The 48 bytes are 16 colors, 3 bytes each. In the format of `RGB`. So the first byte is red, the second is green, and the third is blue. Repeat this 16 times to upload a complete palette.
- `d` (2 binary args): Palette Delay. This effects how fast palette effects are, with higher numbers being slower.
  - The two bytes are a 16-bit unsigned integer in big-endian notation.
- `0` (0 binary args): This command is indeed an ASCII 0. This will power off the LED strip.
- `1` (0 binary args): This command is indeed an ASCII 1. This will power on the LED strip and set it to the color defined by the `S` command.
- `p` (1 ASCII arg): Set the palette
  - These are ASCII arguments
  - `r`: Rainbow
  - `R`: Rainbow Stripe
  - `c`: Cloud
  - `p`: Party
  - `o`: Ocean
  - `l`: Lava
  - `f`: Forest
  - `C`: Currently Uploaded Custom Palette
- `P`: (1 binary arg): Set the Palette Mode.
  - `0`: Static. The colors are simply applied to the LED strip.
  - `1`: Scrolling. The colors will scroll across the LED strip.
  - `2`: Solid. The entire strip will scroll through the palette.
- `S`: (3 binary args): Store Color. This is the color used by the `1` command.
  - The next three bytes are the red, green, and blue channels respectively.
- `s`: (1 binary arg): Palette Stretch. This determines how much a palette is distributed across the LED strip.
  - A byte from 0 - 255.

## License
SigmonLED is licensed under the GNU General Public License v3.0. You can find the license details in the `LICENSE` file in the main branch. Feel free to repurpose, redistribute, and branch off this code anytime :D

