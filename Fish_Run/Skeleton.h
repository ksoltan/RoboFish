#ifndef Skeleton_H
#define Skeleton_H

#include "Joint.h"

class Skeleton {
  public:
    Skeleton();
    void Joint1Set(int duty, int deadZone, float frequency, float phase);
    void Joint2Set(int duty, int deadZone, float frequency, float phase);
    void Joint3Set(int duty, int deadZone, float frequency, float phase);
    void Update();

  private:
    // Define separate joints, initialize in constructor.
    // HOW DO YOU SET THE PHASE OFFSET FOR A JOINT?
    // - Addition to the compare value? Delay time?
    Joint Joint1;
    Joint Joint2;
    Joint Joint3;
};
#endif // Skeleton_H
