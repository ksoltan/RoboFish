// Define all global variables for the skeleton, including pin numbers and initializing output/input on the pins
#define NUM_JOINTS 3 // aka Propulsors
uint8_t joint_to_move = 0; // 0-head, 1-joint2, 2-joint3/tail
uint8_t joint_directions = B000; // all heads start pointing in left direction (tail, joint3, joint2, head)
#define LEFT 0
#define RIGHT 1

// ARDUINO PINS FOR MICs
#define head_r 3
#define head_l 5
#define joint2_r 6
#define joint2_l 9
#define joint3_r 10
#define joint3_l 11
// There are only 3 PWM pins on the Pro Mini. The tail will be actuated as bang-bang for now.
#define tail_r 16 // A2
#define tail_l 17 // A3
#define LED 13

//uint8_t joint_pins[NUM_JOINTS][2] = {{joint3_l, joint3_r}, {tail_l, tail_r}};
//uint8_t joint_pins[NUM_JOINTS][2] = {{head_l, head_r}, {joint2_l, joint2_r}, {joint3_l, joint3_r}, {tail_l, tail_r}};
uint8_t joint_pins[NUM_JOINTS][2] = {{head_l, head_r}, {joint2_l, joint2_r}, {joint3_l, joint3_r}};

void setup()
{
  pinMode(tail_l, OUTPUT);
  pinMode(tail_r, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}
