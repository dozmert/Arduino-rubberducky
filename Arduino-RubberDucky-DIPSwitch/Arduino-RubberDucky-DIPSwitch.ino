/*
SYNOPSIS
  A script to run on an arduino (using atmega32u4 chip) which reads ducky-like scripts from a microSD card.
  
.DESCRIPTION
  A project based on the work of Seytonic's Duckduino-microSD https://github.com/Seytonic/Duckduino-microSD.
  This version does not use DIP Switch settings.

.NOTES
  Version:        	1.0
  Author:         	Dennis Ozmert
  GitHub:	  	      https://github.com/dozmert
  Creation Date:    15/10/2022 @ 10:00pm
  Last Updated:     15/10/2022
  Purpose/Change:	  Arduino Rubberducky
  License:		      GNU General Public License

.CITED WORK
  Seytonic's Duckduino-microSD https://github.com/Seytonic/Duckduino-microSD.
  Arduino BadUSB | with microSD support: https://www.youtube.com/watch?v=ksvo1WDYQ7s
  Arduino BadUSB | w/DIP Switches: https://www.youtube.com/watch?v=QrwqeI99I8E
*/
// IMPORTS & LIBRARIES
#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <Keyboard.h>
// VARIABLES
int buttonPin = 10;  // pushbutton
int sdPin = 4; // SD Pin
File myFile;
boolean first = true;
String DEFAULT_FILE_NAME = "script.txt";
// FUNCTIONS
void setup(){ // Used to initialise SD, open designated file and read through lines
  //Serial.begin(9600); //Debugging 
  //Keyboard.begin(); //Debugging
  delay(2500);
  pinMode(buttonPin,INPUT);
  if (digitalRead(buttonPin) == HIGH){  // If buttonPin pressed, kill function
    //Serial.print("Button_pressed"); //Debugging
    return;
  }else if(!SD.begin(sdPin)){ // Else if SD failed to initialise, kill function
    //Serial.print("SD didn't initialise"); //Debugging
    return;
  }
  myFile = SD.open(DEFAULT_FILE_NAME); // Opens designated file
  if (myFile){ // If file initialised, run function
    //Serial.print("File opened"); //Debugging
    Keyboard.begin(); // Starts HID keyboard function
    String line = ""; // Defines blank variable
    while (myFile.available()){  // While initilised file is available
      char m = myFile.read(); // Read each line
      if (m == '\n'){ // If new line found, clear variable
        Line(line);
        line = "";
      }else if((int) m != 13){ // ?
        line += m;
      }
    }
    Line(line);
    myFile.close(); // Close designated file
  }
    else{
      // Serial.print("File didn't open"); //Debugging output  
  }
  //Serial.print("End of setup"); //Debugging output
  Keyboard.end(); // Stops HID keyboard function
}

void Line(String l){ // Unclear use
  int space_1 = l.indexOf(" ");
  if (space_1 == -1){
    Press(l);
  }else if (l.substring(0,space_1) == "STRING"){
    Keyboard.print(l.substring(space_1 + 1));
  }else if (l.substring(0,space_1) == "DELAY"){
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }else if(l.substring(0,space_1) == "REM"){
  }else{
    String remain = l;
    while(remain.length() > 0){
      int latest_space = remain.indexOf(" ");
      if (latest_space == -1){
        Press(remain);
        remain = "";
      }else{
        Press(remain.substring(0, latest_space));
        remain = remain.substring(latest_space + 1);
      }
      delay(5);
      }
  }
  Keyboard.releaseAll();
}

void Press(String b){ // Defines designated file instructions to HID keyboard inputs
  if(b.length() == 1){
    char c = b[0];
    Keyboard.press(c);
  }else if (b.equals("ENTER")){
    Keyboard.press(KEY_RETURN);
  }else if (b.equals("CTRL")){
    Keyboard.press(KEY_LEFT_CTRL);
  }else if (b.equals("SHIFT")){
    Keyboard.press(KEY_LEFT_SHIFT);
  }else if (b.equals("ALT")){
    Keyboard.press(KEY_LEFT_ALT);
  }else if (b.equals("GUI")){
    Keyboard.press(KEY_LEFT_GUI);
  }else if (b.equals("UP") || b.equals("UPARROW")){
    Keyboard.press(KEY_UP_ARROW);
  }else if (b.equals("DOWN") || b.equals("DOWNARROW")){
    Keyboard.press(KEY_DOWN_ARROW);
  }else if (b.equals("LEFT") || b.equals("LEFTARROW")){
    Keyboard.press(KEY_LEFT_ARROW);
  }else if (b.equals("RIGHT") || b.equals("RIGHTARROW")){
    Keyboard.press(KEY_RIGHT_ARROW);
  }else if (b.equals("DELETE")){
    Keyboard.press(KEY_DELETE);
  }else if (b.equals("PAGEUP")){
    Keyboard.press(KEY_PAGE_UP);
  }else if (b.equals("PAGEDOWN")){
    Keyboard.press(KEY_PAGE_DOWN);
  }else if (b.equals("HOME")){
    Keyboard.press(KEY_HOME);
  }else if (b.equals("ESC")){
    Keyboard.press(KEY_ESC);
  }else if (b.equals("INSERT")){
    Keyboard.press(KEY_INSERT);
  }else if (b.equals("TAB")){
    Keyboard.press(KEY_TAB);
  }else if (b.equals("END")){
    Keyboard.press(KEY_END);
  }else if (b.equals("CAPSLOCK")){
    Keyboard.press(KEY_CAPS_LOCK);
  }else if (b.equals("F1")){
    Keyboard.press(KEY_F1);
  }else if (b.equals("F2")){
    Keyboard.press(KEY_F2);
  }else if (b.equals("F3")){
    Keyboard.press(KEY_F3);
  }else if (b.equals("F4")){
    Keyboard.press(KEY_F4);
  }else if (b.equals("F5")){
    Keyboard.press(KEY_F5);
  }else if (b.equals("F6")){
    Keyboard.press(KEY_F6);
  }else if (b.equals("F7")){
    Keyboard.press(KEY_F7);
  }else if (b.equals("F8")){
    Keyboard.press(KEY_F8);
  }else if (b.equals("F9")){
    Keyboard.press(KEY_F9);
  }else if (b.equals("F10")){
    Keyboard.press(KEY_F10);
  }else if (b.equals("F11")){
    Keyboard.press(KEY_F11);
  }else if (b.equals("F12")){
    Keyboard.press(KEY_F12);
  }else if (b.equals("SPACE")){
    Keyboard.press(' ');
  }
}
// LOOP FUNCTIONS
void loop(){ // Used to control LEDs
  if (digitalRead(buttonPin) == HIGH){ // If button pressed, strobe LEDs
    TXLED0; //TX LED off
    RXLED1; //RX LED on
    delay(1000); // wait for a second
    TXLED1; //TX LED on
    RXLED0; //RX LED off
    delay(1000); // wait for a second
  }else{ // Else kill LEDS
    TXLED0; //TX LED off
    RXLED0; //RX LED off
  }
}
// CODE END
