#ifndef IRUTILS_H
#define IRUTILS_H

#include <IRremote.h>

// Storage for the recorded code
typedef struct {
    int type; // The type of code
    unsigned long value; // The code value if not raw
    unsigned int durations[RAWBUF]; // The durations if raw
    int len; // The length of the code
    int toggle; // The RC5/6 toggle state
} code;


// Stores the code for later playback
// Most of this code is just logging
code storeCode(decode_results *results) {
  code lastCode;

  lastCode.type = results->decode_type;
  int count = results->rawlen;
  if (lastCode.type == UNKNOWN) {
    Serial.println("Received unknown code, saving as raw");
    lastCode.len = results->rawlen - 1;
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= lastCode.len; i++) {
      if (i % 2) {
        // Mark
        lastCode.durations[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      } 
      else {
        // Space
        lastCode.durations[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(lastCode.durations[i - 1], DEC);
    }
    Serial.println("");
  }
  else {
    if (lastCode.type == NEC) {
      Serial.print("Received NEC: ");
      if (results->value == REPEAT) {
        // Don't record a NEC repeat value as that's useless.
        Serial.println("repeat; ignoring.");
        return;
      }
    } 
    else if (lastCode.type == SONY) {
      Serial.print("Received SONY: ");
    } 
    else if (lastCode.type == PANASONIC) {
      Serial.print("Received PANASONIC: ");
    }
    else if (lastCode.type == JVC) {
      Serial.print("Received JVC: ");
    }
    else if (lastCode.type == RC5) {
      Serial.print("Received RC5: ");
    } 
    else if (lastCode.type == RC6) {
      Serial.print("Received RC6: ");
    } 
    else {
      Serial.print("Unexpected codeType ");
      Serial.print(lastCode.type, DEC);
      Serial.println("");
    }
    Serial.println(results->value, HEX);
    lastCode.value = results->value;
    lastCode.len = results->bits;
  }

  return lastCode;
}

void sendCode(IRsend irsend, code lastCode, int repeat) {
  if (lastCode.type == NEC) {
    if (repeat) {
      irsend.sendNEC(REPEAT, lastCode.len);
      Serial.println("Sent NEC repeat");
    } 
    else {
      irsend.sendNEC(lastCode.value, lastCode.len);
      Serial.print("Sent NEC ");
      Serial.println(lastCode.value, HEX);
    }
  } 
  else if (lastCode.type == SONY) {
    irsend.sendSony(lastCode.value, lastCode.len);
    Serial.print("Sent Sony ");
    Serial.println(lastCode.value, HEX);
  } 
  else if (lastCode.type == PANASONIC) {
    irsend.sendPanasonic(lastCode.value, lastCode.len);
    Serial.print("Sent Panasonic");
    Serial.println(lastCode.value, HEX);
  }
  else if (lastCode.type == JVC) {
    irsend.sendJVC(lastCode.value, lastCode.len, false);
    Serial.print("Sent JVC");
    Serial.println(lastCode.value, HEX);
  }
  else if (lastCode.type == RC5 || lastCode.type == RC6) {
    if (!repeat) {
      // Flip the toggle bit for a new button press
      lastCode.toggle = 1 - lastCode.toggle;
    }
    // Put the toggle bit into the code to send
    lastCode.value = lastCode.value & ~(1 << (lastCode.len - 1));
    lastCode.value = lastCode.value | (lastCode.toggle << (lastCode.len - 1));
    if (lastCode.type == RC5) {
      Serial.print("Sent RC5 ");
      Serial.println(lastCode.value, HEX);
      irsend.sendRC5(lastCode.value, lastCode.len);
    } 
    else {
      irsend.sendRC6(lastCode.value, lastCode.len);
      Serial.print("Sent RC6 ");
      Serial.println(lastCode.value, HEX);
    }
  } 
  else if (lastCode.type == UNKNOWN /* i.e. raw */) {
    // Assume 38 KHz
    irsend.sendRaw(lastCode.durations, lastCode.len, 38);
    Serial.println("Sent raw");
  }
}

#endif
