//SKETCH BY ERIC SIMPSON (DATED 09/18/2020)
//FOR USE IN FIRST ITERATION PROTOTYPE AUTOMATED VERTICAL FARM
#include "header.h"

//TOGGLES ALL DIGITAL PINS SEQUENTIALLY (0 = NO RUN, 1 = RUN, ELSE = NO RUN)
void test_run(int arg) {

  //NO RUN
  if (arg == 0) {
    return;
  }

  //RUN TEST
  else if (arg == 1) {

    //TEST REPORT
    Serial.println(F("\nTESTING OUTPUT PINS..."));

    //THE TRANSPORTER
    Serial.println(F("TRANSPORTER"));
    
    digitalWrite(T_MOTOR1_F, HIGH);
    delay(1000);
    digitalWrite(T_MOTOR1_F, LOW);
    delay(1000);
  
    digitalWrite(T_MOTOR1_R, HIGH);
    delay(1000);
    digitalWrite(T_MOTOR1_R, LOW);
    delay(1000);
    
    digitalWrite(T_MOTOR2_F, HIGH);
    delay(1000);
    digitalWrite(T_MOTOR2_F, LOW);
    delay(1000);
  
    digitalWrite(T_MOTOR2_R, HIGH);
    delay(1000);
    digitalWrite(T_MOTOR2_R, LOW);
    delay(1000);

    digitalWrite(T_MOTOR3_E, HIGH);
    delay(1000);
    digitalWrite(T_MOTOR3_E, LOW);
    delay(1000);
  
    //THE SEEDER
    Serial.println(F("SEEDER"));
    
    digitalWrite(S_MOTOR1, HIGH);
    delay(1000);
    digitalWrite(S_MOTOR1, LOW);
    delay(1000);
  
    //THE HARVESTER
    Serial.println(F("HARVESTER"));
    digitalWrite(H_MOTOR1, HIGH);
    delay(1000);
    digitalWrite(H_MOTOR1, LOW);
    delay(1000);
  
    //THE VALVES
    Serial.println(F("VALVES"));
    digitalWrite(VALVE1, HIGH);
    delay(1000);
    digitalWrite(VALVE1, LOW);
    delay(1000);
  
    digitalWrite(VALVE2, HIGH);
    delay(1000);
    digitalWrite(VALVE2, LOW);
    delay(1000);
    
    digitalWrite(VALVE3, HIGH);
    delay(1000);
    digitalWrite(VALVE3, LOW);
    delay(1000);
  
    digitalWrite(VALVE4, HIGH);
    delay(1000);
    digitalWrite(VALVE4, LOW);
    delay(1000);

    //THE NOTIFICATION LEDS
    Serial.println(F("NOTIFICATION LEDS"));
    
    digitalWrite(STATUS_R, HIGH);
    delay(1000);
    digitalWrite(STATUS_R, LOW);
    delay(1000);
    
    digitalWrite(TRANSPORT_R, HIGH);
    delay(1000);
    digitalWrite(TRANSPORT_R, LOW);
    delay(1000);
  
    digitalWrite(EMPTY_R, HIGH);
    delay(1000);
    digitalWrite(EMPTY_R, LOW);
    delay(1000);
    
    digitalWrite(USED_R, HIGH);
    delay(1000);
    digitalWrite(USED_R, LOW);
    delay(1000);
  
    digitalWrite(RACK_R, HIGH);
    delay(1000);
    digitalWrite(RACK_R, LOW);
    delay(1000);

    //TEST REPORT
    Serial.println(F("\nTEST COMPLETE"));
    
    return;
  }

  //NO RUN
  else {
    return;
  }
}

void request_msg()  {
  Serial.println(F("PLEASE ENTER STATUS: "));
}

int request_status()  {
  
  String sresults_temp = "0";
  int nresults_temp = 0;
  
  if (Serial.available())
  {
    sresults_temp = Serial.readString();
    nresults_temp = sresults_temp.toInt();
    Serial.flush();
  }
  else {digitalWrite(STATUS_R, HIGH); delay(1000); digitalWrite(STATUS_R, LOW);}
  
  delay(1000);
  digitalWrite(STATUS_R, LOW);
  return nresults_temp;
}

//START*****************************************************************************************************************MOTOR CONFIGURATION
void TM1F_r(double rev)
{
  //ONE REVOLUTION IN MILLISECONDS
  double o_rev = 1000;//_________________________________________________________________________________________________________T_MOTOR1_F

  Serial.println("\nSTARTING MOTOR...");

  //LOOP NUMBER OF REQUESTED REVOLUTIONS (REV)
  if (floor(rev) == rev)
  { for (int i = 0; i < (rev); i++)
    {
      digitalWrite(T_MOTOR1_F, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }}
  else
  {
    double pr_rev = rev - floor(rev);
    int pz_rev = floor(rev);
    
    for (int i = 0; i < (pz_rev); i++)
    {
      digitalWrite(T_MOTOR1_F, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }
    digitalWrite(T_MOTOR1_F, HIGH);
    delay(o_rev/pr_rev);
    Serial.print(pr_rev); Serial.print(" REVOLUTIONS\n");
  }

  //SHUT OFF MOTOR AFTER REQUESTED REVOLUTIONS
  digitalWrite(T_MOTOR1_F, LOW);
  Serial.println("STOPPING MOTOR...");
  return;
}
void TM1R_r(double rev)
{
  //ONE REVOLUTION IN MILLISECONDS
  double o_rev = 1000;//_________________________________________________________________________________________________________T_MOTOR1_R

  Serial.println("\nSTARTING MOTOR...");

  //LOOP NUMBER OF REQUESTED REVOLUTIONS (REV)
  if (floor(rev) == rev)
  { for (int i = 0; i < (rev); i++)
    {
      digitalWrite(T_MOTOR1_R, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }}
  else
  {
    double pr_rev = rev - floor(rev);
    int pz_rev = floor(rev);
    
    for (int i = 0; i < (pz_rev); i++)
    {
      digitalWrite(T_MOTOR1_R, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }
    digitalWrite(T_MOTOR1_R, HIGH);
    delay(o_rev/pr_rev);
    Serial.print(pr_rev); Serial.print(" REVOLUTIONS\n");
  }

  //SHUT OFF MOTOR AFTER REQUESTED REVOLUTIONS
  digitalWrite(T_MOTOR1_R, LOW);
  Serial.println("STOPPING MOTOR...");
  return;
}
void TM2F_r(double rev)
{
  //ONE REVOLUTION IN MILLISECONDS
  double o_rev = 1000;//_________________________________________________________________________________________________________T_MOTOR2_F

  Serial.println("\nSTARTING MOTOR...");

  //LOOP NUMBER OF REQUESTED REVOLUTIONS (REV)
  if (floor(rev) == rev)
  { for (int i = 0; i < (rev); i++)
    {
      digitalWrite(T_MOTOR2_F, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }}
  else
  {
    double pr_rev = rev - floor(rev);
    int pz_rev = floor(rev);
    
    for (int i = 0; i < (pz_rev); i++)
    {
      digitalWrite(T_MOTOR2_F, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }
    digitalWrite(T_MOTOR2_F, HIGH);
    delay(o_rev/pr_rev);
    Serial.print(pr_rev); Serial.print(" REVOLUTIONS\n");
  }

  //SHUT OFF MOTOR AFTER REQUESTED REVOLUTIONS
  digitalWrite(T_MOTOR2_F, LOW);
  Serial.println("STOPPING MOTOR...");
  return;
}
void TM2R_r(double rev)
{
  //ONE REVOLUTION IN MILLISECONDS
  double o_rev = 1000;//_________________________________________________________________________________________________________T_MOTOR2_R

  Serial.println("\nSTARTING MOTOR...");

  //LOOP NUMBER OF REQUESTED REVOLUTIONS (REV)
  if (floor(rev) == rev)
  { for (int i = 0; i < (rev); i++)
    {
      digitalWrite(T_MOTOR2_R, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }}
  else
  {
    double pr_rev = rev - floor(rev);
    int pz_rev = floor(rev);
    
    for (int i = 0; i < (pz_rev); i++)
    {
      digitalWrite(T_MOTOR2_R, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }
    digitalWrite(T_MOTOR2_R, HIGH);
    delay(o_rev/pr_rev);
    Serial.print(pr_rev); Serial.print(" REVOLUTIONS\n");
  }

  //SHUT OFF MOTOR AFTER REQUESTED REVOLUTIONS
  digitalWrite(T_MOTOR2_R, LOW);
  Serial.println("STOPPING MOTOR...");
  return;
}
void TM3E_r(double rev)
{
  //ONE REVOLUTION IN MILLISECONDS
  double o_rev = 1000;//_________________________________________________________________________________________________________T_MOTOR3_E

  Serial.println("\nSTARTING MOTOR...");

  //LOOP NUMBER OF REQUESTED REVOLUTIONS (REV)
  if (floor(rev) == rev)
  { for (int i = 0; i < (rev); i++)
    {
      digitalWrite(T_MOTOR3_E, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }}
  else
  {
    double pr_rev = rev - floor(rev);
    int pz_rev = floor(rev);
    
    for (int i = 0; i < (pz_rev); i++)
    {
      digitalWrite(T_MOTOR3_E, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }
    digitalWrite(T_MOTOR3_E, HIGH);
    delay(o_rev/pr_rev);
    Serial.print(pr_rev); Serial.print(" REVOLUTIONS\n");
  }

  //SHUT OFF MOTOR AFTER REQUESTED REVOLUTIONS
  digitalWrite(T_MOTOR3_E, LOW);
  Serial.println("STOPPING MOTOR...");
  return;
}
void SM1_r(double rev)
{
  //ONE REVOLUTION IN MILLISECONDS
  double o_rev = 1000;//___________________________________________________________________________________________________________S_MOTOR1

  Serial.println("\nSTARTING MOTOR...");

  //LOOP NUMBER OF REQUESTED REVOLUTIONS (REV)
  if (floor(rev) == rev)
  { for (int i = 0; i < (rev); i++)
    {
      digitalWrite(S_MOTOR1, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }}
  else
  {
    double pr_rev = rev - floor(rev);
    int pz_rev = floor(rev);
    
    for (int i = 0; i < (pz_rev); i++)
    {
      digitalWrite(S_MOTOR1, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }
    digitalWrite(S_MOTOR1, HIGH);
    delay(o_rev/pr_rev);
    Serial.print(pr_rev); Serial.print(" REVOLUTIONS\n");
  }

  //SHUT OFF MOTOR AFTER REQUESTED REVOLUTIONS
  digitalWrite(S_MOTOR1, LOW);
  Serial.println("STOPPING MOTOR...");
  return;
}
void HM1_r(double rev)
{
  //ONE REVOLUTION IN MILLISECONDS
  double o_rev = 1000;//___________________________________________________________________________________________________________H_MOTOR1

  Serial.println("\nSTARTING MOTOR...");

  //LOOP NUMBER OF REQUESTED REVOLUTIONS (REV)
  if (floor(rev) == rev)
  { for (int i = 0; i < (rev); i++)
    {
      digitalWrite(H_MOTOR1, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }}
  else
  {
    double pr_rev = rev - floor(rev);
    int pz_rev = floor(rev);
    
    for (int i = 0; i < (pz_rev); i++)
    {
      digitalWrite(H_MOTOR1, HIGH);
      delay(o_rev);
      Serial.print(i+1); Serial.print(" REVOLUTIONS\n");
    }
    digitalWrite(H_MOTOR1, HIGH);
    delay(o_rev/pr_rev);
    Serial.print(pr_rev); Serial.print(" REVOLUTIONS\n");
  }

  //SHUT OFF MOTOR AFTER REQUESTED REVOLUTIONS
  digitalWrite(H_MOTOR1, LOW);
  Serial.println("STOPPING MOTOR...");
  return;
}
//END*******************************************************************************************************************MOTOR CONFIGURATION

//EXTENDS PICKS UP THEN RETRACTS TRANSPORTER ARM
void arm_pick() {

  double full_fextension = 10;//______________________________________________________________REVOLUTIONS FORWARD TRANSPORTER ARM EXTENSION
  double full_rextension = 10;//______________________________________________________________REVOLUTIONS REVERSE TRANSPORTER ARM EXTENSION
  double quarter_turn = 0.5;//________________________________________________________________REVOLUTIONS QUARTER TRANSPORTER ARM ROTATIONS
  
  Serial.println("\nEXTENDING ARM...");
  TM2F_r(full_fextension);
  delay(1000);
  Serial.println("\nROTATING ARM (PICKING)...");
  TM3E_r(quarter_turn);
  delay(1000);
  Serial.println("\nRETRACTING ARM...");
  TM2R_r(full_rextension);
  delay(1000);
  Serial.println("\nROTATING ARM (DROPPING)...");
  TM3E_r(quarter_turn);
  return;
}

//EXTENDS DROPS OFF THEN RETRACTS TRANSPORTER ARM
void arm_drop() {

  double full_fextension = 10;//______________________________________________________________REVOLUTIONS FORWARD TRANSPORTER ARM EXTENSION
  double full_rextension = 10;//______________________________________________________________REVOLUTIONS REVERSE TRANSPORTER ARM EXTENSION
  double quarter_turn = 0.5;//________________________________________________________________REVOLUTIONS QUARTER TRANSPORTER ARM ROTATIONS

  
  Serial.println("\nROTATING ARM (PICKING)...");
  TM3E_r(quarter_turn);
  delay(1000);
  Serial.println("\nEXTENDING ARM...");
  TM2F_r(full_fextension);
  delay(1000);
  Serial.println("\nROTATING ARM (DROPPING)...");
  TM3E_r(quarter_turn);
  delay(1000);
  Serial.println("\nRETRACTING ARM...");
  TM2R_r(full_rextension);
  return;
}

//MOVES THE TRANPORTER FROM START TO PLACE
void transport(int start, int place)  {

  Serial.println("\nTRANSPORTING...");
  
  double slot_move = 10;//___________________________________________________________________________NUMBER OF REVOLUTIONS TO MOVE ONE SLOT
  
  //DISTANCE TO TRAVEL IN SLOT MOVES (POS = TM1F AND NEG = TM1R)
  int dist = place - start;

  Serial.print("DISTANCE BETWEEN START AND GOAL IS: "); Serial.print(dist); Serial.print("\n");

  if (dist > 0)
  {
    Serial.println("MOVING FORWARDS");
    for (int i = 0; i < dist; i++)
    {
      TM1F_r(slot_move);
      Serial.print("\nMOVED "); Serial.print(i+1); Serial.print(" SLOTS\n");
    }
  }
  else if (dist < 0)
  {
    Serial.println("MOVING BACKWARDS");
    for (int i = 0; i < (dist*-1); i++)
    {
      TM1R_r(slot_move);
      Serial.print("\nMOVED "); Serial.print(i+1); Serial.print(" SLOTS\n");
    }
  }
  else
  {
    Serial.println("STAYING PUT");
    return;
  }
  return;
}

//ACTIVATES SEEDER
void seed(){
  
  double seeding_duration = 10;//________________________________________________________________________REVOLUTIONS TO FULLY SEED GROW TRAY
  
  Serial.println("\nSEEDING...");
  SM1_r(seeding_duration);
  Serial.println("SEEDING COMPLETE");
  
  return;
}

//OPEN OR CLOSES VALVE
void toggle_valve(int valve, int on)  {

  if (valve == 1)
  {
    if (on == 1)
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" ON...\n");
      digitalWrite(VALVE1, HIGH);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" ON\n");
      return;
    }
    else
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" OFF...\n");
      digitalWrite(VALVE1, LOW);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" OFF\n");
      return;
    }
    
    return;
  }
  if (valve == 2)
  {
    if (on == 1)
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" ON...\n");
      digitalWrite(VALVE2, HIGH);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" ON\n");
    }
    else
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" OFF...\n");
      digitalWrite(VALVE2, LOW);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" OFF\n");
    }
  }
  if (valve == 3)
  {
    if (on == 1)
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" ON...\n");
      digitalWrite(VALVE3, HIGH);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" ON\n");
    }
    else
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" OFF...\n");
      digitalWrite(VALVE3, LOW);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" OFF\n");
    }
  }
  if (valve == 4)
  {
    if (on == 1)
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" ON...\n");
      digitalWrite(VALVE4, HIGH);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" ON\n");
    }
    else
    {
      Serial.print("\nTURNING VALVE "); Serial.print(valve); Serial.print(" OFF...\n");
      digitalWrite(VALVE4, LOW);
      Serial.print("VALVE "); Serial.print(valve); Serial.print(" OFF\n");
    }
  }
  return;
}

//RETURNS CURRENT TIME
unsigned long current_time() {
  return millis();
}

//ACTIVATES HARVESTER
void harvest()  {
  
  double harvesting_duration = 10;//__________________________________________________________________REVOLUTIONS TO FULLY HARVEST GROW TRAY

  Serial.println("\nHARVESTING...");
  SM1_r(harvesting_duration);
  Serial.println("HARVESTING COMPLETE");
  
  return;
}
