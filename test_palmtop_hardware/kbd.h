#ifndef _KBD_H_
#define _KBD_H_
/*
 *  The Keyboard is a full function keyboard inspired by Palm Treo650 keyboard.
 *  The keyboard matrix code is based on the original work by Mark Stanley and Alexander Brevig
 *  from http://playground.arduino.cc/Code/Keypad.
 *  
 */
#include <Arduino.h>

#define NAK  0x0   // Not a key
#define SO   0xE   // For representing CapLock key
#define SI   0xF   // For representing Shift key

#define ROWS 4
#define COLS 10

#define BUZZER   PA11

enum {NORMAL, SHIFTED, CAPLOCK};

#define DEBOUNCED_INTERVAL 150

class Keyboard
{
public:

  void begin(void);
  char available();
  char read();

private:

  // GPIO Pins for keyboard matrix
  const uint8_t rowPins[ROWS] = {PD1, PD0, PA15, PA12};  // Row0 - Row3
  const uint8_t colPins[COLS] = {PD2, PD3, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PC13}; //Col0 - Col9

  // Keyboard character map
  const char keys[ROWS][COLS] = {
    // Without Shift
    {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
    {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\b'},
    {'{', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '[', '\n'},
    {NAK,  SI, '+', '~', '=',' ', ',', '<', SO, NAK}
  };
  const char keysShifted[4][10] = {
    // With shift
    {'|', '*', '1', '2', '3', '(', ')', '@', '\"', '\\'},
    {'&', '/', '4', '5', '6', '$', '!', ';', '\'', '\b'},
    {'}', '%', '7', '8', '9', '#', '?', ':', ']', '\n'},
    {NAK, SI, '-', '0', '^', ' ', '.', '>', SO, NAK}
  };

  uint8_t _keyState{NORMAL};
  char _keyCode{0};
};

#endif
