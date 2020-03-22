#pragma once

#include <reactphysics3d.h>

#include "BeQuaternion.hpp"
#include "BeVector3.hpp"

class BeTransform {
  public:
    BeTransform();
    BeTransform(BeVector3 position, BeQuaternion orientation);
    BeTransform(const BeTransform &inputTransform);
    BeTransform(const rp3d::Transform &inputTransform);
    ~BeTransform();
    void SetOrientation(BeQuaternion inputOrientation);
    BeQuaternion GetOrientation() const;
    void SetPosition(const BeVector3 &inputPosition);
    BeVector3 GetPosition() const;
    void SetToIdentity();
    BeTransform GetInverse();
    BeTransform operator*(const BeTransform &rhs);


  private:
    BeQuaternion *orientation;
    BeVector3 *position;

    rp3d::Transform *transform;
};
