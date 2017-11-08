uint8_t LEFT = 0;
uint8_t RIGHT = 1;

// ARDUINO PINS FOR MICs
uint8_t head_r = 3;
uint8_t head_l = 5;
uint8_t LED = 13;

uint8_t curr_dir = LEFT;
float frequency = 1; //Hz
float period = 1 / frequency;
uint8_t steps_in_ramp = 5;
uint8_t max_duty = 20;
uint8_t min_duty = 10;
uint8_t change_amount = (int)((max_duty - min_duty) / 7);
//uint8_t change_amount = 10;

uint8_t curr_duty = min_duty;

float time_change = period / 2 / steps_in_ramp * 1000; // ms
//int time_change = 60; // ms, time between each ramp up of duty. time_change * (max_duty - min_duty)/(change_amount) = T/2

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  flap();
  // Update duty cycle
  curr_duty = curr_duty + change_amount;
  if(curr_duty >= max_duty){
    // Switch direction and reset duty cycle
    if(curr_dir == LEFT){
      curr_dir = RIGHT;
    }else{
      curr_dir = LEFT;
    }
    Serial.println(curr_dir);
    curr_duty = min_duty; // may need to actually ramp downwards, not sure.
  }
  delay(time_change);
}

void flap() {
//  Serial.println(curr_duty);
  int pwm = (int)(255 * curr_duty / 100); // get analogWrite value to execute duty cycle
  Serial.println(pwm);
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

