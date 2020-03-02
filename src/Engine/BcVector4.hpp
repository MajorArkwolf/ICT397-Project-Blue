//
// Created by becky on 1/03/2020.
//

#pragma once

#include <bullet/LinearMath/btQuadWord.h>
#include "BcFloat.hpp"

class BcVector4 {
  public:
    BcVector4(BcFloat inputX, BcFloat inputY, BcFloat inputZ, BcFloat inputW);

    void SetX(BcFloat inputX);
    void SetY(BcFloat inputY);
    void SetZ(BcFloat inputZ);
    void SetW(BcFloat inputW);

    BcFloat GetX();
    BcFloat GetY();
    BcFloat GetZ();
    BcFloat GetW();


  private:
    btQuadWord *bcVec4;

};

