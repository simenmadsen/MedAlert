#ifndef SKJERM_H_INCLUDED
#define SKJERM_H_INCLUDED

#include <WiFi.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

// clear
void SKJERM_clear();
//Starte skjerm
void SKJERM_start();
//Backlight on
void SKJERM_backlightOn();
// Backlight off
void SKJERM_backlightOff();
// Connecting
void SKJERM_kobler();
// Connected
void SKJERM_koblet(IPAddress);
// Print alarm
void SKJERM_alarm(uint8_t);
//Print IP-adressen
void SKJERM_visIP();
// Print error
void SKJERM_error();

#endif

