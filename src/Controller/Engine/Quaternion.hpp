#pragma once

#include <reactphysics3d.h>

#include "Scalar.hpp"
#include "Vector3.hpp"

class Quaternion {
  public:
    /**
    *  @brief default constructor
    *  @param inputX euler coordinate
    *  @param inputY euler coordinate
    *  @param inputZ euler coordinate
    *  @param inputW euler angle
    *  @return void
    */
    Quaternion();
    Quaternion(scalar inputX, scalar inputY, scalar inputZ, scalar inputW);
    Quaternion(Vector3 inputVector, scalar inputW);
    Quaternion(const rp3d::Quaternion &rhs);

    void SetX(scalar inputX);
    scalar  GetX();
    void SetY(scalar inputY);
    scalar  GetY();
    void SetZ(scalar inputZ);
    scalar  GetZ();
    void SetW(scalar inputW);
    scalar  GetW();

    void SetToZero();
    void SetToIdentity();
    Vector3 GetVector();
    scalar GetLength();
    scalar LengthSquared();
    void Normalised();
    void Inverse();
    // https://stackoverflow.com/questions/50312460/c-class-design-base-class-inheritance-or-facade-design-pattern
    Quaternion GetUnit() const;
    Quaternion GetConjugate() const;
    Quaternion GetInverse() const;
    void Identity();
    Quaternion FromEulerAngles(Vector3 inputVector);
    scalar Dot(Quaternion rhs);
    void AngleAxis(scalar radianInput, Vector3 axisInput);
    Quaternion Slerp(const Quaternion &target1, const Quaternion &target2, scalar interval) const;
    Quaternion& operator=(Quaternion rhs);


  private:
    scalar x;
    scalar y;
    scalar z;
    scalar w;
    rp3d::Quaternion *quaternion;
};
