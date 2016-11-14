#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "config.h"
#include "alarm.h"

//  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), BUTTON_isr(), CHANGE);

//initiere knapp
void BUTTON_init();
//interupt sekvens
void BUTTON_isr();

#endif
