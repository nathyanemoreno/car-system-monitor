#include "car-mechanics.h"

// Structure used for store crash report
struct CarCrashReport {
  bool didBrakeWork;
  float currentVelocity;
  float crashVelocity;
  float highestVelocity;
  float targetDistance;
  bool isHonking;
  float timestamp;
};

// Time expected to brake system activate
const int BRAKE_ACTIVATION_TIME_MS = 500;

// Minumum velocity necessary to update car highest velocity.
// Basically, if the car velocity is less than the threshold, the system will consider the car stopped.
const float MIN_CAR_VELOCITY_THRESHOLD = 5;

// Minimum distance necessary for the car is consider crashed.
const float MIN_TARGET_DISTANCE_THRESHOLD = 10;

// Stores car's highest velocity since last stopped.
float highestVelocity;

// Stores last car's state.
CarStateReading lastCarState;

// -- Public functions declarations --
bool didCarCrashed();
CarCrashReport getCrashReport();

// -- Functions implementations --
void updateHighestVelocity(float currentVelocity) {
  if (currentVelocity < MIN_CAR_VELOCITY_THRESHOLD) {
    // Reset highest velocity (car stopped)
    highestVelocity = 0;
    return;
  }
  highestVelocity = currentVelocity;
}

bool checkCrashCondition(float targetDistance) {
  // Crash condition
  return targetDistance < MIN_TARGET_DISTANCE_THRESHOLD;
}

bool didCarCrashed() {
  CarStateReading carState = readCarState();
  lastCarState = carState;

  updateHighestVelocity(carState.velocity);

  return checkCrashCondition(carState.targetDistance);
}

CarCrashReport getCrashReport() {
  float crashVelocity = lastCarState.velocity;
  float timestamp = millis();
  bool isCarHonking = lastCarState.isHonking;

  // Try activate brakes
  activateBrake();

  // Wait for the brakes to activate
  delay(BRAKE_ACTIVATION_TIME_MS);

  // Read new car state
  CarStateReading carState = readCarState();

  CarCrashReport crashReport = {
    carState.isBraking,
    carState.velocity,
    crashVelocity,
    highestVelocity,
    carState.targetDistance,
    carState.isHonking,
    timestamp
  };

  return crashReport;
}
