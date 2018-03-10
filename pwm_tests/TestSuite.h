#ifndef Test_Suite_H
#define Test_Suite_H

class TestSuite{
  public:
    TestSuite(int leftPin, int rightPin, bool isPwmTest = false);
    void SimpleFlapSet(int duty, int deadZone, float frequency, bool isPwmTest);
    void LeftOnlySet(int duty, bool isPwmTest = true);
    void Update();
    void SetPeriod(float frequency = 0.5);
    
  private:
    enum testType { LEFT_ONLY, SIMPLE_FLAP, DUTY_SWEEP, DEAD_ZONE_SWEEP };
    enum dir {RIGHT, LEFT};

    testType  activeTest;

    // Joint pin settings
    int LeftPin;
    int RightPin;
    const int LED = 13;
    bool isPwm = false; // Toggle bang-bang and pwm.

    // Flapping settings
    dir currDir = RIGHT;
    int currFlapNum = 1;
    long period = 1000;   // milliseconds. Period of whole sine wave.
    long lastUpdate; // last update of position.

    // Duty settings
    int currDuty = 50;

    // Dead Zone settings
    int currDeadZone = 0; // dead zone is percent of period.
    
    // Flap Update Functions
    void Flap();
    void UpdateFlapDir();
    void UpdatePins();
    void LeftOnlyUpdate();
};
#endif // Test_Suite_H

