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
int joint3_l = 9;
int joint3_r = 10;
int joint3_l = 11;
int tail_r = A2; // Tail will for now be controlled bang-bang. Can implement pwm on it if necessary.
int tail_l = A3;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(tail_r, OUTPUT);
  pinMode(tail_l, OUTPUT);
}


// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
   static uint32_t last_changed = 0;

    if (millis() < last_changed + 4000)
    {
      caudal_fin_function(1000);
    }
    
//    else if (millis() < last_changed + 8000)
//    {
//      caudal_fin_function(500);     
//    }
//    else if (millis() < last_changed + 12000)
//    {
//      caudal_fin_function(250);     
//    }
    else
    {
      last_changed = millis();
    }
}

// PROPULSION FUNCTIONS
void caudal_fin_function(int f)
{
  static int dir = 0;
  static uint32_t last_changed = 0;
  static int duty = 100;
  static int pwm = (int)(255 * duty / 100);
  
  if (millis() > last_changed + f)
  {
    if (dir)
    {
      analogWrite(head_r, pwm);
      analogWrite(head_l, 0);
      analogWrite(joint2_r, pwm);
      analogWrite(joint2_l, 0);
      analogWrite(joint3_r, pwm);
      analogWrite(joint3_l, 0);
      digitalWrite(tail_r, HIGH);
      digitalWrite(tail_l, LOW); 
      digitalWrite(LED, HIGH);
    }
    else
    {
      analogWrite(head_r, 0);
      analogWrite(head_l, pwm);
      analogWrite(joint2_r, 0);
      analogWrite(joint2_l, pwm);
      analogWrite(joint3_r, 0);
      analogWrite(joint3_l, pwm);
      digitalWrite(tail_r, LOW);
      digitalWrite(tail_l, HIGH);
      digitalWrite(LED, LOW);
    }

    dir = 1 - dir;

    last_changed = millis();
  }
}
