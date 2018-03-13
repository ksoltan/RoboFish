#ifndef Joint_H
#define Joint_H

class Joint{
  public:
    Joint(int leftPin, int rightPin, bool isPwmTest = false);
    void LeftOnlySet(int duty, int deadZone = 0, bool isPwmTest = true);
    void RightOnlySet(int duty, int deadZone = 0, bool isPwmTest = true);
    void SimpleFlapSet(int duty, int deadZone, float frequency, bool isPwmTest = true);
    void Update();
    void SetPeriod(float frequency = 0.5);
    int getCurrFlapNum();
    int getCurrDuty();
    int getCurrDeadZone();
    void setDuty(int duty);
    void setDeadZone(int deadZone);

  private:
    enum flapMode { LEFT_ONLY, RIGHT_ONLY, SIMPLE_FLAP };
    enum dir {RIGHT, LEFT};

    flapMode  activeMode;

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
    void RightOnlyUpdate();
};
#endif // Joint_H

