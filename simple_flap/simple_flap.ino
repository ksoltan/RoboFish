// ARDUINO PINS FOR MICs
//int caudal_1 = 16; // A2 For bang-bang/4th propulsor
//int caudal_2 = 17; // A3
int front_r = 3;
int front_l = 5;
int middle_l = 6;
int middle_r = 9;
int tail_l = 10;
int tail_r = 11;
int LED = 13;
uint32_t last_changed = 0;
int dir = 0;

void setup()
{
  // ARM MOTORS
//  pinMode(caudal_1, OUTPUT);
//  pinMode(caudal_2, OUTPUT);
  pinMode(LED, OUTPUT);
}


// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop()
{
  if (millis() - last_changed > 4000){
    caudal_fin_function();
    last_changed = millis();
  }
}

// PROPULSION FUNCTIONS
void caudal_fin_function()
{
  if (dir==0){
    analogWrite(front_r, 255);
    analogWrite(front_l, 0);
    analogWrite(middle_r, 255);
    analogWrite(middle_l, 0);
    analogWrite(tail_r, 255);
    analogWrite(tail_l, 0);
//      digitalWrite(caudal_1, HIGH);
//      digitalWrite(caudal_2, LOW);
    digitalWrite(LED, HIGH);
  }
  else{
    analogWrite(front_r, 0);
    analogWrite(front_l, 255);
    analogWrite(middle_r, 0);
    analogWrite(middle_l, 255);
    analogWrite(tail_r, 0);
    analogWrite(tail_l, 255);
//      digitalWrite(caudal_1, LOW);
//      digitalWrite(caudal_2, HIGH);
    digitalWrite(LED, LOW);
  }
  dir = (dir+1)%2;
}
