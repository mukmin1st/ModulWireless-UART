/*
   Communication Plug and play (PnP)
   core_modul.ino
   Created  by Mukmin on 28/09/2017
   Copyright © 2017 Mukmin. All rights reserved.
*/

#include <SoftwareSerial.h>
SoftwareSerial cetak1(2, 3); // RX, TX
bool cekGlobal1 = true;
bool cekGlobal2 = true;
int data1, data2;
#define sensorPin A0

void setup() {
  Serial.begin(9600);
  cetak1.begin(9600);
}

void loop() {
  cekGlobal1 = true;
  Serial.println("\nMENU CORE MODUL");  ;
  Serial.println("Tekan k Untuk Scanning Modul Komunikasi");
  system ("cls");
  while (!Serial.available());
  char pilihan = Serial.read();
  switch (pilihan) {
    case 'k':
      while (cekGlobal1) {
        if (cekGlobal2) {
          Serial.println("Scanner Modul Komunikasi.......... \n");
          while (cetak1.available() > 0 ) {
            data1 = cetak1.parseInt();
            if (data1 != NULL ) {
              scan1(data1);
              break;
            }
          }
          delay(500);
        } else {
          int sensorValue;
          sensorValue = analogRead(A0); // read the value from the sensor
          Serial.print("Mengirim data serial !! ");
          Serial.println(sensorValue);
          cetak1.println(sensorValue);
          delay(1000);
        }
      }
  }
}

void scan1(int data1) {
  bool cek1 = true;
  bool cek2 = false;
  int isi1, isi2;
  if (data1 == 1 ) {
    Serial.println("Modul Komunikasi ESP8266 terdeteksi"); //Handshaking 1 
    cetak1.println(1);
    if (cek1) {
      isi1 = cetak1.parseInt();
      if (isi1 =11 ) {
        Serial.println("Modul Komunikasi ESP8266 telah dipilih");//Handshaking 2
        cetak1.println(11);
        cek1 = false;
        cek2 = true;
      } delay(100);
    } if (cek2) {
      int data = cetak1.parseInt();
      if (data == 111) {
        Serial.println("Proses kirim dimulai"); //Handshaking 3
        cek1 = false;
        cek2 = false;
        cekGlobal2 = false;
      } delay(100);
    }
  } else if ( data1 == 2) {
    Serial.println("Modul Komunikasi NRF24l01 terdeteksi"); //Handshaking 1 
    cetak1.println(2);
    if (cek1) {
      isi1 = cetak1.parseInt();
      if (isi1 = 22 ) {
        Serial.println("Modul Komunikasi NRF24l01 telah dipilih");//Handshaking 2 
        cetak1.println(22);
        cek1 = false;
        cek2 = true;
      } delay(100);
    } if (cek2) {
      int data = cetak1.parseInt();
      if (data == 222) {
        Serial.println("Proses kirim dimulai"); //Handshaking 3 
        cek1 = false;
        cek2 = false;
        cekGlobal2 = false;
      } delay(100);
    }
  }
}





