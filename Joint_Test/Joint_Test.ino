#include "TestSuite.h"

TestSuite testSuite;

void setup()
{
  Serial.begin(9600);
  testSuite.FrequencySweepSet(20, 30, 0.5, 3, 0.5);
}

void loop()
{
  // Call the test update which will update the joint if needed
  testSuite.Update();
}

