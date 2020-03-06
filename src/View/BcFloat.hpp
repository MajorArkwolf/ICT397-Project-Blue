//
// Created by becky on 26/02/2020.
//

#pragma once

#include <bullet/LinearMath/btScalar.h>

typedef btScalar bcFloat8;

class BcFloat {
  public:
    BcFloat(bcFloat8 source);
    operator btScalar ();
    bcFloat8 operator +(bcFloat8 target);
    bcFloat8 operator -(bcFloat8 target);
    bcFloat8 operator *(bcFloat8 target);

  private:
    bcFloat8 bcFloat;

};
