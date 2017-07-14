// ARDUINO PINS FOR MICs
int caudal_1 = 16; // A2
int caudal_2 = 17; // A3
int tail_r = 3;
int tail_l = 5;
int LED = 13;

void setup()
{
  // ARM MOTORS
  pinMode(caudal_1, OUTPUT);
  pinMode(caudal_2, OUTPUT);
  pinMode(LED, OUTPUT);
}


// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
  static uint32_t last_changed = 0;

  if (millis() < last_changed + 4000){
    caudal_fin_function(1000);
  }
  else{
    last_changed = millis();
  }
}

// PROPULSION FUNCTIONS
void caudal_fin_function(int f)
{
  static int dir = 0;
  static uint32_t last_changed = 0;

  if (millis() > last_changed + f){
    if (dir){
      analogWrite(tail_r, 255);
      analogWrite(tail_l, 0);
      digitalWrite(caudal_1, HIGH);
      digitalWrite(caudal_2, LOW);
      digitalWrite(LED, HIGH);
    }
    else{
      analogWrite(tail_r, 0);
      analogWrite(tail_l, 255);
      digitalWrite(caudal_1, LOW);
      digitalWrite(caudal_2, HIGH);
      digitalWrite(LED, LOW);
    }

    dir = 1 - dir;
    last_changed = millis();
  }
}
