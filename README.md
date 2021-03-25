# SigmonLED Arduino
This code turns your Arduino into a WS2811 LED controller. Control using UART, which includes IR Remotes, Bluetooth, serial terminals, and anything else you can jam into that RX pin.

Originally created as a Christmas gift for my sister.

See [SigmonLED-App](https://github.com/Stephen-Hamilton-C/SigmonLED-App) for an Android and Desktop application to control this over Bluetooth.

## Setup
You'll need an Arduino, LED strip, and a serial interface to the Arduino. I use an HM-10 BLE module from DSD Tech, it has massive range and fits my needs.

By default, the LED mode is WS2811, so any LED strip with a WS2811 or similar chip will work just fine. Otherwise, you'll need to change the `LED_TYPE` constant at the top of the script.

1. Make sure you have the FastLED library installed and up-to-date.
2. Plug the LED's VCC to 5V, GND to ground, and IN (or data) to digital 3 or other PWM pin.
3. If digital 3 is not available to you, you will need to change the `LED_PIN` constant at the top of the script to whatever your pin is.
4. Put in the amount of LEDs on your strip in the `NUM_LEDS` constant. If there are too many to count, check the product page or packaging of your LED strip.
5. Plug the Arduino into your computer via USB and upload the code
6. Access commands through the Arduino Serial Monitor (Tools>Serial Monitor)

## Commands
- ``x``: Stops listening for arguments and listens for commands. Basically a "nevermind" command.
- ``r``: Set the red channel.
  - `000` - `255`: Set the red channel to this value. Note that the number must be 3 characters long, no matter how small the number. Example: r008 will set red channel to 8, but r8 will make SigmonLED wait for two more numbers.
- ``g``: Set the green channel.
  - See `r` for how to set the value.
- ``b``: Set the blue channel.
  - See `r` for how to set the value.
- ``p``: Enter Palette mode
  - `r`: Rainbow
  - `R`: Rainbow stripe
  - `c`: Cloud
  - `p`: Party
  - `o`: Ocean
  - `l`: Lava
  - `f`: Forest
    - (Entered after palette selection)
    - `l`: Linear blending.
    - `n`: No blending.
- ``P``: Enter Solid Palette mode.
  - See `p` for arguments.
- ``B``: Set Brightness.
  - See `r` for how to set the value.
- ``d``: Set Delay in ms. (applicable to Palette and Solid Palette modes)
  - `0000` - `9999`: Set the delay to this value. Note that the number must be 4 characters long, no matter how small the number. Example: d0100 will set the delay to 100 ms, but d100 will make SigmonLED wait for one more number.
- ``S``: Sleep. Turns off LEDs.
- ``W``: Wake. Turns LEDs on full brightness at full white.
- ``C``: upload a custom palette.
  - Takes in 16 groupings of r, g, and b; each followed by a `#`.
  - For example, each grouping is `r255g000b255#`, which would set that palette index to pink.
  - Once the 16 groupings are fed in, add another `#` to the end to finalize the upload.
  - See [This PasteBin](https://pastebin.com/atVPAubi) for an example custom palette string.
  - Once the palette is uploaded, SigmonLED enters Palette mode, unless the Arduino is already in SolidPalette mode.

Command example: `r127g000b255` will make all LEDs turn purple. \
Command example: `prl` will activate the Rainbow palette with linear blending.

## Licensed
SigmonLED is licensed under the GNU General Public License v3.0. You can find the license details in the `LICENSE` file in the main branch. Feel free to repurpose, redistribute, and branch off this code anytime :D
