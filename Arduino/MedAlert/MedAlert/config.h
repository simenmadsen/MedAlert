#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define REDPIN           3
#define GREENPIN         5
#define BLUEPIN          6
#define BUZZERPIN        3
#define BUTTONPIN        2

/**  Må endres pga annen skjerm   **/
#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7




#define WIFI_SSID        "SimenHuawei"
#define WIFI_PASS        "simen123"

#define LISTENPORT       4000

#define LISTEN_TIMEOUT_US 5000
#define LISTEN_TIMEOUT_NO_DATA_THRESHOLD (15 * (1000000 / LISTEN_TIMEOUT_US))

#endif
