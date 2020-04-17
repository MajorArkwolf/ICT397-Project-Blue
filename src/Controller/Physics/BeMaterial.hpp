#pragma once

#include <iostream>
#include <reactphysics3d.h>

class BeMaterial {
  public:
    BeMaterial();
    BeMaterial(BeMaterial *mat);
    BeMaterial(rp3d::Material mat);
    void SetMaterial(rp3d::Material *target);
    ~BeMaterial();
    [[nodiscard]] rp3d::Material *GetMaterial() const ;
    void SetBounciness(float bounciness);
    BeMaterial &operator=(const BeMaterial &rhs);

  private:
    rp3d::Material *material;
};
