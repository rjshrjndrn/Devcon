//Arduino code
#include <SoftwareSerial.h>
SoftwareSerial s(7,8); // Rx, Tx
 
void setup() {
s.begin(9600);
Serial.begin(9600);
}
 
void loop() {
int data=50;

 s.write("567.44 PPM\n");
delay(1000);
Serial.write("567.44 PPM\n");
}

