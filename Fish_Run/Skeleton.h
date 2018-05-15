#ifndef Skeleton_H
#define Skeleton_H

#include "Joint.h"

// Configured to only swim straight. For turning, will need multiple states and memory of flap settings of each joint.
class Skeleton {
  public:
    Skeleton();
    void Joint1Set(int duty, int deadZone, float frequency, float phase);
    void Joint2Set(int duty, int deadZone, float frequency, float phase);
    void Joint3Set(int duty, int deadZone, float frequency, float phase);
    void Update();
    void TurnLeft();
    void TurnRight();
    void GoStraight();
    //Add function that sets joint not to move.

  private:
    Joint Joint1;
    Joint Joint2;
    Joint Joint3;
    long timeLastUpdated = 0;
    void UpdateSkeleton(); // Function to switch between turning and swimming straight.
};
#endif // Skeleton_H
