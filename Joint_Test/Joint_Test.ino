#include "TestSuite.h"

TestSuite testSuite;

void setup()
{
  Serial.begin(9600);
  // Set test to be run here:
  // FrequencySweepSet(int duty, int deadZone, float minFrequency, float maxFrequency, float frequencyInterval, int flapsPerSetting = 10);
  testSuite.FrequencySweepSet(80, 80, 1, 4, 1);
}

void loop()
{
  // Call the test update which will update the joint if needed
  testSuite.Update();
}
