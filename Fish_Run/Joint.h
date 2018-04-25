#ifndef Joint_H
#define Joint_H

class Joint{
  public:
    Joint(int leftPin, int rightPin, bool isPwmTest = true);
    void LeftOnlySet(int duty, int deadZone = 0);
    void RightOnlySet(int duty, int deadZone = 0);
    void SimpleFlapSet(int duty, int deadZone, float frequency, float phase);
    int Update(); // CAN BE VOID

    int getCurrFlapNum();
    int getCurrDuty();
    int getCurrDeadZone();
    float getCurrFrequency();
    void setDuty(int duty);
    void setDeadZone(int deadZone);
    void setFrequency(float frequency= 0.5);

  private:
    enum flapMode { LEFT_ONLY, RIGHT_ONLY, SIMPLE_FLAP };
    enum dir {RIGHT, LEFT};

    flapMode  activeMode;

    // Joint pin settings
    int LeftPin;
    int RightPin;
    const int LED = 13;
    bool isPwm = true; // Toggle bang-bang and PWM. Default to using PWM.

    // Flapping settings
    dir currDir = RIGHT;
    int currFlapNum = 1;
    long period = 1000;   // milliseconds. Period of whole sine wave.
    long lastUpdate; // last update of position.

    // Duty settings
    int currDuty = 50;

    // Dead Zone settings
    int currDeadZone = 0; // dead zone is percent of period.

    float phaseOffset = 0;

    // Flap Update Functions
    int Flap(); // CAN BE VOID
    int UpdateFlapDir(); // CAN BE VOID
    void UpdatePins();
    void LeftOnlyUpdate();
    void RightOnlyUpdate();
};
#endif // Joint_H
