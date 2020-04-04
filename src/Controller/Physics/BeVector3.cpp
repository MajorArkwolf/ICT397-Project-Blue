#include "BeVector3.hpp"

BeVector3::BeVector3() {
    x       = 0;
    y       = 0;
    z       = 0;
    vector3 = new rp3d::Vector3(0, 0, 0);
}

BeVector3::BeVector3(beScalar inputX, beScalar inputY, beScalar inputZ) {
    vector3 = new rp3d::Vector3(inputX, inputY, inputZ);
}

BeVector3::BeVector3(const BeVector3 &inputVector) {
    x       = inputVector.x;
    y       = inputVector.y;
    z       = inputVector.z;
    vector3 = new rp3d::Vector3(inputVector.x, inputVector.y, inputVector.z);
}

BeVector3::BeVector3(const rp3d::Vector3 &inputVector) {
    x          = inputVector.x;
    y          = inputVector.y;
    z          = inputVector.z;
    vector3->x = inputVector.x;
    vector3->y = inputVector.y;
    vector3->z = inputVector.z;
}

BeVector3::~BeVector3() {
    delete vector3;
}

void BeVector3::SetAllValues(beScalar inputX, beScalar inputY, beScalar inputZ) {
    x          = inputX;
    y          = inputY;
    z          = inputZ;
    vector3->x = x;
    vector3->y = y;
    vector3->z = z;
}

beScalar BeVector3::GetX() const {
    return x;
}

beScalar BeVector3::GetY() const {
    return y;
}

beScalar BeVector3::GetZ() const {
    return z;
}

beScalar BeVector3::GetLength() {
    return vector3->length();
}

beScalar BeVector3::GetLengthSquared() {
    return vector3->lengthSquare();
}

BeVector3 BeVector3::GetUnit() const {
    BeVector3 result = BeVector3(vector3->getUnit());
    return result;
}

BeVector3 BeVector3::GetOrthogonal() {
    BeVector3 result = BeVector3(vector3->getOneUnitOrthogonalVector());
    return result;
}

bool BeVector3::IsUnit() const {
    return vector3->isUnit();
}

bool BeVector3::IsZero() const {
    return vector3->isZero();
}

double BeVector3::Dot(const BeVector3 &rhs) const {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    return vector3->dot(target);
}

BeVector3 BeVector3::Cross(const BeVector3 &rhs) const {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    rp3d::Vector3 result = vector3->cross(target);
    BeVector3 myResult   = BeVector3(result);
    return myResult;
}

void BeVector3::Normalise() {
    vector3->normalize();
    x = vector3->x;
    y = vector3->y;
    z = vector3->z;
}

BeVector3 BeVector3::GetAbsoluteVector() const {
    BeVector3 result = BeVector3(vector3->getAbsoluteVector());
    return result;
}

bool BeVector3::operator==(const BeVector3 &rhs) {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    return *vector3 == target;
}

bool BeVector3::operator!=(const BeVector3 &rhs) {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    return *vector3 != target;
}

BeVector3 BeVector3::operator=(BeVector3 rhs) {
    if (&rhs == this) {
        return *this;
    }

    x = rhs.x;
    y = rhs.y;
    z = rhs.z;

    vector3 = new rp3d::Vector3(rhs.x, rhs.y, rhs.z);

    return *this;
}

BeVector3 BeVector3::operator*(BeVector3 rhs) {
    rp3d::Vector3 target = rp3d::Vector3(rhs.GetX(), rhs.GetY(), rhs.GetZ());
    rp3d::Vector3 temp   = *vector3 * target;
    vector3              = &temp;
    BeVector3 result     = BeVector3(temp);
    return result;
}