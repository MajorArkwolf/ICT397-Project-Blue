
#pragma once

#include <reactphysics3d.h>

#include "BeScalar.hpp"

class BeVector3 {
  public:
    /**
     * @brief default constructor
     */
    BeVector3();

    /**
     * @brief parameterised constructor
     * @param inputX x coord
     * @param inputY y coord
     * @param inputZ z coord
     */
    BeVector3(beScalar inputX, beScalar inputY, beScalar inputZ);

    /**
     * @brief copy constructor
     * @param inputVector target vector
     */
    BeVector3(const BeVector3 &inputVector);

    /**
     * @brief copy constructor from rp3d vector
     * @param inputVector rp3d vector
     */
    BeVector3(const rp3d::Vector3 &inputVector);

    /**
     * @brief destructor
     */
    ~BeVector3();

    /**
     * @brief set all individual coords
     * @param inputX x coord
     * @param inputY y coord
     * @param inputZ z coord
     */
    void SetAllValues(beScalar inputX, beScalar inputY, beScalar inputZ);

    /**
     * @brief getter for x coord
     * @return x coord
     */
    beScalar GetX() const;

    /**
     * @brief getter for y coord
     * @return y coord
     */
    beScalar GetY() const;

    /**
     * @brief getter for z coord
     * @return
     */
    beScalar GetZ() const;

    /**
     * @brief getter for magnitude of vector
     * @return magnitude
     */
    beScalar GetLength();

    /**
     * @brief magnitude squared
     * @return squared magnitude
     */
    beScalar GetLengthSquared();

    /**
     * @brief gets the unit vectir
     * @return unit vector
     */
    BeVector3 GetUnit() const;

    /**
     * @brief the normal
     * @return the normal
     */
    BeVector3 GetOrthogonal();

    /**
     * @brief whether the vector is a unit vector
     * @return boolean of whether the vector is a unit vector
     */
    bool IsUnit() const;

    /**
     * @brief test for zero
     * @return boolean of test for zero
     */
    bool IsZero() const;

    /**
     * @brief dot multiplication
     * @param rhs target vector
     * @return scalar of multiplication
     */
    double Dot(const BeVector3 &rhs) const;

    /**
     * @brief cross multiplication
     * @param rhs target vector
     * @return result of multiplication
     */
    BeVector3 Cross(const BeVector3 &rhs) const;

    /**
     * @brief to normalise the vector
     */
    void Normalise();

    /**
     * @brief getter for absolute
     * @return vector
     */
    BeVector3 GetAbsoluteVector() const;

    /**
     * @brief assignment operator
     * @param rhs target vector
     * @return vector
     */
    BeVector3 operator=(BeVector3 rhs);

    /**
     * @brief equality operator
     * @param rhs target vector
     * @return boolean
     */
    bool operator==(const BeVector3 &rhs);

    /**
     * @brief inequality operator
     * @param rhs target vector
     * @return boolean
     */
    bool operator!=(const BeVector3 &rhs);

    /**
     * @brief multiplication operator
     * @param rhs target vector
     * @return result vector
     */
    BeVector3 operator*(BeVector3 rhs);

  private:
    beScalar x;
    beScalar y;
    beScalar z;
    rp3d::Vector3 *vector3;
};
