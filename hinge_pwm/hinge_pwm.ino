// ARDUINO PINS FOR MICs
// PWM Pins: 3, 5, 6, 9, 10, and 11
// LED pin: 13
// Each coil has two leads. By switching which lead is PWR and which is GND,
// the magnetic field of the coil switches and prompts the magnet to turn to
// align itself. The pin that must be turned on to turn a joint to the right
// is named joint_r. The pin that turns it to the left is joint_l.
int LED = 13;
int head_r = 3;
int head_l = 5;
int joint2_r = 6;
int joint2_l = 9;
int joint3_r = 10;
int joint3_l = 11;
int tail_r = 16; // A2 // Tail will for now be controlled bang-bang. Can implement pwm on it if necessary.
int tail_l = 17; // A3
int RIGHT = 1;
int LEFT = 0;
int dir_head = RIGHT; // The direction of the head will dictate direction of all other joints.

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(tail_r, OUTPUT);
  pinMode(tail_l, OUTPUT);
}

// Because a slight movement will theoretically change the course, take in both direction want joint to go in and the amplitude.
// In this way, if it is already going right but you want a less sharp angle, you can pass right and a smaller duty cycle.
// Abstracted to any joint because they all take the same commands except for the tail.
void moveJoint(int dir, int duty, int right, int left) {
  static int pwm = (int)(255 * duty / 100); // get analogWrite value to execute duty cycle
  if (dir == RIGHT) {
    analogWrite(right, pwm);
    analogWrite(left, 0);
    digitalWrite(LED, HIGH);
  } else {
    analogWrite(right, 0);
    analogWrite(left, pwm);
    digitalWrite(LED, LOW);
  }
}

void moveTail(int dir) {
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

static uint32_t last_head_change = 0;

// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
  if (millis() < last_head_change + 1000) // change head every 1s
  {
    dir_head = (dir_head == RIGHT) ? LEFT : RIGHT; // change the direction of the head
    moveJoint(dir_head, 100, head_r, head_l); // move the head
    last_head_change = millis(); // Update time last changed head
  }
  checkToMoveJoints();
}

// Not efficient move function unless want to vary duty cycle on a joint in the interval
// between when it should move and the next joint needs to move.
void checkToMoveJoints(){
  if(millis() > last_head_change + 750){ // within this interval, until head moves again, keep resending the same move function (doesn't change anything after the first time)
    moveTail(dir_head);
  } else if(millis() > last_head_change + 500){
    moveJoint(dir_head, 100, joint3_r, joint3_l);
  } else if(millis() > last_head_change + 250){
    moveJoint(dir_head, 100, joint2_r, joint2_l);
  }
}

