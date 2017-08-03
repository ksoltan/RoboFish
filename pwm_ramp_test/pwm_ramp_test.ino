uint8_t LEFT = 0;
uint8_t RIGHT = 1;

// ARDUINO PINS FOR MICs
uint8_t head_r = 3;
uint8_t head_l = 5;
uint8_t LED = 13;

uint8_t curr_dir = LEFT;
uint8_t max_duty = 80;
uint8_t min_duty = 10;
uint8_t change_amount = 10;
uint8_t curr_duty = min_duty;

void setup()
{
  // ARM MOTORS
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  flap();
  // Update duty cycle
  curr_duty = curr_duty + change_amount;
  if(change_amount >= max_duty){
    // Switch direction and reset duty cycle
    if(curr_dir == LEFT){
      curr_dir = RIGHT;
    }else{
      curr_dir = LEFT;
    }
    curr_duty = min_duty;
  }
}

void flap() {
  static int pwm = (int)(255 * curr_duty / 100); // get analogWrite value to execute duty cycle
  if (curr_dir == RIGHT) {
    analogWrite(head_r, pwm);
    analogWrite(head_l, 0);
    digitalWrite(LED, HIGH);
  } else {
    analogWrite(head_r, 0);
    analogWrite(head_l, pwm);
    digitalWrite(LED, LOW);
  }
}
