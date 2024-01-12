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
Coming soon™


## IR Usage
See [this handy manual](./docs/ir-usage-manual/SigmonLED%20IR%20Remote%20User's%20Manual.pdf).
Note that non-IR control instructions may not apply to your specific setup.


## License
SigmonLED is licensed under the GNU General Public License v3.0. You can find the license details in the `LICENSE` file in the main branch. Feel free to repurpose, redistribute, and branch off this code anytime :D


[config]: ./include/config.h
