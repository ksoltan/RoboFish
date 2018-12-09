#ifndef Joint_H
#define Joint_H

class Joint{
  public:
    Joint(int leftPin, int rightPin, bool isPwmTest = true);
    void SimpleFlapSet(int duty, int deadZone, float frequency, float phase);
    void FlapSet();
    void LeftOnlySet();
    void RightOnlySet();
    int Update(); // CAN BE VOID, RETURNS INT FOR SERIAL PLOTTER VIS

    int getCurrFlapNum();
    int getCurrDuty();
    int getCurrDeadZone();
    float getCurrFrequency();

    void setDuty(int duty);
    void setDeadZone(int deadZone);
    void setFrequency(float frequency = 0.5);
    void setPhase(float phase = 0);

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

    int currDuty = 50;
    int currDeadZone = 0; // dead zone is percent of period.
    float phaseOffset = 0; // in ms.

    // Flap Update Functions
    int Flap(); // CAN BE VOID, RETURNS INT FOR SERIAL PLOTTER VIS
    int UpdateFlapDir(); // CAN BE VOID, RETURNS INT FOR SERIAL PLOTTER VIS
    void UpdatePins();
    void LeftOnlyUpdate();
    void RightOnlyUpdate();
};
#endif // Joint_H
