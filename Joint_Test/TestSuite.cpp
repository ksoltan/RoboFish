#include <Arduino.h>
#include "TestSuite.h"

#define LEFT_PIN 6
#define RIGHT_PIN 5
TestSuite::TestSuite() : Joint1(LEFT_PIN, RIGHT_PIN) {
  BasicSet(40, 50, 1);
}

void TestSuite::BasicSet(int duty, int deadZone, float frequency, int flapsPerSetting = 10) {
  activeTest = BASIC;
  MaxDuty = duty;
  MaxDeadZone = deadZone;
  TimePerSetting = flapsPerSetting * 1 / frequency * 1000;
  lastUpdate = millis();
  currNumFlaps = 0;
  Joint1.SimpleFlapSet(duty, deadZone, frequency);
  Serial.println("Set Basic Sequence.");
}

void TestSuite::DutySweepSet(int minDuty, int maxDuty, int dutyInterval, int deadZone, float frequency, int flapsPerSetting = 10) {
  activeTest = DUTY_SWEEP;
  MinDuty = minDuty;
  MaxDuty = maxDuty;
  DutyInterval = dutyInterval;
  MaxDeadZone = deadZone;
  TimePerSetting = flapsPerSetting * 1 / frequency * 1000;
  lastUpdate = millis();
  currNumFlaps = 0;
  Joint1.SimpleFlapSet(minDuty, deadZone, frequency);
  Serial.println("Set Duty Sweep.");
}

void TestSuite::DeadZoneSweepSet(int duty, int minDeadZone, int maxDeadZone, int deadZoneInterval, float frequency, int flapsPerSetting = 10) {
  activeTest = DEAD_ZONE_SWEEP;
  MaxDuty = duty;
  MinDeadZone = minDeadZone;
  MaxDeadZone = maxDeadZone;
  DeadZoneInterval = deadZoneInterval;
  TimePerSetting = flapsPerSetting * 1 / frequency * 1000;
  lastUpdate = millis();
  currNumFlaps = 0;
  Joint1.SimpleFlapSet(duty, minDeadZone, frequency);
  Serial.println("Set Dead Zone Sweep.");
}

void TestSuite::FrequencySweepSet(int duty, int deadZone, float minFrequency, float maxFrequency, float frequencyInterval, int flapsPerSetting = 10){
  activeTest = FREQUENCY_SWEEP;
  MaxDuty = duty;
  MaxDeadZone = deadZone;
  MinFrequency = minFrequency;
  MaxFrequency = maxFrequency;
  FrequencyInterval = frequencyInterval;
//  TimePerSetting = flapsPerSetting * 1 / minFrequency * 1000;
  TimePerSetting = 8000; // 8s per frequency
  lastUpdate = millis();
  currNumFlaps = 0;
  Joint1.SimpleFlapSet(duty, deadZone, minFrequency);
  Serial.println("Set Frequency Sweep.");
}

void TestSuite::Update() {
  switch (activeTest) {
    case BASIC:
//      BasicUpdate();
      break;
    case DUTY_SWEEP:
      DutySweepUpdate();
      break;
    case DEAD_ZONE_SWEEP:
      DeadZoneSweepUpdate();
      break;
    case FREQUENCY_SWEEP:
      FrequencySweepUpdate();
      break;
    default:
      break;
  }
  Joint1.Update();
}

void TestSuite::BasicUpdate() {
  if (millis() - lastUpdate > TimePerSetting) {
    currNumFlaps++;
    switch (currNumFlaps % 3) {
      case 0:
        Joint1.SimpleFlapSet(MaxDuty, MaxDeadZone, MaxFrequency);
        break;
      case 1:
        Joint1.LeftOnlySet(MaxDuty, MaxDeadZone);
        break;
      case 2:
        Joint1.RightOnlySet(MaxDuty, MaxDeadZone);
        break;
      default:
        break;
    }
    lastUpdate = millis();
  }
}

void TestSuite::DutySweepUpdate() {
  if (millis() - lastUpdate > TimePerSetting) {
    // Update duty.
    int currDuty = Joint1.getCurrDuty();
    if (currDuty >= MaxDuty) {
      Joint1.setDuty(MinDuty);
    } else {
      Joint1.setDuty(currDuty + DutyInterval);
    }
    lastUpdate = millis();
    Serial.print("Duty = ");
    Serial.print(Joint1.getCurrDuty());
    Serial.print(".\n");
  }
}

void TestSuite::DeadZoneSweepUpdate() {
  if (millis() - lastUpdate > TimePerSetting) {
    // Update deadZone
    int currDeadZone = Joint1.getCurrDeadZone();
    if (currDeadZone >= MaxDeadZone) {
      Joint1.setDeadZone(MinDeadZone);
    } else {
      Joint1.setDeadZone(currDeadZone + DeadZoneInterval);
    }
    lastUpdate = millis();
    Serial.print("Deadzone = ");
    Serial.print(Joint1.getCurrDeadZone());
    Serial.print(".\n");
  }
}

void TestSuite::FrequencySweepUpdate() {
  if (millis() - lastUpdate > TimePerSetting) {
    // Update deadZone
    float currFrequency = Joint1.getCurrFrequency();
    if (currFrequency >= MaxFrequency) {
      Joint1.setPeriod(MinFrequency);
    } else {
      Joint1.setPeriod(currFrequency + FrequencyInterval);
    }
    lastUpdate = millis();
    Serial.print("Frequency = ");
    Serial.print(Joint1.getCurrFrequency());
    Serial.print(".\n");
  }
}
