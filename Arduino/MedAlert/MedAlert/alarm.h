#ifndef ALARM_H_INCLUDED
#define ALARM_H_INCLUDED

#include "util.h"
#include "config.h"
#include "pitches.h"
#include "skjerm.h"
// skrur alarm (lys og buzzer) på 
void ALARM_on();
// skrur alarm av (lys og buzzer) av
void ALARM_off();

void ALARM_init();

#endif

