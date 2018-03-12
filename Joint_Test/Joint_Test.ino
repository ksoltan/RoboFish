#include "Joint.h"

#define LEFT_PIN 3
#define RIGHT_PIN 5

Joint Joint1(LEFT_PIN, RIGHT_PIN);

void setup()
{
  Serial.begin(9600);
}

int count = 0;
long lastUpdate = millis();
void loop()
{
  // Call the test update which will update the joint if needed
  Joint1.Update();
  delay(50);
  if (millis() - lastUpdate > 5000) {
    count++;
    switch (count % 3) {
      case 0:
        Joint1.SimpleFlapSet(90, 50, 1, true);
        break;
      case 1:
        Joint1.LeftOnlySet(80);
        break;
      case 2:
        Joint1.RightOnlySet(80);
        break;
      default:
        break;
    }
    lastUpdate = millis();
  }
}
