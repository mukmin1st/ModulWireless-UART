/*
   Communication Plug and play (PnP)
   modul_esp8266.ino
   Created  by Mukmin on 28/09/2017
   Copyright © 2017 Mukmin. All rights reserved.
*/

#include <SoftwareSerial.h>
SoftwareSerial cetak(2, 3); //(RX , TX)
SoftwareSerial esp8266 (6, 7); //(RX , TX)
int data, codeEsp , isi;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  cetak.begin(9600);
  bool cekGlobal = true;
  bool cek1 = true;
  bool cek2 = false;
  while (cekGlobal) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1500) {
      previousMillis = currentMillis;
      cetak.print(1);
      Serial.println("Handshaking 1 \n");
    } else {
      if (cetak.available() > 0) {
        isi = cetak.parseInt();
        if (cek1) {
          if (isi = 1) {
            Serial.println("Handshaking 2 \n");
            cetak.println("11");
            cek1 = false;
            cek2 = true;
          } delay(100);
        }
        if (cek2) {
          isi = cetak.parseInt();
          if (isi == 11) {
            Serial.println("Handshaking 3 & Modul Siap Kirim \n");
            cetak.println("111");
            cek1 = false;
            cek2 = false;
            cekGlobal = false;
            break;
          } delay(100);
        }
      }
    }
  }
  esp8266.begin(115200);
  previousMillis = 0;
}

void loop() {
  previousMillis = 0;
  if (esp8266.available()) {
    delay(100);
    data = esp8266.parseInt();
    if (data == 0)  Serial.println("connecting wifi ");
    else if (data == 1) Serial.println("wifi connected  ");
    else if (data == 2) Serial.println("connectingBroker");
    else if (data == 3) {
      Serial.println("broker connected"); ; //membaca kode "3"
      int count = 0;
      cetak.listen();
      while (count != 21) {
        isi = cetak.parseInt();
        esp8266.println(isi);
        Serial.print("mengirim data : ");
        Serial.println(isi);
        count++;
        delay(1100);
      }
      Serial.print("Pengiriman Selesai");
    }
    else if (data == 4) Serial.println("error");
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 5000) {
      previousMillis = currentMillis;
      data = esp8266.parseInt();
    }
  }
}




