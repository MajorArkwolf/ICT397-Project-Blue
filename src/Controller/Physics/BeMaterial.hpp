#pragma once

#include <iostream>
#include <reactphysics3d.h>

class BeMaterial {
  public:
    BeMaterial(BeMaterial target);
    rp3d::Material GetMaterial();
    void SetBounciness(float bounciness);
    BeMaterial operator=(BeMaterial rhs);

  private:
    rp3d::Material material;
};
