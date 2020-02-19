//node mcu
#include <SoftwareSerial.h>
SoftwareSerial s(D2,D6); // Rx, Tx
char data;
void setup() {
s.begin(9600);
Serial.begin(9600);
}
 
void loop() {
  Serial.println("in loop\n");
  if (s.available()>0)
  {
    data=s.read();
    Serial.println(data);
  }
  delay(1000);
}

