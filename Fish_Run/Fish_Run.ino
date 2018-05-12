#include "Skeleton.h"

 Skeleton fishSkeleton;
// For generate_deflection_sequence([28, 26, 26, 28], @get_posture_short_fish)
// Amplitude Frequency  Phase (ms)
// 6.7606    5.9840    83.57  Joint1 (Head)
// 18.4154   5.9840   -21.70  Joint2
// 18.4154   5.9840    29.26  Joint3

void setup()
{
  Serial.begin(9600);
  fishSkeleton.Joint1Set(50, 50, 4, 100);
  fishSkeleton.Joint2Set(70, 40, 4, -50);
  fishSkeleton.Joint3Set(100, 20, 4, 50);
}

void loop()
{
  // Call the test update which will update the joint if needed
  fishSkeleton.Update();
}
