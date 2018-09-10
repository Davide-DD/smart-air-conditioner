/*
 * INCLUDES
 */

#include <IRremote.h>
#include "CommandsManager.h"


/*
 * CONSTANTS AND ENUM DECLARATIONS
 */

#define LENGTH 99
#define KHZ 38
unsigned int on[LENGTH] = {8900, 4450, 550, 1700, 550, 1650, 550, 550, 600, 500, 600, 550, 550, 550, 550, 550, 550, 1700, 550, 1650, 550, 1700, 550, 550, 550, 1650, 550, 550, 600, 550, 550,550, 550,550, 550,1700, 550,550, 550,550, 550,550, 550,600, 500,600, 550,550, 600,550, 550,550, 550,550, 550,550, 550,600, 550,550, 550,550, 550,550, 550,600, 500,1700, 550,1650, 550,600, 550,550, 550,1650, 550,600, 550,550, 550,550, 550,550, 600,1650, 500,1700, 550,550, 600,1650, 500,600, 550,1650, 550,600, 500};  // NEC C1D08000
unsigned int off[LENGTH] = {8950, 4400, 600, 1650, 550, 1650, 600, 500, 600, 500, 600, 550, 600, 500, 600, 500, 600, 1650, 550, 1650, 600, 1650, 550, 550, 600, 1600, 600, 500, 600, 550, 550,550, 600,500, 600,1650, 550,550, 600,500, 600,500, 600,500, 600,550, 600,500, 600,550, 550,550, 600,500, 600,500, 600,550, 550,1650, 600,500, 600,500, 600,550, 550,1650, 600,1600, 600,550, 550,550, 600,1600, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,1600, 600,500, 600,550, 600,500, 600,1600, 600,500, 600};  // NEC C1D08008
enum mode { power_off, power_on };


/*
 * VARIABLES
 */
 
IRsend irsend; // An IR LED must be connected to the output PWM pin 3;
mode currentMode = power_off;


void setup() {
  Serial.begin(9600);
}


void loop() {
  Serial.println("Waiting for a remote command...");
  
  int command = decodeCommand(); // defined in CommandsManager.h
  Serial.print("Command received: ");
  Serial.println(command);
  
  if(currentMode == power_off) {
    irsend.sendRaw(on, LENGTH, KHZ);
    Serial.println("Sent on");
    currentMode = power_on;
  } else {
    irsend.sendRaw(off, LENGTH, KHZ);
    Serial.println("Sent off");
    currentMode = power_off;
  }
}
