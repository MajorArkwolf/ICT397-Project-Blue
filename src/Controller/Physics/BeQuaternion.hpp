#pragma once

#include <reactphysics3d.h>

#include "BeScalar.hpp"
#include "BeVector3.hpp"

class BeQuaternion {
  public:
    /**
     *  @brief default constructor
     *  @param inputX euler coordinate
     *  @param inputY euler coordinate
     *  @param inputZ euler coordinate
     *  @param inputW euler angle
     *  @return void
     */
    BeQuaternion();
    BeQuaternion(beScalar inputX, beScalar inputY, beScalar inputZ, beScalar inputW);
    BeQuaternion(BeVector3 inputVector, beScalar inputW);
    BeQuaternion(const rp3d::Quaternion &rhs);

    void SetX(beScalar inputX);
    beScalar GetX() const;
    void SetY(beScalar inputY);
    beScalar GetY() const;
    void SetZ(beScalar inputZ);
    beScalar GetZ() const;
    void SetW(beScalar inputW);
    beScalar GetW() const;

    void SetToZero();
    void SetToIdentity();
    BeVector3 GetVector();
    beScalar GetLength();
    beScalar LengthSquared();
    void Normalised();
    void Inverse();
    // https://stackoverflow.com/questions/50312460/c-class-design-base-class-inheritance-or-facade-design-pattern
    BeQuaternion GetUnit() const;
    BeQuaternion GetConjugate() const;
    BeQuaternion GetInverse() const;
    void Identity();
    BeQuaternion FromEulerAngles(BeVector3 inputVector);
    beScalar Dot(BeQuaternion rhs);
    void AngleAxis(beScalar radianInput, BeVector3 axisInput);
    BeQuaternion Slerp(const BeQuaternion &target1, const BeQuaternion &target2,
                       beScalar interval) const;
    BeQuaternion &operator=(BeQuaternion rhs);
    BeQuaternion &operator*(BeQuaternion rhs);

  private:
    beScalar x;
    beScalar y;
    beScalar z;
    beScalar w;
    rp3d::Quaternion *quaternion;
};
