## ModulWireless-UART
 Device for send data wireless with wifi (ESP8266) and radio (NRF24l01)

Wireless communication is a communication technology that uses electromagnetic waves to transmit signals with close 
distances and long distances. However, the use of wireless communication modules such as ESP8266 and NRF24L01 for
wireless data transmission learning media for beginners who hadware use some microcontroller like Arduino constrained 
during initial configuration. From the problem it is necessary research about making wireless communication module that
is Plug and Play (PnP) when connected with microcontroller like Arduino. In this research use 2 wirelesss communication
module that are ESP8266 type E-01 and NRF24101 and use serial communication (UART) to connect to microntroler like Arduino Uno. 
here is an ATtmega 328p chip or ATtiny85 chip as an intermediary / serial communication control from ESP8266 or NRF24101
to Arduino Uno acting as a core module. The design of communication module testing ESP8266 and NRF24101 is done in 3 stages of 
introduction, selection, and transmission of PnP communication module data. In the introduction phase - the selection of
communication module using 3 way handshaking process while in the data transmission phase for ESP8266 communication module using MQTT protocol and communication module NRF24101 using RF24 library to make data transmission. The results of data transmission from 21 times the delivery of communication module is 100%. It is influenced by the delivery of data delivery delay, for ESP8266 given delay of at least 1.1 seconds while NRF241 01 given delay at least 1 second. 
