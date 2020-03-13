#pragma once

#include <reactphysics3d.h>

#include "Scalar.hpp"

class Vector3 {
  public:
    Vector3();
    Vector3(scalar inputX, scalar inputY, scalar inputZ);
    Vector3(const Vector3 &inputVector);
    Vector3(const rp3d::Vector3 &inputVector);
    ~Vector3();
    void SetAllValues(scalar inputX, scalar inputY, scalar inputZ);
    scalar GetX();
    scalar GetY();
    scalar GetZ();
    scalar GetLength();
    scalar GetLengthSquared();
    Vector3 GetUnit() const;
    Vector3 GetOrthogonal();
    bool IsUnit() const;
    bool IsZero() const;
    double Dot(const Vector3 &rhs) const;
    Vector3 Cross(const Vector3 &rhs) const;
    void Normalise();
    Vector3 GetAbsoluteVector() const;
    Vector3 operator=(Vector3 rhs) const;
    bool operator==(const Vector3 &rhs);
    bool operator!=(const Vector3 &rhs);



  private:
    scalar x;
    scalar y;
    scalar z;
    rp3d::Vector3 *vector3;


};
