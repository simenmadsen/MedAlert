#include "alarm.h"
#include <arduino.h>

  
void ALARM_init() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}


//Setter på alarm
void ALARM_on(){
  setColor(255,0,0);
  for (int a = 0 ; a < 10; a ++) {
  PITCH_play();
    }
  }
  
 //Slår av alarm
void ALARM_off(){
  setColor(0,255,0);
  PITCH_StopPlay();
  delay(2000);
  setColor(0,0,0);
  }
