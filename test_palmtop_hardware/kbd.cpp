#include "kbd.h"

void Keyboard::begin() {
    for (int c=0; c<COLS; c++) {
        pinMode(colPins[c], INPUT_PULLUP);
    }

    for (int r=0; r<ROWS; r++) {
        pinMode(rowPins[r], INPUT);
    }
}

char Keyboard::available() {

  static unsigned long startTime = millis();
  
  if (millis() - startTime > DEBOUNCED_INTERVAL) {
    for (int r=0; r<ROWS; r++) {
      
      pinMode(rowPins[r], OUTPUT);
      digitalWrite(rowPins[r], LOW);
      
      for (int c=0; c<COLS; c++) {
        if (digitalRead(colPins[c]) == 0) {
          _keyCode = keys[r][c];
          
          switch (_keyCode) {
            case SI:    // key shift pressed
              _keyState = !_keyState;
              _keyCode = 0;
              break;
            case SO:    // caplock pressed
              _keyState = CAPLOCK;
              _keyCode = 0;
              break;
            default:
              if (_keyState == SHIFTED) {
                _keyCode = keysShifted[r][c];
              }
              else if (_keyState == CAPLOCK) {
                if (_keyCode >='a' && _keyCode<='z') {
                  _keyCode = keys[r][c] - 0x20;  // capital character
                  _keyState = NORMAL;
                }
                else {
                  _keyState = NORMAL;
                }
              }
              break;
          }
          tone(BUZZER, 4000, 50);
          pinMode(rowPins[r], INPUT);
          startTime = millis();
          return _keyCode;
        }
      }
      pinMode(rowPins[r], INPUT);
      startTime = millis();
    }
  }
  return 0;
}

char Keyboard::read() {
  return _keyCode;
}
