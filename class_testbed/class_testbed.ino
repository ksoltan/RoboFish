uint8_t LEFT = 0;
uint8_t RIGHT = 1;
// The number of times PWM should be updated per period of the sin wave
uint8_t samples_per_period = 64;
const float Pi = 3.14159;

float amplitude = .5;
// frequency in Hz (cycles/second)
float freq = .1;
// phase_shift in seconds
float phase_shift = 0;
// period in seconds
float period = 1/freq;
// time between samples in s
float _sampling_period = period / samples_per_period;

int _pinL = 3;
int _pinR = 5;

int _current_sample = 0;
int _timer = 0;
int _curr_duty = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (millis() - _timer >= _sampling_period*1000) {
    _timer = millis();
    set_pwm();
    _current_sample = (_current_sample + 1) % samples_per_period;
  };
}

void set_pwm () {
  // calculate current duty by figuring out how many seconds we are into the current cycle
  _curr_duty = (int)(255*amplitude*sin(2*Pi/period * (_current_sample * _sampling_period + phase_shift)));
//      Serial.print("Updating _curr_duty to ");
  Serial.println(_curr_duty);
//  Serial.print("fn returns ");
//  Serial.println((int)(255*sin(2*Pi/period * (_current_sample * _sampling_period + phase_shift))));
//  Serial.print("amplitude is ");
//  Serial.println(amplitude);
  // then figure out if we're going left or right and set the appropriate pin
  if (_curr_duty < 0) {
    analogWrite(_pinL, -1*_curr_duty);
  }
  else {
    analogWrite(_pinR, _curr_duty);
  };
};
