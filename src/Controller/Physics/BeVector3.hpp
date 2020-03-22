#pragma once

#include <reactphysics3d.h>

#include "BeScalar.hpp"

class BeVector3 {
  public:
    BeVector3();
    BeVector3(beScalar inputX, beScalar inputY, beScalar inputZ);
    BeVector3(const BeVector3 &inputVector);
    BeVector3(const rp3d::Vector3 &inputVector);
    ~BeVector3();
    void SetAllValues(beScalar inputX, beScalar inputY, beScalar inputZ) const;
    beScalar GetX() const;
    beScalar GetY() const;
    beScalar GetZ() const;
    beScalar GetLength();
    beScalar GetLengthSquared();
    BeVector3 GetUnit() const;
    BeVector3 GetOrthogonal();
    bool IsUnit() const;
    bool IsZero() const;
    double Dot(const BeVector3 &rhs) const;
    BeVector3 Cross(const BeVector3 &rhs) const;
    void Normalise();
    BeVector3 GetAbsoluteVector() const;
    BeVector3 operator=(BeVector3 rhs) const;
    bool operator==(const BeVector3 &rhs);
    bool operator!=(const BeVector3 &rhs);



  private:
    beScalar x;
    beScalar y;
    beScalar z;
    rp3d::Vector3 *vector3;


};
