#include "button.h"
#include "statemachine.h"
#include <arduino.h>

volatile int buttonState = 0;

//initiere knapp
void BUTTON_init(){
  pinMode(BUTTONPIN,INPUT_PULLUP);
  }
//interupt sekvens
void BUTTON_isr(){
  ALARM_off();
  }

