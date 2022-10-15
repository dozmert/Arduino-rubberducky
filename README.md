# Arduino Rubberducky
#### Synopsis
A script to run on an arduino (using atmega32u4 chip) which reads ducky-like scripts from a microSD card. 
There are two versions of this script:
- Arduino-RubberDucky-SingleScript
- Arduino-RubberDucky-DIPSwitch

#### Description
A project based on the work of [Seytonic's Duckduino-microSD](https://github.com/Seytonic/Duckduino-microSD).  Videos of his project can be found [here](https://www.youtube.com/watch?v=ksvo1WDYQ7s) and [here](https://www.youtube.com/watch?v=QrwqeI99I8E). I wanted to tackle this project myself as both a learning experience and a utility tool for my craft. 

#### Usage
- Write .ino file to Arduino
- Create and load scripts onto microSD card
- Select script via DIP switch configuration
- Plug Arduino into PC to execute script
- Press and old tactile button when plugging Arduino into PC to not execute script

#### Hardware
- 1x Arduino Leonardo Pro Micro
>TZT Pro Micro ATmega32U4 5V 16MHz Original Chip Replace ATmega328 For Arduino Pro Mini With 2 Row Pin Header For Leonardo UNO R3
- 1x MicroSD card reader module
>Micro SD Storage Expansion Board Micro SD TF Card Memory Shield Module SPI For Arduino
- 1x MicroSD card
> Formatted as FAT32
- 1x DIP Switch 
> 6 way DIP switch, standard pcb IC mounting. Can use various sizes based on Arduino pinout.
- 1x Tactile switch
- 1x Resistor
>Unknown, taken from Arduino Uno Starter kit.

#### Pinout
Data below based on breadboard layout.
| Arduino Pin | - | Module | - | Module |
| --- | --- | --- | --- | --- |
| Arduino VCC-1 | -> | microSD VCC | - | - |
| Arduino GND | -> | microSD GND | - | - |
| Arduino D14 | -> | microSD MISO | - | - |
| Arduino D16 | -> | microSD MOSI | - | - |
| Arduino D15 | -> | microSD SCK | - | - |
| Arduino D4 | -> | microSD CS | - | - |
| Arduino VCC-2 | -> | TactileButton-1 | - | - |
| Arduino GND-2 | -> | Resistor | -> | TactileButton-2-1
| Arduino D10 | -> | TactileButton-2-2 | - | - |
| Arduino D2 | -> | DIPSwitch-1 | -> | Arduino GND |
| Arduino D3 | -> | DIPSwitch-2 | -> | Arduino GND |
| Arduino D5 | -> | DIPSwitch-3 | -> | Arduino GND |
| Arduino D6 | -> | DIPSwitch-4 | -> | Arduino GND |
| Arduino D7 | -> | DIPSwitch-5 | -> | Arduino GND |
| Arduino D8 | -> | DIPSwitch-6 | -> | Arduino GND |

#### Notes to keep in mind
- Long ducky-like script strings may crash arduino due to RAM consumption. String lines over 300 characters should be split into seperate lines. This will not affect how the script runs but will help reduce RAM consumption.
> STRING abcde
> STRING fghij
- Hyphens must not be used for simultaneous key presses due to current scripting. 
>"CTRL ALT DELETE" instead of "CTRL-ALT-DELETE"
- Features not implemented: DEFAULT_DELAY, REPLAY. This project uses arduino's inbuilt <a href="https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h">keyboard.h</a> library, any keys not implemented in that will not work with this. eg: PRINTSCREEN.

#### To do
- Confirm resistor used in hardware
- Install bluetooth module for remote interactivity
- Photos of hardware
- Implement more keys that aren't used in [keyboard.h library](https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h).
