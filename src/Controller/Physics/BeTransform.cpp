#include "BeTransform.hpp"

#include <glm/detail/type_quat.hpp>

BeTransform::BeTransform() {
    orientation = rp3d::Quaternion(0, 0, 0, 0);
    position    = rp3d::Vector3(0, 0, 0);
}

BeTransform::BeTransform(BeVector3 position, BeQuaternion orientation) {
    rp3d::Quaternion dir = rp3d::Quaternion(orientation.GetX(), orientation.GetY(),
                                            orientation.GetZ(), orientation.GetW());
    rp3d::Vector3 pos    = rp3d::Vector3(position.GetX(), position.GetY(), position.GetZ());
    transform            = rp3d::Transform(pos, dir);
}

BeTransform::BeTransform(glm::vec3 pos, glm::quat orient) {
    rp3d::Vector3 positions = rp3d::Vector3(pos.x, pos.y, pos.z);
    rp3d::Quaternion dir    = rp3d::Quaternion(orient.x, orient.y, orient.z, orient.w);

    orientation = dir;
    positions   = positions;
    transform   = rp3d::Transform(positions, dir);
}

BeTransform::BeTransform(const BeTransform &inputTransform) {
    position    = inputTransform.position;
    orientation = inputTransform.orientation;

    transform = rp3d::Transform(position, orientation);
}

BeTransform::BeTransform(const rp3d::Transform &inputTransform) {
    position    = inputTransform.getPosition();
    orientation = inputTransform.getOrientation();
    transform   = inputTransform;
}

BeTransform::~BeTransform() {}

BeQuaternion BeTransform::GetOrientation() {
    BeQuaternion orient = BeQuaternion(transform.getOrientation().x, transform.getOrientation().y,
                                       transform.getOrientation().z, transform.getOrientation().w);

    return orient;
}

void BeTransform::SetOrientation(BeQuaternion inputOrientation) {
    orientation = rp3d::Quaternion(inputOrientation.GetX(), inputOrientation.GetY(),
                                   inputOrientation.GetZ(), inputOrientation.GetW());
    transform.setOrientation(orientation);
}

void BeTransform::SetPosition(const BeVector3 &inputPosition) {
    position = rp3d::Vector3(inputPosition.GetX(), inputPosition.GetY(), inputPosition.GetZ());
    transform.setPosition(position);
}

glm::vec3 BeTransform::GetPosition() const {

    glm::vec3 pos(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);

    return pos;
}

void BeTransform::SetToIdentity() {
    transform.setToIdentity();
    position.setToZero();
    orientation.setToIdentity();
}

BeTransform BeTransform::GetInverse() {
    BeTransform result = BeTransform(transform.getInverse());
    return result;
}

BeTransform &BeTransform::operator=(const BeTransform &rhs) {
    position    = rhs.position;
    orientation = rhs.orientation;
    transform   = rhs.transform;
    return *this;
}

BeTransform &BeTransform::operator*(const BeTransform &rhs) {
    rp3d::Vector3 posResult     = position * rhs.position;
    rp3d::Quaternion quatResult = orientation * rhs.orientation;
    rp3d::Transform temp        = rp3d::Transform(posResult, quatResult);
    transform                   = temp;
    BeTransform result          = BeTransform(transform);
    return result;
}