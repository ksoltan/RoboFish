uint8_t LEFT = 0;
uint8_t RIGHT = 1;
// The number of times PWM should be updated per period of the sin wave
uint8_t samples_per_period = 64;
const float Pi = 3.14159;

class Joint {

  public:

    // amplitude as a fraction of maximum voltage (0 to 1)
    float amplitude;
    // frequency in Hz (cycles/second)
    float freq;
    // phase_shift in seconds
    float phase_shift;
    // period in seconds
    float period;

    Joint(int pinL, int pinR, float a, float f, float phi) {
      _pinL = pinL;
      _pinR = pinR;
      update_params(a, f, phi);
    };

    void update_joint(){
      if (millis() - _timer >= _sampling_period * 1000) {
        _timer = millis();
        set_pwm();
        _current_sample = (_current_sample + 1) % samples_per_period;
        Serial.println(_curr_duty);
      };
    };

    void update_params(float a, float f, float phi) {
      amplitude = a;
      freq = f;
      phase_shift = phi;
      period = 1 / freq;
      _sampling_period = period / samples_per_period;
    }

  // everything after this point will become private when we finalize the code:
    int _pinL;
    int _pinR;
    // time between samples in s
    float _sampling_period;
    int _current_sample = 0;
    unsigned long _timer = 0;
    int _curr_duty = 0;

    void set_pwm () {
      // calculate current duty by figuring out how many seconds we are into the current cycle
      _curr_duty = (int)(255 * amplitude * sin(2*Pi / period * (_current_sample * _sampling_period + phase_shift)));

      // then figure out if we're going left or right and set the appropriate pin
      if (_curr_duty < 0) {
        analogWrite(_pinL, -1 * _curr_duty);
        analogWrite(_pinR, 0);
      }
      else {
        analogWrite(_pinL, 0);
        analogWrite(_pinR, _curr_duty);
      };
    };
};
