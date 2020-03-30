#pragma once

#include <reactphysics3d.h>

typedef rp3d::HeightFieldShape::HeightDataType beHeightType;

class BeHeightField {
  public:


    BeHeightField();

  private:
    rp3d::HeightFieldShape beHeightField;

};
