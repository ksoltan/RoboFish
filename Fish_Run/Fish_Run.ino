#include "Joint.h"

// Skeleton fishSkeleton;
Joint Joint1(3, 5);
Joint Joint2(6, 10);

void setup()
{
  Serial.begin(9600);
  Joint1.SimpleFlapSet(100, 0, 4, 0);
  Joint2.SimpleFlapSet(100, 0, 1, 50);
}

void loop()
{
  // Call the test update which will update the joint if needed
  int res1 = Joint1.Update();
  int res2 = Joint2.Update();
  Serial.print(res1);
  Serial.print(" ");
  Serial.println(res2);
}
