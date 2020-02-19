//Arduino code
#include <SoftwareSerial.h>
SoftwareSerial s(7,8); // Rx, Tx
 
void setup() {
s.begin(9600);
Serial.begin(9600);
}
 
void loop() {
int data=50;

 s.write('5');
delay(1000);
Serial.write('5');
}

