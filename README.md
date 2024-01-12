# SigmonLED-Arduino
This code turns your Arduino into a WS2811 LED controller.
Controlled using Serial or IR.
Works especially well over Serial with HM-10 BLE modules.

Originally created as a Christmas gift for my sister.

Android and Desktop applications are planned for this system.
Currently, IR is the easiest way to control this.


## Setup
You'll need an Arduino and an LED strip.
By default, the LED mode is WS2811, so any LED strip with a WS2811 or similar chip will work just fine.
Otherwise, you'll need to change the `LED_TYPE` constant in [config.h][config].

1. Download the [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension for VS Code.
2. Plug the LED's VCC to 5V, GND to ground, and IN (or data) to digital 6 or other PWM pin.
    - The LEDs don't need to be powered by the Arduino, so they could be externally powered if you need more current.
3. If digital 6 is not available to you, you will need to change the `LED_PIN` constant in [config.h][config].
4. Put in the amount of LEDs on your strip in the `LED_COUNT` constant in [config.h][config].
5. Setup your choice of control interface (see below)
6. Plug the Arduino into your computer via USB and upload the code.
   - Make sure digital 1 and 0 (tx and rx) are unplugged before uploading!


Now the LEDs are setup, but you still have to configure the control interface.
There are two main methods to control SigmonLED: serial, and IR.
Depending on the number of LEDs, and your specific Arduino model, you may not be able to use both due to RAM constraints.
However, each can be enabled or disabled with the `ENABLE_SERIAL_COMMANDS` and `ENABLE_IR_INPUT` constants in [config.h][config].


### Serial
1. Plug your serial interface into the TX and RX digital pins.
2. If you are not using an HM-10 BLE module, set `TIMEOUT_MESSAGE` to `0` in [config.h][config].
3. Otherwise, set it to whatever command must be sent to the serial interface to initiate a disconnect.
4. Ensure `ENABLE_SERIAL_COMMANDS` is set to `true` in [config.h][config].


### IR
1. Plug the IR sensor data pin to digital 7 or other non-PWM pin.
2. If digital 7 is not available to you, you will need to change the `IR_PIN` constant in [config.h][config]


## Serial Commands


### Command Behavior
All Serial commands now require verification when sent.
Commands are delimited with a newline character (`\n`).
When a command is sent, the Arduino will respond with `verify <command>` if it recognizes the command.
`<command>` will, of course, be replaced with what was sent.
The Arduino will then wait for `confirm` to run the command.
If the command does not match, resending the command will start the process over.
If the command is not recognized,
or if there is no response within a set time (defined by `MESSAGE_TIMEOUT` in [config.h][config]),
then the Arduino responds with `disregard` and ignores the command.
If `confirm` is sent, the Arduino responds with `confirmed` if arguments are valid,
or `disregard` if something went wrong running the command.

Examples: (TX = Send to Arduino, RX = Receive from Arduino. Every transmission ends in `\n`)
```
TX: color 255 0 0
RX: verify color 255 0 0
TX: confirm
RX: confirmed
```
```
TX: lol hello
RX: disregard
```
```
TX: color 0 255 0
RX: verify color 0 255 0
TX: color 0 0 255
RX: verify color 0 0 255
TX: confirm
RX: confirmed
```
```
TX: color 255 255 255
RX: verify color 255 255 255
*5 seconds pass*
RX: disregard
```


### Commands
- `color <red> <green> <blue>`
  - Changes the entire strip to the color provided.
  - red, green, and blue arguments must be within the inclusive range 0 - 255
- `hello`
  - Returns the current state of the controller
  - Format: `MAJOR.MINOR.PATCH red,green,blue mode brightness palette_type palette_delay palette_stretch palette_mode palette_blending`
  - Example: `3.2.0 255,0,0 0 255 0 10 8 0 1`
- `blend <int>`
  - Sets the palette blending mode.
  - Possible values:

| Blend Value | Description |
| ----------- | ----------- |
|   0   | No blending |
|   1   | Linear blending |
|   2   | Linear blending, no wrap |
- `bright <int>`
  - Sets the brightness of the current color or palette
  - Must be within the inclusive range 0 - 255
- `delay <int>`
  - Sets the millisecond delay between palette scroll updates
  - Must be within the inclusive range 0 - 65535
- `palette <int>`
  - Sets the current palette to be used and switches to palette mode
  - Possible values:
 
| Palette Value | Description |
| ------------- | ----------- |
|   0   |   Rainbow   |
|   1   | Rainbow Stripe |
|   2   |    Party    |
|   3   |    Ocean    |
|   4   |    Lava     |
|   5   |    Forest   |
|   6   |    Custom   |
- `pmode <int>`
  - Sets the palette scrolling mode
  - Possible values:

| Palette Mode | Description |
| ------------ | ----------- |
|       0      | Static - No Scrolling |
|       1      | Scroll |
|       2      | Solid - Entire LED strip scrolls through palette |
- `stretch <int>`
  - Sets the distribution of palette colors across the LED strip
  - Must be within the inclusive range 0 - 255
- `custom <index> <red> <green> <blue>`
  - Sets the color at the given index for the custom palette
  - index must be within the inclusive range 0 - 15
  - red, green, and blue must be within the inclusive range 0 - 255


## IR Usage
See [this handy manual](./docs/ir-usage-manual/SigmonLED%20IR%20Remote%20User's%20Manual.pdf).
Note that non-IR control instructions may not apply to your specific setup.


## License
SigmonLED is licensed under the GNU General Public License v3.0. You can find the license details in the `LICENSE` file in the main branch. Feel free to repurpose, redistribute, and branch off this code anytime :D


[config]: ./include/config.h
