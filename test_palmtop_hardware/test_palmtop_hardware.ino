/* 
 *  PalmTop - A STM32G070-based Development Board with keyboard, display and a BASIC interpreter
 *  
 *  The pin definitions using in this code is the hardware design of PalmTop board. It requires
 *  a custom board configuration based on stm32duino Arduino_Core_STM32 for PalmTop.
*/

#include <UC1609.h>
#include "image.h"
#include "kbd.h"


// UC1609 display settings
#define CD       PA10
#define CS       PA4
#define RST      -1    // share with MCU's NRST pin

#define CONTRAST 0x38

UC1609 lcd(CS, CD, RST);
Keyboard keyboard;


void startUpScreen() {
  lcd.drawImage(0, 0, 192, 64, logo);
  tone(BUZZER, 4000, 500);
  delay(2000);
  lcd.clearDisplay();
}

void setup() {

  pinMode(BUZZER, OUTPUT);

  keyboard.begin();

  delay(3);     // for LCD to get ready after powering up
  lcd.begin(CONTRAST);
  lcd.setFont(font5x7_extended);

  startUpScreen();

}

void loop() {

  if (keyboard.available()) {
    char c = keyboard.read();
    lcd.write(c);
  }

  delay(1);

}
