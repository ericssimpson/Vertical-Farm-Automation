//SKETCH BY ERIC SIMPSON (DATED 09/18/2020)
//FOR USE IN FIRST ITERATION PROTOTYPE AUTOMATED VERTICAL FARM
#include "header.h"

//VARIABLE DECLARATIONS
unsigned long rack_status[RACK_SIZE][2] = {0};
int current_location = 0;
int empty_tray = 0;
int used_tray = 0;
int temp_time;

//SETUP CODE TO RUN ON BOOT
void setup() {
  
  //INPUT SETUP
  Serial.begin(9600);
  Serial.println(F("BEGIN SETUP..."));
  
  //THE TRANSPORTER PIN SET
  pinMode(T_MOTOR1_F, OUTPUT);
  pinMode(T_MOTOR1_R, OUTPUT);
  pinMode(T_MOTOR2_F, OUTPUT);
  pinMode(T_MOTOR2_R, OUTPUT);
  pinMode(T_MOTOR3_E, OUTPUT);

  //THE SEEDER PIN SET
  pinMode(S_MOTOR1, OUTPUT);

  //THE HARVESTER PIN SET
  pinMode(H_MOTOR1, OUTPUT);
  
  //THE VALVE PIN SET
  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);

  //THE NOTIFICATION PIN SET
  pinMode(STATUS_R, OUTPUT);
  pinMode(TRANSPORT_R, OUTPUT);
  pinMode(EMPTY_R, OUTPUT);
  pinMode(USED_R, OUTPUT);
  pinMode(RACK_R, OUTPUT);

  Serial.println(F("ALL PINS MARKED AND SETUP"));
  
  //TEST ALL MARKED PINS
  test_run(0);  //0 = NO RUN, 1 = RUN, ELSE = NO RUN
  
  //ASK USER ABOUT CURRENT TRANSPORTER LOCATION (0 INDEXED FROM THE LEFT)
  Serial.println(F("\nNO TIMEOUT (WILL WAIT UNTIL STATUS REPORTED)"));
  Serial.print(F("TRANSPORTER LOCATION: ")); if (current_location == 0){Serial.print(F("NULL"));}
  Serial.println(F("STATUS KEY (1 INDEXED LEFT TO RIGHT FROM TRAY INSERT)"));
  
  request_msg();
  while (current_location == 0)
  {
  digitalWrite(TRANSPORT_R, HIGH);
  current_location = request_status();
  }
  
  Serial.print(F("TRANSPORTER LOCATION: ")); Serial.print(current_location); Serial.print(F("\n"));
  current_location = current_location - 1;
  digitalWrite(TRANSPORT_R, LOW);
  
  //ASK USER ON BOOT WHAT RACK STATUS IS (1 = AVALIABLE, 0 = USED)
  for (int SLOT = 0; SLOT < RACK_SIZE; SLOT++) {
     Serial.println(F("\nTIMEOUT IN 15 SECONDS (WILL DEFAULT TO 0 AVLIABLE)"));
     Serial.print(F("GROW RACK ")); Serial.print(SLOT+1); Serial.print(F(" STATUS: ")); Serial.print(rack_status[SLOT][0]); Serial.print(F("\n"));
     Serial.println(F("STATUS KEY 1 INDEXED LEFT TO RIGHT FROM INSERT AND (0 = USED OR 1 = OPEN)"));
     
    temp_time = 15;
    request_msg();
    while ((temp_time > 0) && (rack_status[SLOT][0] == 0))
    {
       digitalWrite(RACK_R, HIGH);
       rack_status[SLOT][0] = request_status();
       temp_time = temp_time - 1;
       digitalWrite(RACK_R, LOW);
    }
    rack_status[SLOT][1] = 0;
    
    if (temp_time == 0)
    {
      rack_status[SLOT][0] = 0;
      Serial.println(F("STATUS DEFAULTED TO 0"));
    }
    Serial.print(F("GROW RACK ")); Serial.print(SLOT+1); Serial.print(F(" STATUS: ")); Serial.print(rack_status[SLOT][0]); Serial.print(F("\n"));
    digitalWrite(RACK_R, LOW);
  }
  //COMPLETED SETUP
  Serial.println(F("\nSET UP COMPLETE"));
}

//MAIN CODE TO RUN CONSTANTLY
void loop() {
  
  //ASK USER ABOUT EMPTY TRAY SLOT AVALIABLE (FULL = 1, EMPTY = 0)
  Serial.println(F("\nTIMEOUT IN 15 SECONDS (WILL DEFAULT TO 0 AVLIABLE)"));
  Serial.print(F("EMPTY TRAYS ")); Serial.print(F("STATUS KEY (0 = NO TRAYS OR 1 = ONE TRAY)\n"));

  temp_time = 15;
  request_msg();
  while ((temp_time > 0) && (empty_tray == 0))
  {
     digitalWrite(EMPTY_R, HIGH);
     empty_tray = request_status();
     temp_time = temp_time - 1;
     digitalWrite(EMPTY_R, LOW);
  }
  if (temp_time == 0)
    {
      empty_tray = 0;
      Serial.println(F("STATUS DEFAULTED TO 0"));
    }
  Serial.print(F("NUMBER OF EMPTY TRAYS: ")); Serial.print(empty_tray); Serial.print(F("\n"));
  digitalWrite(EMPTY_R, LOW);

  //ASK USER ABOUT USED TRAY SLOT AVALIABLE (EMPTY = 1, FULL = 0)
  Serial.println(F("\nTIMEOUT IN 15 SECONDS (WILL DEFAULT TO ONE USED (0))"));
  Serial.print(F("USED TRAYS ")); Serial.print(F("STATUS KEY (1 = NOT USED OR 0 = ONE USED)\n"));

  temp_time = 15;
  request_msg();
  while ((temp_time > 0) && (used_tray == 0))
  {
     digitalWrite(USED_R, HIGH);
     used_tray = request_status();
     temp_time = temp_time - 1;
     digitalWrite(USED_R, LOW);
  }
  if (temp_time == 0)
    {
      used_tray = 0;
      Serial.println(F("STATUS DEFAULTED TO 0 (ONE USED)"));
    }
  Serial.print(F("NUMBER OF AVLIABLE USED TRAY SLOTS: ")); Serial.print(used_tray); Serial.print(F("\n"));
  digitalWrite(USED_R, LOW);

  //REPORT INPUT COMPLETE
  Serial.println(F("\nINPUT COMPLETE"));
  Serial.println(F("\nEVALUATING FARMING PROCESS..."));

  //IF EMPTY TRAY AVALIABLE THEN CONSIDER SEEDING
  Serial.println(F("\nCONSIDERING SEEDING..."));
  if (empty_tray == 1)  {

    Serial.println(F("EMPTY TRAY FOUND"));
    
    //CHECKS IF AND WHERE A OPEN RACK EXISTS TO PUT A SEEDED GROW TRAY
    Serial.println(F("SEARCHING FOR OPEN RACK..."));
    for (int SLOT = 0; SLOT < RACK_SIZE; SLOT++) {

      if (empty_tray == 0)
      {
        Serial.println(F("\nCONSIDERING SEEDING..."));
        Serial.println(F("NO EMPTY TRAYS FOUND"));
        return;
      }

      /*Serial.println("\nDEBUG");
      Serial.println(SLOT);
      Serial.println(rack_status[SLOT][0]);
      Serial.println(rack_status[SLOT][1]);
      Serial.println("DEBUG\n");
      delay(5000);*/
      
      int OPEN = 1;
      int CLOSED = 0;
      
      if (rack_status[SLOT][0] == CLOSED) {
        Serial.print(F("GROW RACK ")); Serial.print(SLOT+1); Serial.print(F(" CLOSED\n"));
      }
  
      if (rack_status[SLOT][0] == OPEN) {

        Serial.print(F("GROW RACK ")); Serial.print(SLOT+1); Serial.print(F(" OPEN\n"));
        Serial.println(F("GROW RACK SLOT FOUND"));

        //SUBTRACT 1 TRAY FROM EMPTY TRAY SLOT
        Serial.println(F("RESERVING EMPTY TRAY"));
        empty_tray = empty_tray - 1;
        
        //GO TO EMPTY TRAY SPOT AND PICK UP TRAY
        Serial.println(F("PICKING UP EMPTY TRAY"));
        transport(current_location, EMPTY); 
        arm_pick();
        current_location = EMPTY;

        //GO TO SEEDER SPOT AND DROP OFF TRAY
        Serial.println(F("SEEDING TRAY"));
        transport(current_location, SEEDER);
        arm_drop();
        current_location = SEEDER;

        //ACTIVATE SEEDER
        seed();

        //PICK UP FROM SEEDER THEN DROP OFF TRAY IN OPEN RACK
        Serial.println(F("MOVING TRAY TO OPEN GROW RACK SLOT"));
        arm_pick();
        transport(current_location, SLOT + 2);
        arm_drop();

        //MARK OPEN RACK CLOSED AND RECORD TIME
        Serial.println(F("RESERVING GROW RACK SLOT"));

        /*Serial.println("\nDEBUG");
        Serial.println(SLOT);
        Serial.println(rack_status[SLOT][0]);
        Serial.println(rack_status[SLOT][1]);
        Serial.println("DEBUG\n");*/
        
        rack_status[SLOT][0] = CLOSED;
        rack_status[SLOT][1] = current_time();

        /*Serial.println("\nDEBUG");
        Serial.println(SLOT);
        Serial.println(rack_status[SLOT][0]);
        Serial.println(rack_status[SLOT][1]);
        Serial.println("DEBUG\n");
        delay(5000);*/

        //ACTIVATE VALVE FOR GROWING
        Serial.println(F("OPENING VALVE"));
        toggle_valve(SLOT + 2, OPEN);
        
        //GO TO BACK TO POSITION ONE (SEEDING LOCATION)
        Serial.println(F("RETURNING TO DEFAULT POSITION AT SEEDER"));
        transport(current_location, SEEDER); 
        current_location = SEEDER;
      }
    }
  }
  else  {
    Serial.println(F("NO EMPTY TRAYS FOUND"));
  }
  
  //IF USED TRAY SLOT EMPTY THEN CONSIDER HARVESTING
  Serial.println(F("\nCONSIDERING HARVESTING..."));
  if (used_tray == 1) {

    Serial.println(F("USED TRAY LOCATION EMPTY"));
    
    //CHECKS IF AND WHERE A READY TO HARVEST RACK EXISTS THEN HARVESTS
    Serial.println(F("SEARCHING FOR READY TO HARVEST GROW RACK..."));
    for (int SLOT = 0; SLOT < RACK_SIZE; SLOT++) {

      if (used_tray == 0)
      {
        Serial.println(F("\nCONSIDERING HARVESTING..."));
        Serial.println(F("NO READY TO HARVEST TRAY SPOTS OPEN"));
        return;
      }
      
      /*Serial.println("\nDEBUG");
      Serial.println(SLOT);
      Serial.println(rack_status[SLOT][0]);
      Serial.println(rack_status[SLOT][1]);
      Serial.println("DEBUG\n");
      delay(5000);*/
  
      int OPEN = 1;
      int CLOSED = 0;
  
      if ((rack_status[SLOT][0] == OPEN) || ((current_time() - rack_status[SLOT][1]) <= GROWTIME)) {
        Serial.print(F("GROW RACK ")); Serial.print(SLOT+1); Serial.print(F(" NOT READY\n"));
      }
  
      if ((rack_status[SLOT][0] == CLOSED) && ((current_time() - rack_status[SLOT][1]) > GROWTIME)) {

        Serial.print(F("GROW RACK ")); Serial.print(SLOT+1); Serial.print(F(" READY\n"));
        Serial.println(F("GROW RACK SLOT FOUND"));

        //SUBTRACT 1 FROM AVLIABLE USED TRAY SPOT
        Serial.println(F("RESERVING USED TRAY SLOT"));
        used_tray = used_tray - 1;
        
        //DEACTIVATE VALVE FOR GROWING
        Serial.println(F("TURNING OFF VALVE"));
        toggle_valve(SLOT + 2, CLOSED);
        
        //GO TO READY TO HARVEST TRAY SPOT AND PICK UP TRAY
        Serial.println(F("PICKING UP READY TO HARVEST TRAY"));
        transport(current_location, SLOT + 2);
        arm_pick();
        current_location = SLOT + 2;
  
        //GO TO HARVESTER AND DROP OFF TRAY
        Serial.println(F("HARVESTING TRAY"));
        transport(current_location, HARVESTER);
        arm_drop();
        current_location = HARVESTER;
  
        //ACTIVATE HARVESTER
        harvest();
  
        //PICK UP FROM HARVESTER THEN DROP OFF TRAY IN USED RACK
        Serial.println(F("MOVING TRAY TO USED TRAY SLOT"));
        arm_pick();
        transport(current_location, USED);
        arm_drop();
  
        //MARK CLOSED RACK OPEN AND ERASE TIME
        Serial.println(F("MARKING READY TO HARVEST RACK OPEN"));
        
        /*Serial.println("\nDEBUG");
        Serial.println(SLOT);
        Serial.println(rack_status[SLOT][0]);
        Serial.println(rack_status[SLOT][1]);
        Serial.println("DEBUG\n");*/
        
        rack_status[SLOT][0] = OPEN;
        rack_status[SLOT][1] = 0;

        /*Serial.println("\nDEBUG");
        Serial.println(SLOT);
        Serial.println(rack_status[SLOT][0]);
        Serial.println(rack_status[SLOT][1]);
        Serial.println("DEBUG\n");
        delay(5000);*/
  
        //GO TO BACK TO POSITION ONE (SEEDING LOCATION)
        Serial.println(F("RETURNING TO DEFAULT POSITION AT SEEDER"));
        transport(current_location, SEEDER);
        current_location = SEEDER;
      }
    }
  }
  else {
    Serial.println(F("NO READY TO HARVEST TRAY SPOTS OPEN"));
  }
  Serial.println(F("\nEND OF ONE SEED TO HARVEST CYCLE\n"));
  delay(60000);
}
  
