#include "button.h"
#include "statemachine.h"
#include <arduino.h>

volatile int buttonState = 0;

//initiere knapp
void BUTTON_init(){
  pinMode(BUTTONPIN,INPUT);
  }
//interupt sekvens
void BUTTON_isr(){
  buttonState = digitalRead(BUTTONPIN);
  ALARM_off();
  sm_process_signals();
  }

