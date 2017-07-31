#include "Skeleton.h"

Skeleton Fish;
// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
  Fish.UpdateJoints();
  delay(1);
}

void flap(int dir, int duty) {
  static int pwm = (int)(255 * duty / 100); // get analogWrite value to execute duty cycle
  if (joint_to_move == NUM_JOINTS - 1) {
    flapFin(dir);
  } else {
    if (dir == RIGHT) {
      analogWrite(joint_pins[joint_to_move][RIGHT], pwm);
      analogWrite(joint_pins[joint_to_move][LEFT], 0);
      digitalWrite(LED, HIGH);
    } else {
      analogWrite(joint_pins[joint_to_move][RIGHT], 0);
      analogWrite(joint_pins[joint_to_move][LEFT], pwm);
      digitalWrite(LED, LOW);
    }
  }
}

void flapFin(int dir) {
  if (dir == RIGHT) {
    digitalWrite(tail_r, HIGH);
    digitalWrite(tail_l, LOW);
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(tail_r, LOW);
    digitalWrite(tail_l, HIGH);
    digitalWrite(LED, LOW);
  }
}

void moveNextJoint() {
  // Assuming that all joint movement right now is just bang bang
  // in the opposite direction of where they were
  // Get current joint direction
  int curr_dir = (joint_directions >> joint_to_move) & 1;  
  // flap fin in opposite direction, currently at full amplitude
  flap(1 - curr_dir, 100);
  // update the joint's direction. Current joint to move is updated in loop.
  joint_directions = joint_directions ^ (uint8_t)(pow(2, joint_to_move)+0.5);
  //printJointPos();
}

void printJointPos(){
  for(int i = 0; i < NUM_JOINTS; i++){
    int dir = (joint_directions >> i) & 1;
    if(dir){
      // Right
      Serial.print("\\");
    }else{
      Serial.print("/");
    }
  }
  Serial.print("\n");
}

