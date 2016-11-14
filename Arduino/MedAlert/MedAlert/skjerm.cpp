#include "skjerm.h"
#include "config.h"
#include "wifi.h"
#include "alarm.h"



LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// clear
void SKJERM_clear() {
  lcd.clear();
  }
//Starte skjerm
void SKJERM_start() {
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("Skjerm er klar");
  delay(2000);
  }

//Backlight on
void SKJERM_backlightOn() {
  lcd.setBacklight(HIGH);
  }

// Backlight off
void SKJERM_backlightOff() {
  lcd.setBacklight(LOW);
  }

// Connecting
void SKJERM_kobler(){
  lcd.print ("Kobler opp..");
  delay(2000);
  }
  
// Viser IP adressen
void SKJERM_visIP(){
  lcd.print(wifi_localIP());
}

// Printer ut Error
void SKJERM_error(){
  lcd.print("Error");
}

// Connected
void SKJERM_koblet(IPAddress ip){
  lcd.print ("Koblet til nettverk");
  lcd.setCursor(0,1);
  lcd.print (ip); 
  delay(1000);
  }

// Print alarm
void SKJERM_alarm(uint8_t pakke){
  
switch (pakke) {
  case 1:
  lcd.home();
  lcd.print("Ta kl.07:00");
  lcd.setCursor(0,1);
  lcd.print("medisinen = )");
  ALARM_on();
  delay(2000);
  break;

  case 2:
  lcd.home();
  lcd.print("Ta kl. 13:00");
  lcd.setCursor(0,1);
  lcd.print("medisinen = )");
  ALARM_on();
  delay(2000);
  break;

  case 3: 
  lcd.home();
  lcd.print("Ta kl. 17:00");
  lcd.setCursor(0,1);
  lcd.print("medisinen = )");
  ALARM_on();
  delay(2000);
  break;

  case 4:
  lcd.home();
  lcd.print("Ta kl. 21:00");
  lcd.setCursor(0,1);
  lcd.print("medisinen = )");
  ALARM_on();
  delay(2000);
  break;
  }

  
  }







