// Tests supported:
enum testType { SIMPLE_FLAP, DUTY_SWEEP, DEAD_ZONE_SWEEP };
enum dir {RIGHT, LEFT};

class TestSuite{
  public:
    // Member Variables:
    testType  ActiveTest;  // which pattern is running

    // Joint pin settings
    int LeftPin;
    int RightPin;
    int LED = 13;
    bool isPwm = false; // Toggle bang-bang and pwm.

    // Flapping settings
    dir currDir = RIGHT;
    int currFlapNum;

    // Duty settings
    int MinDuty;
    int MaxDuty;
    int currDuty;
    int DutyInterval;

    // Dead Zone settings
    int MinDeadZone;
    int MaxDeadZone;
    int currDeadZone; // dead zone is percent of period.
    int DeadZoneInterval;

    long Period;   // milliseconds. Period of whole sine wave.
    long lastUpdate; // last update of position.
    int FlapsPerSetting; // num flaps before setting update.

    // Constructor - calls base-class constructor to initialize strip
    TestSuite(int leftPin, int rightPin, float frequency = 0.5, int duty = 100, int deadZone = 50, bool isPwmTest = false)
    {
      pinMode(leftPin, OUTPUT);
      pinMode(rightPin, OUTPUT);
      pinMode(LED, OUTPUT);
      SimpleFlapSet(duty, deadZone, frequency, isPwmTest);
    }

    void SimpleFlapSet(int duty, int deadZone, float frequency, bool isPwmTest){
      currDuty = duty;
      currDeadZone = deadZone;
      isPwm = isPwmTest;
      currFlapNum = 1;
      ActiveTest = SIMPLE_FLAP;
      Serial.println("Set Simple Flap."); // When set, may not print correclt as the Serial isn't initialized until the main sketch setup.
      SetPeriod(frequency);
    }

    void Update(){
      // Update parameters depending on test.
      switch(ActiveTest){
        case DUTY_SWEEP:
          DutySweepUpdate();
          break;
        case DEAD_ZONE_SWEEP:
          DeadZoneSweepUpdate();
          break;
        default:
          break;
      }
      Flap();
    }

    void Flap(){
      UpdateFlapDir();
      UpdatePins();
    }

    void UpdateFlapDir(){
      if(millis() - lastUpdate >= Period / 2){
        // currDir = 1 - CurrDir; // Switch direction
        if (currDir == RIGHT){
          currDir = LEFT;
        } else{
          currDir = RIGHT;
        }
        lastUpdate = millis();
        currFlapNum++; // Another flap has been completed.
        Serial.println("Flap.");
      }
    }

    void UpdatePins(){
      // Check if not in dead zone.
//      Serial.print("Diff between last changed and current time:");
//      Serial.print(millis() - lastUpdate);
//      Serial.print(".\n");
//      Serial.print("Time percentage range:");
//      Serial.print(Period / 2 * (100 - currDeadZone) / 100);
//      Serial.print(".\n");
      if(millis() - lastUpdate <= Period / 2 * (100 - currDeadZone) / 100){
        if(isPwm){ // Use pwm to the pins.
          int pwm = (int)(255 * currDuty / 100);
          if(currDir == RIGHT){
            Serial.println("RIGHT");
            analogWrite(RightPin, pwm);
            analogWrite(LeftPin, 0);
            digitalWrite(LED, HIGH);
          }else{
            Serial.println("LEFT");
            analogWrite(RightPin, 0);
            analogWrite(LeftPin, pwm);
            digitalWrite(LED, LOW);
          }
        } else{ // Bang-bang control
          if(currDir == RIGHT){
            Serial.println("RIGHT");
            digitalWrite(RightPin, HIGH);
            digitalWrite(LeftPin, LOW);
            digitalWrite(LED, HIGH);
          }else{
            Serial.println("LEFT");
            analogWrite(RightPin, LOW);
            analogWrite(LeftPin, HIGH);
            digitalWrite(LED, LOW);
          }
        }
      } else{
        Serial.println("ZERO PWM!!!");
        digitalWrite(RightPin, LOW);
        digitalWrite(LeftPin, LOW);
      }
    }

    void SetPeriod(float frequency){
      Period = (int)(1 / frequency * 1000); // convert to ms.
      Serial.print("Period set to: ");
      Serial.print(Period);
      Serial.print("ms.\n");
    }

    void DutySweepSet(int minDuty, int maxDuty, int dutyInterval, int deadZone, float frequency, bool isPwmTest, int flapsPerSetting){
      MinDuty = minDuty;
      MaxDuty = maxDuty;
      DutyInterval = dutyInterval;
      currDuty = minDuty;
      currDeadZone = deadZone;
      isPwm = isPwmTest;
      FlapsPerSetting = flapsPerSetting;
      ActiveTest = DUTY_SWEEP;
      Serial.print("Set Duty Sweep.\n");
      SetPeriod(frequency);
    }

    void DutySweepUpdate(){
      if(currFlapNum > FlapsPerSetting){
        currFlapNum = 1; // Reset flap number.
        // Update duty.
        if(currDuty >= MaxDuty){
          currDuty = MinDuty;
        }else{
          currDuty += DutyInterval;
        }
        Serial.print("Duty updated to: ");
        Serial.print(currDuty);
        Serial.print(".\n");
      }
    }

    void DeadZoneSweepSet(int minDeadZone, int maxDeadZone, int deadZoneInterval, int duty, float frequency, bool isPwmTest, int flapsPerSetting){
      MinDeadZone = minDeadZone;
      MaxDeadZone = maxDeadZone;
      DeadZoneInterval = deadZoneInterval;
      currDuty = duty;
      currDeadZone = minDeadZone;
      isPwm = isPwmTest;
      FlapsPerSetting = flapsPerSetting;
      ActiveTest = DEAD_ZONE_SWEEP;
      Serial.print("Set Dead Zone Sweep.\n");
      SetPeriod(frequency);
    }

    void DeadZoneSweepUpdate(){
      if(currFlapNum > FlapsPerSetting){
        currFlapNum = 1; // Reset flap number.
        // Update duty.
        if(currDeadZone >= MaxDeadZone){
          currDeadZone = MinDeadZone;
        }else{
          currDeadZone += DeadZoneInterval;
        }
        Serial.print("Dead zone updated to: ");
        Serial.print(currDeadZone);
        Serial.print(".\n");
      }
    }
};
