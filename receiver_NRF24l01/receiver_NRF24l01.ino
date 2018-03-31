#define CE_PIN 9
#define CSN_PIN 10
#include <SPI.h>
#include "RF24.h"

RF24 radio(CE_PIN, CSN_PIN);
byte address[11] = "SimpleNode";
unsigned long payload = 0;

void setup() {
  Serial.begin(115200);
  radio.begin(); // Start up the radio  
  radio.openReadingPipe(1, address); // Write to device address 'SimpleNode'
  radio.startListening();
}

void loop(void) {
  radio.read( &payload, sizeof(unsigned long));
  if (payload != 0) {
    Serial.print("Accepted : ");
    Serial.println(payload);
  } else {
    Serial.println("NRF24L01 belum Terdeteksi");
  }
  delay(1000);
}


