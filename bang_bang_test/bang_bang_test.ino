// ARDUINO PINS FOR MICs
int caudal_1 = 16; // A2
int caudal_2 = 17; // A3


void setup()
{
  // ARM MOTORS
  pinMode(caudal_1, OUTPUT);
  pinMode(caudal_2, OUTPUT);
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
  
  if (millis() > last_changed + f)
  {
    if (dir)
    {
      digitalWrite(caudal_1, HIGH);
      digitalWrite(caudal_2, LOW);
      Serial.println("high");
    }
    else
    {
      digitalWrite(caudal_1, LOW);
      digitalWrite(caudal_2, HIGH);
      Serial.println("low");
    }

    dir = 1 - dir;

    last_changed = millis();
  }
}
