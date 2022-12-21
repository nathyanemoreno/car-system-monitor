#include <Servo.h>
#include <Ultrasonic.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "crash-detector.h"

char *params[6] = { "is_honking=", "current_velocity=", "crash_velocity=", "highest_velocity=", "target_distance=", "timestamp=" };
int i;
CarCrashReport crashReport;
bool finishSentReport = true;

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  pinMode(BUZZER_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BRAKE_PIN, INPUT_PULLUP);

  pinMode(SERVO_SG90_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ULTRASONIC_HCSR04_ECHO, INPUT);   //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(ULTRASONIC_HCSR04_TRIG, OUTPUT);  //DEFINE O PINO COMO SAIDA (ENVIA)

  Serial.begin(9600);
  servo.attach(SERVO_SG90_PIN, 500, 2500);  // States that the servo is attached to pin 5
  servo.write(10);                          //Sets the servo angle to 10degrees
  randomSeed(analogRead(A0));
}

void loop() {
  activateBrake();
  stopBrake();
  activateHorn();
  stopHorn();
}

void requestEvent() {
  bool didCrash = didCarCrashed();  // update real-time car crash state

  // if (didCrash) {
  Serial.println(i);
  if (finishSentReport) {
    crashReport = getCrashReport();
    finishSentReport = false;
  }

  String mReport;
  switch (i) {
    case 0:
      mReport = params[i] + (String)(crashReport.isHonking ? "0" : "1") + "&";
      break;
    case 1:
      mReport = params[i] + (String)(int)(crashReport.currentVelocity) + "&";
      break;
    case 2:
      mReport = params[i] + (String)(int)(crashReport.crashVelocity) + "&";
      break;
    case 3:
      mReport = params[i] + (String)(int)(crashReport.highestVelocity) + "&";
      break;
    case 4:
      mReport = params[i] + (String)(int)(crashReport.targetDistance) + "&";
      break;
    case 5:
      mReport = params[i] + (String)(int)(crashReport.timestamp) + "&#";
      i = -1;
      finishSentReport = true;
      break;
    default:
      break;
  }

  i++;

  Wire.write(mReport.c_str());
}
