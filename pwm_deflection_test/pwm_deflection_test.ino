// ARDUINO PINS FOR MICs
int caudal_1 = 3; // A2
int caudal_2 = 5; // A3
int LED = 13;
int duty = 0;
int dir = 0;

void setup() {
  // ARM MOTORS
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}


// MAIN LOOP DEFINING THE ROBOTS BEHAVIOR
void loop() {
  if (duty < 100) {
    duty = duty + 10;
  } else {
    duty = 0;
  }
  Serial.println("Starting new duty cycle");
  run_flapping_sequence();
}

void run_flapping_sequence() {
  static uint32_t last_changed = 0;
  while (last_changed != -1) {
    if (millis() < last_changed + 4000) {
      caudal_fin_function(1000);
    }
    else if (millis() < last_changed + 8000) {
      caudal_fin_function(500);
    }
    else if (millis() < last_changed + 12000) {
      caudal_fin_function(250);
    }
    else if (millis() < last_changed + 16000) {
      caudal_fin_function(125);
    }
    else {
      last_changed = -1; // Whole loop cleared, stop
    }
  }
  delay(30);
}

// PROPULSION FUNCTIONS
void caudal_fin_function(int f) {
  int pwm = (int)(255 * curr_duty / 100);

  if (millis() > f) {
    if (dir) {
      analogWrite(head_r, pwm);
      analogWrite(head_l, 0);
      digitalWrite(LED, HIGH);
    }
    else {
      analogWrite(head_r, 0);
      analogWrite(head_l, pwm);
      digitalWrite(LED, LOW);
    }
    dir = 1 - dir;
    last_changed = millis();
  }
}
