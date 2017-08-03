// In MATLAB, ran get_deflection_pattern([24.55, 26.1, 25, 25], @get_posture_short_fish)
// to get:  num_joint, time_from_prev_joint(s), amplitude(deg)
//            3.0000, 0.0726, 29.6189
//            1.0000, 0.0247, 16.1928
//            2.0000, 0.0695, 29.4735
// Joint order in Arduino: (2, 0, 1) since MATLAB indexes from 1
// From short_fish_joint_motion_approx_vs_original.png, see that pattern is
// (peak, trough, peak), so set joint_directions to 010, instead of 000.

const int NUM_JOINTS = 3;
uint8_t joint_order[NUM_JOINTS] = {2, 0, 1}; // 2, 0, 1, 2, 0, 1, ...
uint8_t joint_idx = 1; // idx in joint_order
uint8_t joint_to_move = 0; // joint_order[joint_idx]
uint8_t joint_directions = B011; // Pretend that joint2 already moved, before joint2 = B010
float time_since_prev_joint[NUM_JOINTS] = {24.7, 6.95, 72.6}; //ms, order joints 0, 1, 2
uint8_t joint_duty[NUM_JOINTS] = {50, 100, 100}; // From amplitude, head looks about half of other joints
uint8_t LEFT = 0;
uint8_t RIGHT = 1;

// ARDUINO PINS FOR MICs
uint8_t head_r = 3;
uint8_t head_l = 5;
uint8_t joint2_r = 6;
uint8_t joint2_l = 9;
uint8_t joint3_r = 10;
uint8_t joint3_l = 11;
uint8_t joint_pins[NUM_JOINTS][2] = {{head_l, head_r}, {joint2_l, joint2_r}, {joint3_l, joint3_r}};
uint8_t LED = 13;

void setup()
{
  // ARM MOTORS
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}


// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
  static uint32_t last_changed = 0;
  if (millis() - last_changed > time_since_prev_joint[joint_to_move]) {
    moveNextJoint();
    last_changed = millis();
    joint_idx = (joint_idx + 1) % NUM_JOINTS; // make it loop back from 2 to 0.
    joint_to_move = joint_order[joint_idx];
  }
}

void flap(int dir, int duty) {
  static int pwm = (int)(255 * duty / 100); // get analogWrite value to execute duty cycle
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

void moveNextJoint() {
  // Assuming that all joint movement right now is just bang bang
  // in the opposite direction of where they were
  // Get current joint direction
  int curr_dir = (joint_directions >> joint_to_move) & 1;
  
  // flap fin in opposite direction of its current orientation
  flap(1 - curr_dir, joint_duty[joint_to_move]);
  
  // update the joint's direction. Current joint to move is updated in loop.
  // Add 0.5 to avoid rounding problem
  joint_directions = joint_directions ^ (uint8_t)(pow(2, joint_to_move) + 0.5);
}
