#ifndef TestSuite_H
#define TestSuite_H

#include "Joint.h"

class TestSuite {
  public:
    TestSuite();
    void BasicSet(int duty, int deadZone, float frequency, int flapsPerSetting = 10);
    void DutySweepSet(int minDuty, int maxDuty, int dutyInterval, int deadZone, float frequency, int flapsPerSetting = 10);
    void DeadZoneSweepSet(int duty, int minDeadZone, int maxDeadZone, int deadZoneInterval, float frequency, int flapsPerSetting = 10);
    void Update();

  private:
    enum testType { BASIC, DUTY_SWEEP, DEAD_ZONE_SWEEP };

    testType activeTest;
    Joint Joint1; // Initialize in constructor

    // Duty parameters
    int MinDuty = 10;
    int MaxDuty;
    int DutyInterval = 0;

    // DeadZone parameters
    int MinDeadZone = 10;
    int MaxDeadZone;
    int DeadZoneInterval = 0;

    int TimePerSetting;
    int currNumFlaps = 0;
    float lastUpdate;
    float Frequency = 1;

    void BasicUpdate();
    void DutySweepUpdate();
    void DeadZoneSweepUpdate();


};
#endif // TestSuite_H
