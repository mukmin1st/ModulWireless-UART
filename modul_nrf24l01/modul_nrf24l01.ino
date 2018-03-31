/*
   Communication Plug and play (PnP)
   modul_NRF24l01.ino
   Created  by Mukmin on 28/09/2017
   Copyright © 2017 Mukmin. All rights reserved.
*/
#include <SoftwareSerial.h>
#include "RF24.h"
SoftwareSerial cetak(3 , 4); // (RX TX)
RF24 radio(3, 3);

byte address[11] = "SimpleNode";
unsigned long payload;
unsigned long previousMillis = 0;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  cetak.begin(9600);
  int isi1;
  bool cekGlobal = true;
  bool cek1 = true;
  bool cek2 = false;
  while (cekGlobal) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1500) {
      previousMillis = currentMillis;
      cetak.print(2); //Handshaking 1
    } else {
      if (cetak.available() > 0) {
        isi1 = cetak.parseInt();
        if (cek1) {
          if (isi1 == 2) {
            cetak.println(22);//Handshaking 2
            cek1 = false;
            cek2 = true;
          } delay(100);
        }
        if (cek2) {
          isi1 = cetak.parseInt();
          if (isi1 == 22) {
            cetak.println(222);//Handshaking 3
            cek1 = false;
            cek2 = false;
            cekGlobal = false;
            break;
          } delay(100);
        }
      }
    }
  }
}

void loop(void) {
  int count = 0;
  cetak.listen();
  if (cetak.available() > 0) {
    while (count != 21) {
      payload = cetak.parseInt();
      radio.write( &payload, sizeof(unsigned long) ); //Send data to 'Receiver' ever second
      count++;
      delay(1000);
    }
    delay(5000);
  }
}


 



















