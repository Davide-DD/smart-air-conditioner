/*
 * INCLUDES
 */

#include "IRUtils.h"
#include "CommandsManager.h"


/*
 * CONSTANTS AND ENUM DECLARATIONS
 */

#define RECV_PIN 11  // An IR detector/demodulator must be connected to the input RECV_PIN
enum ops { learning, listening, waiting };


/*
 * VARIABLES
 */

IRrecv irrecv(RECV_PIN);
IRsend irsend; // An IR LED must be connected to the output PWM pin 3;
decode_results results;
ops currentOp = learning;
code lastCode;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}


void loop() {
  if (currentOp == learning) {
    Serial.println("Waiting for a IR signal...");
    currentOp = waiting;
  }
  else if (currentOp == listening) {
    Serial.println("Waiting for a remote command...");
  }
  if (currentOp == learning || currentOp == waiting) {
    if (irrecv.decode(&results)) {
      lastCode = storeCode(&results);
      currentOp = listening;
    }
  }
  else {
    int command = decodeCommand();
    Serial.print("Command received: ");
    Serial.println(command);
    irsend.sendRaw(lastCode.durations, lastCode.len, 38);
  }
}
