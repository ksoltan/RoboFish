#include "TestSuite.h"

#define LEFT_PIN 3
#define RIGHT_PIN 5

TestSuite testSuite(LEFT_PIN, RIGHT_PIN);

void setup()
{
  Serial.begin(9600);
  testSuite.LeftOnlySet(50);
//  testSuite.DutySweepSet(10, 50, 10, 50, 0.5, true, 4);
//  testSuite.DutySweepSet(10, 50, 10, 50, 0.5, true, 4);
}

void loop()
{
  // Call the test update which will update the joint if needed
  testSuite.Update();
  delay(50);
}
