// pins to power the joint coils
int front = 1;
int middle = 2;
int back = 3;

// pin for visual feedback via LED
int LED = 10;

// the sin lookup table has duty cycle values corresponding to a single cycle of sin
// current_index represents the current x position along the sin wave
int sin_lookup[16] 
int current_index = 0;

// frequency and period of sin wave
float freq = 8; // hz
float sin_period = 1/freq; 
// how long between changing the current pwm value; should be period of sin wave divided by length of lookup table
float lookup_period = sin_period/16;

// timer variable
float time_of_last_switch = 0;

void setup() {
  time_of_last_switch = millis();
  pinMode(LED, OUTPUT);
}

void loop() {
  if (millis() - time_of_last_switch >= lookup_period){
    // if it's been longer than one lookup_period since we last switched pwm values, update the timer and index variables and set the current pwm duty cycle
    time_of_last_switch = millis();
    current_index = (current_index + 1)%16;
    set_duty_cycle();
  }
}

void set_duty_cycle() {
  // set the duty cycle of each analog output by looking up its value
  // currently pretty dumb, needs to be generalized
  analogWrite(front, sin_lookup[current_index]);
  analogWrite(middle, sin_lookup[current_index]);
  analogWrite(back, sin_lookup[current_index]);
}

