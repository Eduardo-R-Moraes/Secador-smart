// FSM with Fault Tolerance for Arduino
#include <NewPing.h>

#define TRIG_MAIN    3
#define ECHO_MAIN    2
#define TRIG_RED     12
#define ECHO_RED     8
#define MAX_DIST     400

// LEDs and Button
#define LED_ON       5
#define LED_OFF      4
#define LED_REDUND   7
#define BUTTON_FAIL  6

// FSM States
enum State { IDLE, PARTIAL, TOTAL, FAULT };
const char* stateNames[] = {"IDLE", "PARTIAL", "TOTAL", "FAULT"};
State currentState = IDLE;

// Sensors
NewPing sensorMain(TRIG_MAIN, ECHO_MAIN, MAX_DIST);
NewPing sensorRed(TRIG_RED, ECHO_RED, MAX_DIST);

void setup() {
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_OFF, OUTPUT);
  pinMode(LED_REDUND, OUTPUT);
  pinMode(BUTTON_FAIL, INPUT_PULLUP);

  Serial.begin(9600);
  delay(100);
  // Cabeçalho atualizado
  Serial.println("State,Consumption,RedundantOn,Distance,IsOn");
}

void loop() {
  bool buttonFail = (digitalRead(BUTTON_FAIL) == LOW);
  int distance;
  bool usingRedundant = false;
  int consumption = 0;
  bool isOn = false;

  int mainDist = sensorMain.ping_cm();
  if (buttonFail || mainDist == 0) {
    distance = sensorRed.ping_cm();
    usingRedundant = true;
  } else {
    distance = mainDist;
  }

  switch (currentState) {
    case IDLE:
      if (!buttonFail && distance > 0 && distance < 100) currentState = PARTIAL;
      else if (buttonFail || distance <= 0) currentState = FAULT;
      break;
    case PARTIAL:
      if (buttonFail) currentState = FAULT;
      else if (distance > 0 && distance < 35) currentState = TOTAL;
      else if (distance >= 100 || distance == 0) currentState = IDLE;
      break;
    case TOTAL:
      if (buttonFail) currentState = FAULT;
      else if (distance >= 100 || distance == 0) currentState = IDLE;
      break;
    case FAULT:
      if (!buttonFail && !isnan(distance) && distance > 0) currentState = IDLE;
      break;
  }

  switch (currentState) {
    case IDLE:
      digitalWrite(LED_ON, LOW);
      digitalWrite(LED_OFF, HIGH);
      digitalWrite(LED_REDUND, LOW);
      consumption = 1;
      isOn = false;
      break;
    case PARTIAL:
      digitalWrite(LED_ON, millis() % 1000 < 500);
      digitalWrite(LED_OFF, millis() % 1000 >= 500);
      digitalWrite(LED_REDUND, LOW);
      consumption = 3;
      isOn = true;
      break;
    case TOTAL:
      digitalWrite(LED_ON, HIGH);
      digitalWrite(LED_OFF, LOW);
      digitalWrite(LED_REDUND, LOW);
      consumption = 5;
      isOn = true;
      break;
    case FAULT:
      digitalWrite(LED_ON, LOW);
      digitalWrite(LED_OFF, LOW);
      digitalWrite(LED_REDUND, HIGH);
      consumption = 4;
      usingRedundant = true;
      isOn = false;
      break;
  }

  // Impressão atualizada com distância e estado ligado/desligado
  Serial.print(stateNames[currentState]); Serial.print(",");
  Serial.print(consumption); Serial.print(",");
  Serial.print(usingRedundant); Serial.print(",");
  Serial.print(distance); Serial.print(",");
  Serial.println(isOn);

  delay(300);
}
