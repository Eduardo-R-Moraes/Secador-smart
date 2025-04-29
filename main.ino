#include <NewPing.h>

#define TRIG_TRUE 3
#define ECHO_TRUE 2
#define TRIG_BACKUP 12
#define ECHO_BACKUP 8
#define MAX_DISTANCE 400

NewPing sensor_true(TRIG_TRUE, ECHO_TRUE, MAX_DISTANCE);
NewPing sensor_backup(TRIG_BACKUP, ECHO_BACKUP, MAX_DISTANCE);

#define LED_ON 5
#define LED_OFF 4
#define LED_BACKUP 7
#define BUTTON_FAIL 6

void setup() {
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_OFF, OUTPUT);
  pinMode(LED_BACKUP, OUTPUT);
  pinMode(BUTTON_FAIL, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  bool fail = digitalRead(BUTTON_FAIL) == LOW;  // Pressionado = falha

  Serial.print("Falha: ");
  Serial.println(fail);

  digitalWrite(LED_ON, HIGH);  // Sempre começa com ligado

  int distance;
  if (fail) {
    distance = sensor_true.ping_cm();
    digitalWrite(LED_BACKUP, LOW);
  } else {
    distance = sensor_backup.ping_cm();
    digitalWrite(LED_BACKUP, HIGH);
  }

  Serial.print("Distância: ");
  Serial.println(distance);

  if (distance > 0 && distance < MAX_DISTANCE) {
    if (distance >= 35) {
      digitalWrite(LED_ON, LOW);
      digitalWrite(LED_OFF, HIGH);
    } else {
      digitalWrite(LED_ON, HIGH);
      digitalWrite(LED_OFF, LOW);
    }
  }

  delay(300);
}