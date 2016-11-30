/*******************************************************************************
 * 
 * Arduino-Gmail
 * ----------------
 * 
 * An example project for INFO361 / Advanced Topics in Human-Computer Interaction
 * University of Bergen, 2016
 * 
  ******************************************************************************/

#include "TimerOne.h"
#include "config.h"
#include "util.h"
#include "wifi.h"
#include "statemachine.h"
#include "skjerm.h"
#include "alarm.h"
#include "pitches.h"
#include "button.h"


/************************************ STATES **********************************/
t_state s_fatal_err, s_init, s_init_timer, s_init_wifi, s_init_udp, s_listen;





// Error state
void s_fatal_err_enter() {
  SKJERM_error();
  delay(5000);
  resetDevice();
}

// Initierer funksjoner
void s_init_enter() {
  MCUSR = 0; // Reset watchdog flags
  SKJERM_start();
  BUTTON_init();
  sm_emit(SIGSUCC);
}

/**  Starter timeren   **/
void s_init_timer_enter() {
  Timer1.initialize(); 
  sm_emit(SIGSUCC);
}

/**  Starter Wifi og kobler til ruteren   **/
void s_init_wifi_enter() {
  SKJERM_backlightOn();
  SKJERM_clear();
  SKJERM_kobler();
  wifi_connect(); // This blocks until connection is established
  SKJERM_clear();
  SKJERM_visIP();
  
  sm_emit(SIGSUCC);
}

/**  Stopper wifi animasjonen for å kunne bruke Skjermen til noe annet   **/
void s_init_wifi_exit() {
  delay(8000);
  SKJERM_clear();
}

/**  Mottar udp pakker, gir error dersom ikke pakker, suksess for sendte pakker   **/
void s_init_udp_enter() {
  if (!serv_start()) {
    sm_emit(SIGERR);
  } else {
    sm_emit(SIGSUCC);
  }
}

/**  Fungerer som en update, bare 100ganger i sekundet   **/
void s_listen_enter() {
  serv_start_polltimer();
}

void s_listen_exit() {
  serv_stop_polltimer();
}

/**  Mottar og sender signaler, dersom noe skjer sier ifra til statemaskinen   **/
void s_listen_signal(t_sig *s) {
  t_data_recv buf;
  int status = wifi_status();

  switch (s->type) {

    case sig_timeout:
      if (serv_getdata(&buf)) { //venter på pakke, pakker den ut
        SKJERM_alarm(buf.pakke);
      // Strange phenomenon: WiFi Shield sometimes randomly believes it is not present, and returns WL_NO_SHIELD
      // although it is attached and seemingly working. This check incorporates a workaround.
      } else if (status != WL_CONNECTED && status != WL_NO_SHIELD) {
        sm_emit(SIGCONNLOST);
      } 
  }
}

/********************************** END STATES ********************************/

/**  Stater   **/


void setup() {
 
 BUTTON_init();
 attachInterrupt(digitalPinToInterrupt(BUTTONPIN), BUTTON_isr, CHANGE);
 
  s_fatal_err   = { .onEnter       = s_fatal_err_enter, 
                    .onExit        = NULL, 
                    .onSignal      = NULL,
                    .transitions   = { 
                        .success   = NULL, 
                        .err       = NULL,
                        .timeout   = NULL,
                        .conn_lost = NULL,
                        .no_server = NULL}};

  s_init        = { .onEnter       = s_init_enter, 
                    .onExit        = NULL, 
                    .onSignal      = NULL,
                    .transitions   = { 
                        .success   = &s_init_timer, 
                        .err       = &s_fatal_err,
                        .timeout   = NULL,
                        .conn_lost = NULL,
                        .no_server = NULL}};

  s_init_timer  = { .onEnter       = s_init_timer_enter, 
                    .onExit        = NULL, 
                    .onSignal      = NULL,
                    .transitions   = { 
                        .success   = &s_init_wifi, 
                        .err       = &s_fatal_err,
                        .timeout   = NULL,
                        .conn_lost = NULL,
                        .no_server = NULL}};

  s_init_wifi   = { .onEnter       = s_init_wifi_enter, 
                    .onExit        = s_init_wifi_exit, 
                    .onSignal      = NULL,
                    .transitions   = { 
                        .success   = &s_init_udp, 
                        .err       = &s_fatal_err,
                        .timeout   = NULL,
                        .conn_lost = NULL,
                        .no_server = NULL}};

  s_init_udp    = { .onEnter       = s_init_udp_enter, 
                    .onExit        = NULL, 
                    .onSignal      = NULL,
                    .transitions   = { 
                        .success   = &s_listen, 
                        .err       = &s_fatal_err,
                        .timeout   = NULL,
                        .conn_lost = NULL,
                        .no_server = NULL}};


  s_listen      = { .onEnter       = s_listen_enter,   
                    .onExit        = s_listen_exit, 
                    .onSignal      = s_listen_signal,
                    .transitions   = { 
                        .success   = NULL, 
                        .err       = &s_fatal_err,
                        .timeout   = NULL,
                        .conn_lost = &s_init_wifi,
                        .no_server = NULL}};

sm_init(&s_init);


}

void loop() {
  sm_process_signals();
}
