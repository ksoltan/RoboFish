// ARDUINO PINS FOR MICs
// PWM Pins: 3, 5, 6, 9, 10, and 11
// LED pin: 13
int LED = 13;
int caudal_1 = 10;
int caudal_2 = 11;


void setup()
{
  pinMode(LED, OUTPUT);
}


// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
   static uint32_t last_changed = 0;

    if (millis() < last_changed + 4000)
    {
      caudal_fin_function(1000);
    }
    else if (millis() < last_changed + 8000)
    {
      caudal_fin_function(500);     
    }
    else if (millis() < last_changed + 12000)
    {
      caudal_fin_function(250);     
    }
    else if (millis() < last_changed + 16000)
    {
      caudal_fin_function(125);
    }
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
  static int duty = 50;
  static int pwm = (int)(255 * duty / 100)
  
  if (millis() > last_changed + f)
  {
    if (dir)
    {
      analogWrite(caudal_1, pwm);
      analogWrite(caudal_2, 0);
      digitalWrite(LED, HIGH);
    }
    else
    {
      analogWrite(caudal_1, 0);
      analogWrite(caudal_2, pwm);
      digitalWrite(LED, LOW);
    }

    dir = 1 - dir;

    last_changed = millis();
  }
}
