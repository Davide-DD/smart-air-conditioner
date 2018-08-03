#include "IRUtils.h"


int RECV_PIN = 11;  // An IR detector/demodulator must be connected to the input RECV_PIN

IRrecv irrecv(RECV_PIN);
IRsend irsend; // An IR LED must be connected to the output PWM pin 3;

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}


enum ops { learning, listening };

enum ops currentOp = learning;
code lastCode;
int lastButtonState;

void loop() {
  if (currentMode == learning) {
    Serial.println("Waiting for an IR signal...");
    if (irrecv.decode(&results)) {
      lastCode = storeCode(&results);
      // TODO: check repeat meaning in storeCode and sendCode functions
    }
  }
  else {
    Serial.println("Waiting for a remote command...");
    int command = decodeCommand();
    Serial.print("Command received: ");
    Serial.println(command);
    sendCode(irsend, lastCode);
  }
}

int decodeCommand() {
  while(Serial.available()==0);
  return Serial.parseInt();
}

