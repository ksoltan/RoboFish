#include "TestSuite.h"

TestSuite testSuite;

void setup()
{
  Serial.begin(9600);
  // Set test to be run here:
  // FrequencySweepSet(int duty, int deadZone, float minFrequency, float maxFrequency, float frequencyInterval, int flapsPerSetting = 10);
  //BasicSet(int duty, int deadZone, float frequency, int flapsPerSetting = 10);
    testSuite.BasicSet(80, 50, 2);
//  testSuite.FrequencySet(80, 50,
}

void loop()
{
  // Call the test update which will update the joint if needed
  testSuite.Update();
}
