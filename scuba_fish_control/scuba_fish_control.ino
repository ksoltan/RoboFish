// Written by Nina Petelina for her BS thesis Hydrodynamics
// of Magnet-Coil Actuated Robotic Fish to control the fish's
// amplitude and frequency of flap to get a Strouhal number
// close to real-life fish. Instead of a bang-bang control,
// the ramp pwm smoothly changes the amplitude of the fin
// to eliminate start-stop vortices.

// Question: Why does pwm value exceed 255 in analogWrite?
// Can do so using lower-level hardware control:
// https://arduino.stackexchange.com/questions/31436/arduinouno-mega-is-there-a-way-to-exceed-256-in-analogwrite
// But AnalogWrite function is not designed for >255.

// Code for variable control of tail motion

//#define E2 12 // Enable Pin for motor 2
#define I3 3 // Control pin 1 for motor 2
#define I4 5 // Control pin 2 for motor 2

void setup(){
//  pinMode(E2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);
}

void loop(){
  digitalWrite(I4, HIGH);
  int coil_pwm_4 = 0; int coil_pwm_3 = 0;
  int change_pwm = 50;

  // left side
  int left_k = 0;
  for(int left_k; left_k <= 5; left_k = left_k + 1){
    coil_pwm_3 = change_pwm * left_k;
    analogWrite(I3, coil_pwm_3);
    analogWrite(I4, 0);
    delay(65); // controls the frequency of the tail beat
  }
  // right motion
  int right_k = 0;
  for(int right_k; right_k <= 8; right_k = right_k + 1){
    coil_pwm_4 = change_pwm * right_k;
    analogWrite(I4, coil_pwm_4);
    analogWrite(I3, 0);
    delay(65);
  }
}

