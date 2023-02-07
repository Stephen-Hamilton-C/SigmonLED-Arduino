# Changelog
All notable changes to SigmonLED-Arduino will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
SigmonLED-Arduino uses [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.2] - 2022-02-07
### Fixed
- On/Off commands not working when in Palette mode

## [1.0.1] - 2022-02-06
### Fixed
- Incorrect number of arguments being read in some edge cases

## [1.0.0] - 2022-02-05
### Added
- New palette mode: static. This simply distributes the palette across the entire LED strip depending on the Palette Stretching.
- On/Off color storing. You can now define a color to use when running the "Wake" command
### Changed
- Most commands take in binary arguments instead of ASCII to reduce transmission size.
- All commands must end in `\n` to be recognized.
- Linear blending is now separated from the palette command.
- Brightness command now only affects palette modes.
- Static Color is now defined by a single command rather than three.
- All numbers are now sent as binary rather than ASCII hexadecimal
- Palette Mode is now determined by a separate command

## [0.4.1] - 2021-12-31
### Fixed
- Potential lockout bug. If there is no comms for 3 minutes, SigmonLED disconnects anything connected to the bluetooth module

## [0.4.0] - 2021-04-09
### Added
- Palette Stretch setting. use s# to change (where # is a single-digit hexadecimal number)

## [0.3.0] - 2021-03-26
### Added
- Ability to upload custom made palettes. See `README.md` for instructions on how to upload and show a custom palette
### Removed
- A bunch of debug output to serial
### Changed
- Colors are now received as hexadecimal.
- LEDs are now set on a timer rather than a delay. This will make commands much more responsive.


## [0.2.0] - 2021-02-15
### Added
- This Changelog :)
- Solid palette mode. Use `P` command to activate
