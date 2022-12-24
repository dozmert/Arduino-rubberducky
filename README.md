# Arduino Rubberducky
### Synopsis
A script to run on an Arduino (using atmega32u4 chip) which reads ducky-like scripts from a microSD card. 

### Description
A project based on the work of [Seytonic's Duckduino-microSD](https://github.com/Seytonic/Duckduino-microSD).  Videos of his project can be found [here](https://www.youtube.com/watch?v=ksvo1WDYQ7s) and [here](https://www.youtube.com/watch?v=QrwqeI99I8E). I wanted to tackle this project myself as both a learning experience and a utility tool for my craft. 

### Usage
- Write .ino file to Arduino
- Create and load scripts onto microSD card
- Select script via DIP switch configuration
- Plug Arduino into PC to execute script
- Press and hold tactile button when plugging Arduino into PC to not execute script

#### Software
##### Arduino Script
| Script name | Script capabilities | 
| --- | --- |
| [Arduino-RubberDucky-Part1](https://github.com/dozmert/Arduino-rubberducky/blob/master/Arduino-RubberDucky-Part1/Arduino-RubberDucky-Part1.ino) | Single payload script |
| [Arduino-RubberDucky-Part2](https://github.com/dozmert/Arduino-rubberducky/blob/master/Arduino-RubberDucky-Part2/Arduino-RubberDucky-Part2.ino) | MicroSD payload script | 
| [Arduino-RubberDucky-Part3](https://github.com/dozmert/Arduino-rubberducky/blob/master/Arduino-RubberDucky-Part3/Arduino-RubberDucky-Part3.ino) | In progress... Bluetooth Remote Interactivity |

##### Payload Script Examples
| Payload script | Description |
| :---: | --- |
| [SingleScript](https://github.com/dozmert/Arduino-rubberducky/blob/master/Example%20scripts/SingleScript/script.txt) | A simple paylod which runs cmd.exe and echos "Hello world" |
| [DIPSwitch](https://github.com/dozmert/Arduino-rubberducky/tree/master/Example%20scripts/DIPSwitch) | 64 payloads based on a 6-way DIP switch's binary output. The first script "000000" is the same as the SingleScript. In addition is a txt file with all 64 filenames listed that can be used to index/record your script usage |

### Build
#### Hardware
- 1x Arduino Leonardo Pro Micro
>TZT Pro Micro ATmega32U4 5V 16MHz Original Chip Replace ATmega328 For Arduino Pro Mini With 2 Row Pin Header For Leonardo UNO R3

![](/img/build_1.jpg)

- 1x MicroSD card reader module
>Micro SD Storage Expansion Board Micro SD TF Card Memory Shield Module SPI For Arduino
> Formatted as FAT32

![](/img/build_2.jpg)

- 1x Tactile switch
- 1x Resistor
>Unknown, taken from Arduino Uno Starter kit.

![](/img/build_3.jpg)

- 1x DIP Switch 
> 6 way DIP switch, standard pcb IC mounting. Can use various sizes based on Arduino pinout.

![](/img/build_4.jpg)

- 1x Bluetooth Module
> Generic Board

![](/img/build_8.jpg)

#### Pinout
Data below based on breadboard layout.
| Build Part | Module Pin | - | Module Pin | - | Module Pin |
| :---: | :---: | :---: | :---: | :---: | :---: |
| Part 1 | Arduino VCC | -> | microSD VCC |  |  |
| Part 1 | Arduino GND | -> | microSD GND |  |  |
| Part 1 | Arduino D14 | -> | microSD MISO |  |  |
| Part 1 | Arduino D16 | -> | microSD MOSI |  |  |
| Part 1 | Arduino D15 | -> | microSD SCK |  |  |
| Part 1 | Arduino D4 | -> | microSD CS |  |  |
| Part 1 | Arduino VCC | -> | TactileButton-1 |  |  |
| Part 1 | Arduino GND | -> | Resistor | -> | TactileButton-2-1
| Part 1 | Arduino D10 | -> | TactileButton-2-2 |  |  |
| Part 2 | Arduino D3 | -> | DIPSwitch-1 | -> | Arduino GND |
| Part 2 | Arduino D5 | -> | DIPSwitch-2 | -> | Arduino GND |
| Part 2 | Arduino D6 | -> | DIPSwitch-3 | -> | Arduino GND |
| Part 2 | Arduino D7 | -> | DIPSwitch-4 | -> | Arduino GND |
| Part 2 | Arduino D8 | -> | DIPSwitch-5 | -> | Arduino GND |
| Part 2 | Arduino D9 | -> | DIPSwitch-6 | -> | Arduino GND |
| Part 3 | Arduino VCC | -> | BTModule-VCC |  |  |
| Part 3 | Arduino GND | -> | BTModule-GND |  |  |
| Part 3 | Arduino D0 (TX0) | -> | BTModule-TX |  |  |
| Part 3 | Arduino D1 (RX1) | -> | BTModule-RX |  |  |

#### Breadboard prototyping
##### Part 1
1. Wiring MicroSD reader to Arduino board
![](/img/build_5.jpg)
2. Wiring tactile button to board.
![](/img/build_6.jpg)
##### Part 2
4. Wiring DIP switch to board.
![](/img/build_7.jpg)

##### Part 3
5. Wiring BTModule to board.
(Work in progress)
7. Plug into PC and write .ino file to Arduino.
(Work in progress)
9. Insert MicroSD into PC and copy in DIPSwitch profile scripts.
(Work in progress)

### Notes & Troubleshooting
- I originally had a lot of trouble getting this working which ended up being a result of my pin contacts failing to carry signals. If you're using pins, ensure they're soldered.
- Long ducky-like script strings may crash Arduino due to RAM consumption. String lines over 300 characters should be split into separate lines. This will not affect how the script runs but will help reduce RAM consumption.
> STRING abcdefghijklmnopqrstu
> STRING vwxyzmnopqrstuvwxyz
- Hyphens must not be used for simultaneous key presses due to current scripting. 
>"CTRL ALT DELETE" instead of "CTRL-ALT-DELETE"
- Features not implemented: DEFAULT_DELAY, REPLAY. This project uses Arduino's inbuilt <a href="https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h">keyboard.h</a> library, any keys not implemented in that will not work with this. eg: PRINTSCREEN.

### To do
- Confirm resistor used in hardware for documentation.
- Find a better/efficient wiring method for the tactile button. I'm not too knowledgable on wiring.
- Install bluetooth module for remote interactivity.
- Implement more keys that aren't used in [keyboard.h library](https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h).
- 3D print a small form factor housing.
- Expand example payloads based on official Hak5 rubberducky payloads - [Github](https://github.com/hak5/usbrubberducky-payloads)
- Emulate official Hak5 rubberducky attackmodes - [documentation](https://docs.hak5.org/hak5-usb-rubber-ducky/attack-modes-constants-and-variables/attack-modes)
