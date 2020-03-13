#pragma once

#include <reactphysics3d.h>

#include "Quaternion.hpp"
#include "Vector3.hpp"

class Transform {
  public:
    Transform();
    Transform(Vector3 position, Quaternion orientation);
    Transform(const Transform &inputTransform);
    ~Transform();
    void SetOrientation(Quaternion inputOrientation);
    Quaternion GetOrientation();
    void SetPosition(const Vector3 &inputPosition);
    Vector3 GetPosition();
    void SetToIdentity();
    void GetInverse();
    Transform operator*(const Transform &rhs);


  private:
    Quaternion orientation;
    Vector3 position;

    rp3d::Transform *transform;
};
