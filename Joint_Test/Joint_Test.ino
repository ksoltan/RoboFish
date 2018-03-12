#include "TestSuite.h"

TestSuite testSuite;

void setup()
{
  Serial.begin(9600);
  testSuite.DeadZoneSweepSet(80, 10, 50, 10, 1, 5);
}

void loop()
{
  // Call the test update which will update the joint if needed
  testSuite.Update();
  delay(100);
}
