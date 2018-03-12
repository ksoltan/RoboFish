/**
* Loop through duty cycles from 0 to 100%, letting the fin flap a couple of times at each setting.
* The goal of this code is to determine the response of the hinge to different PWM values.
* Future improvement: let fin flap at different frequencies for each setting.
* Current improvement: Pwm is on for a certain percentage of the time. (Oooh, create test modes)
*                       -> pretty easy, update duty, update flap like cuttlespeak
*/

// ARDUINO PINS FOR MICs
int head_r = 3; // A2
int head_l = 5; // A3
int LED = 13;

int curr_duty = 50;
int dir = 0;
int num_flaps_per_duty = 4;
int curr_flap = 1;
int time_to_switch_dir = 2000; // Allow for 2s between each fin direction change
int curr_time_percentage = 100;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(curr_flap > num_flaps_per_duty){
//    updateDutyCycle();
    curr_flap = 1;
  }
  flap();
}

void updateDutyCycle(){
  if (curr_duty < 25) {
    curr_duty = curr_duty + 2;
  } else {
    curr_duty = 1; // Start the loop over.
    Serial.println("Starting new duty cycle");
  }
  Serial.println(curr_duty);
}

void updateTimePercentage(){
  if (curr_time_percentage < 40) {
    curr_time_percentage = curr_time_percentage + 5;
  } else {
    curr_time_percentage = 1; // Start the loop over.
    Serial.println("Starting new time percentage cycle");
  }
  Serial.println(curr_time_percentage);
}

static long last_changed = 0;
void flap(){
  // Check if need to switch direction.
  // Since this control sequence keeps pwm signal constant, need to set it once.
  if(millis() - last_changed >= time_to_switch_dir){
    dir = 1 - dir;
    last_changed = millis();
    curr_flap++;
    Serial.println("Flap.");
  }
  move_fin();
}

void move_fin(){
  int pwm = (int)(255 * curr_duty / 100);
//  Serial.print("Diff between last changed and current time:");
//  Serial.print(millis() - last_changed);
//  Serial.print(".\n");
//  Serial.print("Time percentage range:");
//  Serial.print(curr_time_percentage / 100.0 * time_to_switch_dir);
//  Serial.print(".\n");
  if(millis() - last_changed <= curr_time_percentage / 100.0 * time_to_switch_dir){ // Only supply pwm during time percentage
    if (dir) {
      Serial.println("RIGHT");
      analogWrite(head_r, pwm); // Set pwm to move right.
      analogWrite(head_l, 0);
      digitalWrite(LED, HIGH);
    }
    else {
      Serial.println("LEFT");
      analogWrite(head_r, 0);
      analogWrite(head_l, pwm); // Set pwm to move left.
      digitalWrite(LED, LOW);
    }
  } else{
      Serial.println("Zero PWM!!!");
      analogWrite(head_r, 0);
      analogWrite(head_l, 0); // Set pwm to move left.
  }
}
