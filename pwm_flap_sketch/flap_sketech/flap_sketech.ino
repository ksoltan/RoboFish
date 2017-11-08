// pins for each direction of each coil
int front_l = 3;
int front_r = 5;
int middle_l = 5;
int middle_r = 9;
int back_l = 10;
int back_r = 11;

// the sin lookup table has duty cycle values corresponding to a single cycle of sin
// current_index represents the current x position along the sin wave
int sin_lookup_len = 16;
int sin_lookup[16] = {0, 49, 97, 141, 180, 212, 235, 250, 255, 250, 235, 212, 180, 141, 97, 49};
int current_index = 0;

// direction the tail is moving
int current_direction = 0;

// frequency and period of sin wave
float freq = .1; // hz
float sin_period = 1/freq*1000; 
// how long between changing the current pwm value; should be period of sin wave divided by length of lookup table
float lookup_period = sin_period/sin_lookup_len;

// timer variable
float time_of_last_duty_cycle_change = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (millis() - time_of_last_duty_cycle_change >= lookup_period){
    // if it's been longer than one lookup_period since we last changed pwm values, update the timer and index variables and set the current pwm duty cycle
    time_of_last_duty_cycle_change = millis();
    current_index = (current_index + 1) % sin_lookup_len;
    if (current_index == 0)
    {
      // in the case that we've looped around and completed one half cycle of sin
      current_direction = (current_direction + 1) % 2;
    }
    
    set_duty_cycle();
  }
}

void set_duty_cycle() {
  Serial.print(current_direction);
  Serial.print(" ");
  Serial.println(sin_lookup[current_index]);
  if (current_direction == 0)
  {
    analogWrite(front_l, sin_lookup[current_index]);
    analogWrite(front_r, 0);
    
    analogWrite(middle_l, sin_lookup[current_index]);
    analogWrite(middle_r, 0);
    
    analogWrite(back_l, sin_lookup[current_index]);
    analogWrite(back_r, 0);
  }
  else
  {
    analogWrite(front_l, 0);
    analogWrite(front_r, sin_lookup[current_index]);
    
    analogWrite(middle_l, 0);
    analogWrite(middle_r, sin_lookup[current_index]);
    
    analogWrite(back_l, 0);
    analogWrite(back_r, sin_lookup[current_index]);
  }
}
