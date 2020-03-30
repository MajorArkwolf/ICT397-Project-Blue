#pragma once

#include <reactphysics3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BeQuaternion.hpp"
#include "BeVector3.hpp"

namespace BeReact{
    class BeTransform;
}


class BeReact::BeTransform {
  public:
    BeTransform();
    BeTransform(BeVector3 position, BeQuaternion orientation);
    BeTransform(glm::vec3 position, glm::quat orientation);
    BeTransform(const BeTransform &inputTransform);
    BeTransform(const rp3d::Transform &inputTransform);
    ~BeTransform();
    void SetOrientation(BeQuaternion inputOrientation);
    BeQuaternion GetOrientation();
    void SetPosition(const BeVector3 &inputPosition);
    BeVector3 GetPosition() const;
    void SetToIdentity();
    BeTransform GetInverse();
    BeTransform &operator=(const BeTransform &rhs);
    BeTransform &operator*(const BeTransform &rhs);


  private:
    BeQuaternion orientation;
    BeVector3 position;

    rp3d::Transform transform;
};
