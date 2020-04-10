//SKETCH BY ERIC SIMPSON (DATED 09/18/2020)
//FOR USE IN FIRST ITERATION PROTOTYPE AUTOMATED VERTICAL FARM
#include "Arduino.h"

//IF DEFINED SKIP
#ifndef HEADER_H
#define HEADER_H

//GROW RACK CONFIGURATION

  //TOTAL NUMBER OF GROW SLOTS AVALIABLE
  const int RACK_SIZE = 2;

  //SEEDER LOCATION (LEFT TO RIGHT FROM TRAY INSERT 0 INDEX)
  const int SEEDER = 0;

  //EMPTY LOCATION (LEFT TO RIGHT FROM TRAY INSERT 0 INDEX)
  const int EMPTY = 1;

  //USED LOCATION (LEFT TO RIGHT FROM TRAY INSERT 0 INDEX)
  const int USED = 4;

  //HARVESTER LOCATION (LEFT TO RIGHT FROM TRAY INSERT 0 INDEX)
  const int HARVESTER = 5;

  //LENGTH OF GROW PERIOD FOR SEEDS
  const unsigned long GROWTIME = 5000;
  
//THE PINS SELECTED FOR EACH PART

  //THE TRANSPORTER
  //FORWARD AND REVERSE PINS FOR RELAY TO MOTOR FOR TRACK
  const int T_MOTOR1_F = 2;//150
  const int T_MOTOR1_R = 3;
  //FORWARD AND REVERSE PINS FOR RELAY TO MOTOR ON ARM
  const int T_MOTOR2_F = 4;//200
  const int T_MOTOR2_R = 5;
  //ROTATE PINS FOR RELAY TO MOTOR ON ARM
  const int T_MOTOR3_E = 6;//87
  
  //THE SEEDER
  const int S_MOTOR1 = 7;//87

  //THE HARVESTER
  const int H_MOTOR1 = 8;//6000

  //THE VALVES (ORIENTED LEFT TO RIGHT FROM TRAY INSERTION PERSPECTIVE 1 INDEX)
  const int VALVE1 = 9;
  const int VALVE2 = 10;
  const int VALVE3 = 11;
  const int VALVE4 = 12;
  
  //THE REQUEST USER INPUT NOTIFICATION
  const int STATUS_R = 14; //A0
  const int TRANSPORT_R = 15; //A1
  const int EMPTY_R = 16; //A2
  const int USED_R = 17; //A3
  const int RACK_R = 18; //A4

//TOGGLES ALL RELAYS SEQUENTIALLY
void test_run(int arg);

//ASKS USER TO ENTER NUMBER SIGNIFYING STATUS
void request_msg();
int request_status();

//START*****************************************************************************************************************MOTOR CONFIGURATION
void TM1F_r(double rev);
void TM1R_r(double rev);
void TM2F_r(double rev);
void TM2R_r(double rev);
void TM3E_r(double rev);
void SM1_r(double rev);
void HM1_r(double rev);
//END*******************************************************************************************************************MOTOR CONFIGURATION

//EXTENDS PICKS UP THEN RETRACTS TRANSPORTER ARM
void arm_pick();

//EXTENDS DROPS OFF THEN RETRACTS TRANSPORTER ARM
void arm_drop();

//MOVES THE TRANPORTER FROM START TO PLACE
void transport(int start, int place);

//ACTIVATES SEEDER
void seed();

//OPEN OR CLOSES VALVE
void toggle_valve(int valve, int on);

//RETURNS CURRENT TIME
unsigned long current_time();

//ACTIVATES HARVESTER
void harvest();

#endif
