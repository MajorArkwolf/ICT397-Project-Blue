#include "BeQuaternion.hpp"

BeQuaternion::BeQuaternion() {
    x          = 0;
    y          = 0;
    z          = 0;
    w          = 0;
    quaternion = new rp3d::Quaternion(0, 0, 0, 0);
}

BeQuaternion::BeQuaternion(beScalar inputX, beScalar inputY, beScalar inputZ,
                           beScalar inputW) {
    x          = inputX;
    y          = inputY;
    z          = inputZ;
    w          = inputW;
    quaternion = new rp3d::Quaternion(inputX, inputY, inputZ, inputW);
}

BeQuaternion::BeQuaternion(BeVector3 inputVector, beScalar inputW) {
    x = inputVector.GetX();
    y = inputVector.GetY();
    z = inputVector.GetZ();
    w = inputW;

    rp3d::Vector3 rhs =
        rp3d::Vector3(inputVector.GetX(), inputVector.GetY(), inputVector.GetZ());
    quaternion = new rp3d::Quaternion(rhs, inputW);
}

BeQuaternion::BeQuaternion(const rp3d::Quaternion &rhs) {
    *quaternion = rhs;
    x           = quaternion->x;
    y           = quaternion->y;
    z           = quaternion->z;
    w           = quaternion->w;
}

void BeQuaternion::SetX(beScalar inputX) {
    x = inputX;
}

beScalar BeQuaternion::GetX() const {
    return x;
}

void BeQuaternion::SetY(beScalar inputY) {
    y = inputY;
}

beScalar BeQuaternion::GetY() const {
    return y;
}

void BeQuaternion::SetZ(beScalar inputZ) {
    z = inputZ;
}

beScalar BeQuaternion::GetZ() const {
    return z;
}

void BeQuaternion::SetW(beScalar inputW) {
    w = inputW;
}

beScalar BeQuaternion::GetW() const {
    return w;
}

void BeQuaternion::SetToZero() {
    quaternion->setToZero();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

void BeQuaternion::SetToIdentity() {
    quaternion->setToIdentity();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

BeVector3 BeQuaternion::GetVector() {
    rp3d::Vector3 target = quaternion->getVectorV();
    BeVector3 result     = BeVector3(target);
    return result;
}

beScalar BeQuaternion::GetLength() {
    return quaternion->length();
}

beScalar BeQuaternion::LengthSquared() {
    return quaternion->lengthSquare();
}

void BeQuaternion::Normalised() {
    quaternion->normalize();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

void BeQuaternion::Inverse() {
    quaternion->inverse();
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

BeQuaternion BeQuaternion::GetUnit() const {
    BeQuaternion result = BeQuaternion(quaternion->getUnit());
    return result;
}

BeQuaternion BeQuaternion::GetConjugate() const {
    BeQuaternion result = BeQuaternion(quaternion->getConjugate());
    return result;
}

BeQuaternion BeQuaternion::GetInverse() const {
    BeQuaternion result = BeQuaternion(quaternion->getInverse());
    return result;
}

void BeQuaternion::Identity() {
    quaternion->identity();
    x = quaternion->identity().x;
    y = quaternion->identity().y;
    z = quaternion->identity().z;
    w = quaternion->identity().w;
}

BeQuaternion BeQuaternion::FromEulerAngles(BeVector3 inputVector) {
    rp3d::Vector3 target =
        rp3d::Vector3(inputVector.GetX(), inputVector.GetY(), inputVector.GetZ());
    BeQuaternion result = BeQuaternion(quaternion->fromEulerAngles(target));
    return result;
}

beScalar BeQuaternion::Dot(BeQuaternion rhs) {
    rp3d::Quaternion target = rp3d::Quaternion(rhs.x, rhs.y, rhs.z, rhs.w);
    beScalar result         = quaternion->dot(target);

    return result;
}

void BeQuaternion::AngleAxis(beScalar radianInput, BeVector3 axisInput) {
    rp3d::Vector3 target =
        rp3d::Vector3(axisInput.GetX(), axisInput.GetY(), axisInput.GetZ());
    quaternion->getRotationAngleAxis(radianInput, target);
    x = quaternion->x;
    y = quaternion->y;
    z = quaternion->z;
    w = quaternion->w;
}

BeQuaternion BeQuaternion::Slerp(const BeQuaternion &target1,
                                 const BeQuaternion &target2,
                                 beScalar interval) const {
    rp3d::Quaternion targetOne =
        rp3d::Quaternion(target1.x, target1.y, target1.z, target1.w);
    rp3d::Quaternion targetTwo =
        rp3d::Quaternion(target2.x, target2.y, target2.z, target2.w);
    BeQuaternion result =
        BeQuaternion(rp3d::Quaternion::slerp(targetOne, targetTwo, interval));
    return result;
}

BeQuaternion &BeQuaternion::operator=(BeQuaternion rhs) {

    if (&rhs == this) {
        return *this;
    }

    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;

    auto *temp = new rp3d::Quaternion(rhs.x, rhs.y, rhs.z, rhs.w);
    quaternion = temp;

    return *this;
}

BeQuaternion &BeQuaternion::operator*(BeQuaternion rhs) {
    rp3d::Quaternion target =
        rp3d::Quaternion(rhs.GetX(), rhs.GetY(), rhs.GetZ(), rhs.GetW());
    rp3d::Quaternion temp = *quaternion * target;
    quaternion            = &temp;
    BeQuaternion result   = BeQuaternion(temp);
    return result;
}
