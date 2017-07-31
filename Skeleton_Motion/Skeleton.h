#include "Skeleton_Variables.h"
class Skeleton{
  private:
    // Joint State is reflected by the direction and the pwm strength (amplitude -> angle of deflection relative 
    // to previous joint) of the joint.
    uint8_t curr_joint_state[NUM_JOINTS][2] = {{RIGHT, 100}, {RIGHT, 100}, {RIGHT, 100}}; // Could write function to automatically populate array
    uint8_t joint_order_idx = 0;
    uint8_t joint_order[NUM_JOINTS] = {1, 2, 0} // Based on phases, ordering from greatest to least (all should be positive)
  public:
  // Constructor
  Skeleton();
  
  void UpdateJoints(){
    
  }

  // Don't need actual positions, just need deflection angles
  // can't return arrays, only pointers. If I want to get messy with that,
  // sure, otherwise, find a way to just change global variable
  GetJointDeflectionApprox(float t){
    return null;
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

  // If not a PWM pin, use bang bang approach.
  // Hard coded to the Tail fin joint
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
  
  float get_posture(float x, float t){
    float c1 = 0.4; // Amplitude of oscillation. The higher c1 is, the more wide the sweep is of the function
    float c2 = 0; // When not 0, introduces quadratic term. Motion is more steep and tightly curved
    float k = 0.15; // Frequency of oscillation. The higher k is, the more zig-zaggy the motion is
    uint8_t omega = 20; // Speed of oscillation. The higher omega is, the faster the body moves
    return (c1 * x + c2 * x*x) * sin(k * x + omega * t) - c1 * x * sin(omega * t);
  }
};

