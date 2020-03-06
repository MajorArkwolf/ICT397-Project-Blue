//
// Created by becky on 26/02/2020.
//

#pragma once

#include <algorithm>
#include <bullet/LinearMath/btQuaternion.h>

#include "BcFloat.hpp"


class BcQuaternion{
  public:
    typedef btQuaternion bcQuaternion8;
    BcQuaternion(BcFloat inputX, BcFloat inputY, BcFloat inputZ, BcFloat inputW);

    void Rotation();

    BcQuaternion &operator=(btQuaternion rhs);
  private:
    btQuaternion *bcQuaternion;
};


