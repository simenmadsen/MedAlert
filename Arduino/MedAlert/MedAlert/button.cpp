#include "button.h"
#include "statemachine.h"
#include <arduino.h>

//initiere knapp
void BUTTON_init(){
  pinMode(BUTTONPIN,INPUT_PULLUP);
  }
//interupt sekvens
void BUTTON_isr(){
  ALARM_off();
  }

