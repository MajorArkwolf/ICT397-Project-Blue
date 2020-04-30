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

    /**
     * @brief parameterised constructor
     *  @param inputX euler coordinate
     *  @param inputY euler coordinate
     *  @param inputZ euler coordinate
     *  @param inputW euler angle
     */
    BeQuaternion(beScalar inputX, beScalar inputY, beScalar inputZ, beScalar inputW);

    /**
     * @brief parameterised constructor
     * @param inputVector euler vector
     * @param inputW axis angle
     */
    BeQuaternion(BeVector3 inputVector, beScalar inputW);

    /**
     * @brief cop constructor
     * @param rhs the quaternion to be copied
     */
    BeQuaternion(const rp3d::Quaternion &rhs);

    /**
     * @brief setter for x coord
     * @param inputX x coord
     */
    void SetX(beScalar inputX);

    /**
     * @brief gettfor x coord
     * @return x coord
     */
    beScalar GetX() const;

    /**
     * @brief setter for y coord
     * @param inputY y coord
     */
    void SetY(beScalar inputY);

    /**
     * @brief getter for y coord
     * @return y coord
     */
    beScalar GetY() const;

    /**
     * @brief setter for z coord
     * @param inputZ z coord
     */
    void SetZ(beScalar inputZ);

    /**
     * @brief getter for z coord
     * @return z coord
     */
    beScalar GetZ() const;

    /**
     * @brief setter for angle
     * @param inputW
     */
    void SetW(beScalar inputW);

    /**
     * @brief getter for angle
     * @return angle for quaternion
     */
    beScalar GetW() const;

    /**
     * @brief set quaternion to zero
     */
    void SetToZero();

    /**
     * @brief set quaternion to identity
     */
    void SetToIdentity();

    /**
     * @brief get vector component
     * @return vector coords
     */
    BeVector3 GetVector();

    /**
     * @brief gets the magnitude of the quaternion
     * @return the magnitude
     */
    beScalar GetLength();

    /**
     * @brief square of length
     * @return the square of length
     */
    beScalar LengthSquared();

    /**
     * @brief normlise to unit quaternion
     */
    void Normalised();

    /**
     * @brief sets the inverse of the quaternion
     */
    void Inverse();

    /**
     * @brief unit quaternion
     * @return the unit quaternion
     */
    BeQuaternion GetUnit() const;

    /**
     * @brief the conjugate
     * @return the conjugate quaternion
     */
    BeQuaternion GetConjugate() const;

    /**
     * @brief gets the inverse of the quaternion
     * @return inverse quaternion
     */
    BeQuaternion GetInverse() const;

    /**
     * @brief set to identity quaternion
     */
    void Identity();

    /**
     * @brief creates a quaternion from a vector
     * @param inputVector vector
     * @return quaternion
     */
    BeQuaternion FromEulerAngles(BeVector3 inputVector);

    /**
     * @brief dot multiplication of quaternion
     * @param rhs the quaternion to be multiplied
     * @return the scalar
     */
    beScalar Dot(BeQuaternion rhs);

    /**
     * @brief sets the axis angle for rotation
     * @param radianInput the amount to rotate
     * @param axisInput the axis to rotate around
     */
    void AngleAxis(beScalar radianInput, BeVector3 axisInput);

    /**
     * @brief rotation interpolation
     * @param target1 quaternion source
     * @param target2 quaternion destination
     * @param interval interval
     * @return interpolated quaternion
     */
    BeQuaternion Slerp(const BeQuaternion &target1, const BeQuaternion &target2,
                       beScalar interval) const;

    /**
     * @brief assignment operator
     * @param rhs the target quaternion
     * @return the assigned quaternion
     */
    BeQuaternion &operator=(BeQuaternion rhs);

    /**
     * @brief multiplication operator
     * @param rhs target quaternoin
     * @return result of multiplication
     */
    BeQuaternion &operator*(BeQuaternion rhs);

  private:
    beScalar x;
    beScalar y;
    beScalar z;
    beScalar w;
    rp3d::Quaternion *quaternion;
};
