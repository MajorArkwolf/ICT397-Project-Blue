#include "Quaternion.hpp"

Quaternion::Quaternion() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
    quaternion = new rp3d::Quaternion(0,0,0,0);
}

Quaternion::Quaternion(scalar inputX, scalar inputY, scalar inputZ,
                               scalar inputW) {
    x = inputX;
    y = inputY;
    z = inputZ;
    w = inputW;
    quaternion = new rp3d::Quaternion(inputX, inputY, inputZ, inputW);
}

Quaternion::Quaternion(Vector3 inputVector, scalar inputW) {
    x = inputVector.GetX();
    y = inputVector.GetY();
    z = inputVector.GetZ();
    w = inputW;

    rp3d::Vector3 rhs = rp3d::Vector3(inputVector.GetX(), inputVector.GetY(), inputVector.GetZ());
    quaternion = new rp3d::Quaternion(rhs, inputW);
}

Quaternion::Quaternion(const rp3d::Quaternion &rhs){
    *quaternion = rhs;
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

void Quaternion::SetX(scalar inputX) {
    x = inputX;
}

scalar Quaternion::GetX() {
    return x;
}

void Quaternion::SetY(scalar inputY) {
    y = inputY;
}

scalar Quaternion::GetY() {
    return y;
}

void Quaternion::SetZ(scalar inputZ) {
    z = inputZ;
}

scalar Quaternion::GetZ() {
    return z;
}

void Quaternion::SetW(scalar inputW) {
    w = inputW;
}

scalar Quaternion::GetW() {
    return w;
}

void Quaternion::SetToZero() {
    quaternion->setToZero();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

void Quaternion::SetToIdentity() {
    quaternion->setToIdentity();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

Vector3 Quaternion::GetVector() {
    rp3d::Vector3 target = quaternion->getVectorV();
    Vector3 result = Vector3(target);
    return result;
}

scalar Quaternion::GetLength() {
    return quaternion->length();
}

scalar Quaternion::LengthSquared() {
    return  quaternion->lengthSquare();
}

void Quaternion::Normalised() {
    quaternion->normalize();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

void Quaternion::Inverse() {
    quaternion->inverse();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

Quaternion Quaternion::GetUnit() const{
    Quaternion result = Quaternion(quaternion->getUnit());
    return result;
}

Quaternion Quaternion::GetConjugate() const{
    Quaternion result = Quaternion(quaternion->getConjugate());
    return result;
}

Quaternion Quaternion::GetInverse() const{
    Quaternion result = Quaternion(quaternion->getInverse());
    return result;
}

void Quaternion::Identity() {
    quaternion->identity();
    x = quaternion->identity().x;
    y = quaternion->identity().y;
    z = quaternion->identity().z;
    w = quaternion->identity().w;
}

Quaternion Quaternion::FromEulerAngles(Vector3 inputVector) {
    rp3d::Vector3 target = rp3d::Vector3(inputVector.GetX(), inputVector.GetY(), inputVector.GetZ());
    Quaternion result = Quaternion(quaternion->fromEulerAngles(target));
    return result;
}

scalar Quaternion::Dot(Quaternion rhs) {
    rp3d::Quaternion target = rp3d::Quaternion(rhs.x, rhs.y, rhs.z, rhs.w);
    scalar result = quaternion->dot(target);

    return result;
}

void Quaternion::AngleAxis(scalar radianInput, Vector3 axisInput) {
    rp3d::Vector3 target = rp3d::Vector3(axisInput.GetX(), axisInput.GetY(), axisInput.GetZ());
    quaternion->getRotationAngleAxis(radianInput, target);
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

Quaternion Quaternion::Slerp(const Quaternion &target1, const Quaternion &target2, scalar interval) const{
    rp3d::Quaternion targetOne = rp3d::Quaternion(target1.x, target1.y, target1.z, target1.w);
    rp3d::Quaternion targetTwo = rp3d::Quaternion(target2.x, target2.y, target2.z, target2.w);
    Quaternion result = Quaternion(rp3d::Quaternion::slerp(targetOne, targetTwo, interval));
    return result;
}

Quaternion& Quaternion::operator=(Quaternion rhs){
    std::swap(x, rhs.x);
    std::swap(y, rhs.y);
    std::swap(z, rhs.z);
    std::swap(w, rhs.w);
    rp3d::Quaternion *temp = new rp3d::Quaternion(rhs.x, rhs.y, rhs.z, rhs.w);
    quaternion = temp;
}



