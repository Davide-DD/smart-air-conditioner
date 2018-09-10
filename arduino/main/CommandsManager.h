#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

/*
 * Simulates a communication with a control center
 * that sends commands (as integers) to execute
 */
int decodeCommand() {
  while(Serial.available()==0);
  return Serial.parseInt();
}


#endif
