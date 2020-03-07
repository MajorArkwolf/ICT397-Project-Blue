#pragma once

#include <bullet/LinearMath/btVector3.h>
#include "BcFloat.hpp"

typedef btVector3 bcVector3;

class BcVector3 {
  public:
    BcVector3(BcFloat x, BcFloat y, BcFloat z);

    BcVector3 Cross(BcVector3 rhs);

  private:
    btVector3 *bcVector3;
};
