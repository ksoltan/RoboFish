#include "joint.h"

//array pin_pairs[] = [[3, 5], [6, 9], [10, 11]];
//Joint joints[3];
int left = 10;
int right = 11;
Joint j1(left, right, .5, .25, 0);

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
