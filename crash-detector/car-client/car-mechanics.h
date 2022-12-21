#include <math.h>
#include "Arduino.h"
#define SERVO_SG90_PIN 9
#define ULTRASONIC_HCSR04_TRIG 4
#define ULTRASONIC_HCSR04_ECHO 5
#define BUZZER_PIN 3
#define BUZZER_BUTTON_PIN 6
#define VELOCITY_SENSOR_PIN 7
#define BRAKE_PIN 8

Servo servo;    //Defines the object Servo of type(class) Servo
int angle = 0;  // Defines an integerm

Ultrasonic ultrasonic(ULTRASONIC_HCSR04_TRIG, ULTRASONIC_HCSR04_ECHO);
int distancia;  //VARIÁVEL DO TIPO INTEIRO
String result;  //VARIÁVEL DO TIPO STRING

// Structure used for store car's state
struct CarStateReading {
  float velocity;
  float targetDistance;
  bool isHonking;
  bool isBraking;
};

// Manipulates system failures events
const int MAX_FAILURE_CHANCE = 100;
const int BREAKER_FAILURE_CHANCE = 10;  // 20 in MAX_FAILURE_CHANCE (100)

// Real-time car's data
float currentVelocity;        // Stores car's velocity
float currentTargetDistance;  // Stores car's distance to a front target
bool isHonking = false;       // Stores state of car's honk
bool isBraking = false;       // Stores state of car's brake

// -- Capabilities and sensor reading functions --
float readVelocity() {
  // Serial.println(analogRead(VELOCITY_SENSOR_PIN));
  delay(100);
  return analogRead(VELOCITY_SENSOR_PIN);
}

float readTargetDistance() {
  float distance;
  // TODO: implement real read of the ultrasonic sensor
  digitalWrite(ULTRASONIC_HCSR04_TRIG, LOW);   //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2);                        //INTERVALO DE 2 MICROSSEGUNDOS
  digitalWrite(ULTRASONIC_HCSR04_TRIG, HIGH);  //SETA O PINO 6 COM PULSO ALTO "HIGH"
  delayMicroseconds(10);                       //INTERVALO DE 10 MICROSSEGUNDOS
  digitalWrite(ULTRASONIC_HCSR04_TRIG, LOW);   //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
  //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
  //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
  //NA VARIAVEL "distancia"
  distance = (ultrasonic.Ranging(CM));  //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
  result = String(distance);            //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
  delay(500);                           //INTERVALO DE 500 MILISSEGUNDOS
  return distance;
}

bool readBrakeState() {
  // Simulate a brake failure
  int chance = random(MAX_FAILURE_CHANCE);
  // Serial.println(chance < BREAKER_FAILURE_CHANCE);
  return chance < BREAKER_FAILURE_CHANCE;
}

// -- Functions declarations --
CarStateReading readCarState();
void readCarCapabilities();
void activateBrake();
void stopBrake();
void activateHorn();
void stopHorn();

// -- Functions implementations --
CarStateReading readCarState() {
  readCarCapabilities();

  CarStateReading carState = {
    currentVelocity,
    currentTargetDistance,
    isHonking,
    isBraking,
  };

  return carState;
}

void readCarCapabilities() {
  currentVelocity = readVelocity();
  currentTargetDistance = readTargetDistance();
}

void activateBrake() {
  int willBrakeWork = readBrakeState();
  // Serial.println(!isBraking && willBrakeWork ? "true" : "false");

  if (!isBraking && willBrakeWork) {
    if (digitalRead(BRAKE_PIN) == LOW) {
      for (angle = 10; angle < 190; angle++) {
        servo.write(angle);
        delay(1);
      }
      isBraking = true;
    }
  }
}

void stopBrake() {
  if (digitalRead(BRAKE_PIN) == HIGH && isBraking) {
    for (angle = 190; angle > 10; angle--) {
      servo.write(angle);
      // delay(pow(angle * 0.02, 2) );
      delay(3);
    }
    isBraking = false;
  }
}

void activateHorn() {
  if (digitalRead(BUZZER_BUTTON_PIN) == LOW && !isHonking) {
    tone(BUZZER_PIN, 400);
    isHonking = true;
  }
}

void stopHorn() {
  if (digitalRead(BUZZER_BUTTON_PIN) == HIGH && isHonking) {

    noTone(BUZZER_PIN);
    isHonking = false;
  }
}