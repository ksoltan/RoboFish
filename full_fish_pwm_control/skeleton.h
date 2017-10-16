#include "joint.h"

//array pin_pairs[] = [[3, 5], [6, 9], [10, 11]];
//Joint joints[3];

Joint j1(10, 11, .5, .5, 0);

class Skeleton {
  
  public:

    Skeleton() {
    };

    void update_skeleton() {
      j1.update_joint();
    }

};

// method to update each joint

// methods for different motions

