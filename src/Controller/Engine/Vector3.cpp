#include "Vector3.hpp"

Vector3::Vector3(){
    x = 0;
    y = 0;
    z = 0;
    vector3 = new rp3d::Vector3(0, 0, 0);
}


Vector3::Vector3(scalar inputX, scalar inputY, scalar inputZ) {
   vector3 = new rp3d::Vector3(inputX, inputY, inputZ);
}

Vector3::Vector3(const Vector3 &inputVector) {
    x = inputVector.x;
    y = inputVector.y;
    z = inputVector.z;
    vector3 = new rp3d::Vector3(inputVector.x, inputVector.y, inputVector.z);
}

Vector3::Vector3(const rp3d::Vector3 &inputVector)
{
    x = inputVector.x;
    y = inputVector.y;
    z = inputVector.z;
    vector3->x = inputVector.x;
    vector3->y = inputVector.y;
    vector3->z = inputVector.z;
}

Vector3::~Vector3(){
    delete vector3;
}

void Vector3::SetAllValues(scalar inputX, scalar inputY, scalar inputZ) {
    x = inputX;
    y = inputY;
    z = inputZ;
    vector3->x = x;
    vector3->y = y;
    vector3->z = z;
}

scalar Vector3::GetX() {
    return x;
}

scalar Vector3::GetY() {
    return y;
}

scalar Vector3::GetZ() {
    return z;
}

scalar Vector3::GetLength() {
    return vector3->length();
}

scalar Vector3::GetLengthSquared() {
    return vector3->lengthSquare();
}

Vector3 Vector3::GetUnit() const{
    Vector3 result = Vector3(vector3->getUnit());
    return result;
}

Vector3 Vector3::GetOrthogonal() {
    Vector3 result = Vector3(vector3->getOneUnitOrthogonalVector());
    return result;
}

bool Vector3::IsUnit() const {
    return vector3->isUnit();
}

bool Vector3::IsZero() const {
    return vector3->isZero();
}

double Vector3::Dot(const Vector3 &rhs) const {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    return vector3->dot(target);
}

Vector3 Vector3::Cross(const Vector3 &rhs) const {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    rp3d::Vector3 result =  vector3->cross(target);
    Vector3 myResult = Vector3(result);
    return myResult;
}

void Vector3::Normalise() {
    vector3->normalize();
    x = vector3->x;
    y = vector3->y;
    z = vector3->z;
}

Vector3 Vector3::GetAbsoluteVector() const {
    Vector3 result = Vector3(vector3->getAbsoluteVector());
    return result;
}

bool Vector3::operator==(const Vector3 &rhs) {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    return *vector3 == target;
}

bool Vector3::operator!=(const Vector3 &rhs) {
    rp3d::Vector3 target = rp3d::Vector3(rhs.x, rhs.y, rhs.z);
    return *vector3 != target;
}
