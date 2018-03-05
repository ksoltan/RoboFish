#include "skeleton.h"

Skeleton s1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  s1.update_skeleton();
}
