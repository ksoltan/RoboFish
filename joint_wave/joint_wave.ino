const int NUM_JOINTS = 2;
uint8_t joint_to_move = 0; // 0-head, 1-joint2, 2-joint3, 3-tail
uint8_t joint_directions = B0000; // all heads start pointing in left direction (tail, joint3, joint2, head)
uint8_t LEFT = 0;
uint8_t RIGHT = 1;

// ARDUINO PINS FOR MICs
uint8_t tail_r = 3;
uint8_t tail_l = 5;
uint8_t fin_r = 16; // A2
uint8_t fin_l = 17; // A3
uint8_t joint_pins[NUM_JOINTS][2] = {{tail_l, tail_r}, {fin_l, fin_r}};
uint8_t LED = 13;

void setup()
{
  // ARM MOTORS
  pinMode(fin_l, OUTPUT);
  pinMode(fin_r, OUTPUT);
  pinMode(LED, OUTPUT);
}


// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
  static uint32_t last_changed = 0;
  if (millis() - last_changed > 500) {
    moveNextJoint();
    last_changed = millis();
    joint_to_move = (joint_to_move + 1) % NUM_JOINTS; // make it loop back from 3 to 0.
  }
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
    digitalWrite(fin_r, HIGH);
    digitalWrite(fin_l, LOW);
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(fin_r, LOW);
    digitalWrite(fin_l, HIGH);
    digitalWrite(LED, LOW);
  }
}

void moveNextJoint() {
  // Assuming that all joint movement right now is just bang bang
  // in the opposite direction of where they were
  // Get current joint direction
  int curr_dir = (joint_directions >> joint_to_move) && 1;
  // flap fin in opposite direction, currently at full amplitude
  flap(1 - curr_dir, 100);
  // update the joint's direction. Current joint to move is updated in loop.
  joint_directions = joint_directions ^ (uint8_t)pow(2, joint_to_move);
}

