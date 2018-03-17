#ifndef TestSuite_H
#define TestSuite_H

#include "Joint.h"

class TestSuite {
  public:
    TestSuite();
    void BasicSet(int duty, int deadZone, float frequency, int flapsPerSetting = 10);
    void DutySweepSet(int minDuty, int maxDuty, int dutyInterval, int deadZone, float frequency, int flapsPerSetting = 10);
    void DeadZoneSweepSet(int duty, int minDeadZone, int maxDeadZone, int deadZoneInterval, float frequency, int flapsPerSetting = 10);
    void FrequencySweepSet(int duty, int deadZone, float minFrequency, float maxFrequency, float frequencyInterval, int flapsPerSetting = 10);
    void Update();

  private:
    enum testType { BASIC, DUTY_SWEEP, DEAD_ZONE_SWEEP, FREQUENCY_SWEEP };

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

    // Frequency parameters
    float MinFrequency = 0.5;
    float MaxFrequency;
    float FrequencyInterval;

    void BasicUpdate();
    void DutySweepUpdate();
    void DeadZoneSweepUpdate();
    void FrequencySweepUpdate();
};
#endif // TestSuite_H
