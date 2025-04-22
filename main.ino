#include "Ultrasonic.h"
#define fail_pin 6

HC_SR04 sensor_true(8, 12);
HC_SR04 sensor_backup(2, 3);

int on = 5;
int off = 4;
int backup = 7;
int distance;

void setup() {
  pinMode(on, OUTPUT);
  pinMode(off, OUTPUT);
  pinMode(backup, OUTPUT);

  pinMode(fail_pin, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  bool fail = digitalRead(fail_pin);
  Serial.println(fail);

  if(!fail){
    distance = sensor_true.distance();
    digitalWrite(backup, LOW);
  }
  else{
    digitalWrite(backup, HIGH);
    distance=sensor_backup.distance();
  }

  if (distance>=35) {
    digitalWrite(on, LOW);
    digitalWrite(off, HIGH);
  }
  else (distance<35) {
    digitalWrite(on, HIGH);
    digitalWrite(off, LOW);
  }
  
  delay(300);
}
