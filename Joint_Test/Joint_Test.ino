#include "TestSuite.h"

TestSuite testSuite;

void setup()
{
  Serial.begin(9600);
  testSuite.DeadZoneSweepSet(20, 50, 90, 10, 1, 5);
}

void loop()
{
  // Call the test update which will update the joint if needed
  testSuite.Update();
}

