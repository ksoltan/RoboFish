#include <Arduino.h>
#include "Skeleton.h"

// PWM pins are paired based on the Timer they respond to: https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM

#define LEFT_PIN_1 6
#define RIGHT_PIN_1 5
#define LEFT_PIN_2 10
#define RIGHT_PIN_2 9
#define LEFT_PIN_3 3
#define RIGHT_PIN_3 11

  Skeleton::Skeleton() : Joint1(LEFT_PIN_1, RIGHT_PIN_1), Joint2(LEFT_PIN_2, RIGHT_PIN_2),
    Joint3(LEFT_PIN_3, RIGHT_PIN_3){
  }

  void Skeleton::Joint1Set(int duty, int deadZone, float frequency, float phase){
    Joint1.setDuty(duty);
    Joint1.setDeadZone(deadZone);
    Joint1.setFrequency(frequency);
    Joint1.setPhase(phase);
  }

  void Skeleton::Joint2Set(int duty, int deadZone, float frequency, float phase){
    Joint2.setDuty(duty);
    Joint2.setDeadZone(deadZone);
    Joint2.setFrequency(frequency);
    Joint2.setPhase(phase);
  }

  void Skeleton::Joint3Set(int duty, int deadZone, float frequency, float phase){
    Joint3.setDuty(duty);
    Joint3.setDeadZone(deadZone);
    Joint3.setFrequency(frequency);
    Joint3.setPhase(phase);
  }

  void Skeleton::Update(){
    int res1 = Joint1.Update();
    int res2 = Joint2.Update();
    int res3 = Joint3.Update();
    Serial.print(res1);
    Serial.print(" ");
    Serial.print(res2);
    Serial.print(" ");
    Serial.println(res3);
  }
