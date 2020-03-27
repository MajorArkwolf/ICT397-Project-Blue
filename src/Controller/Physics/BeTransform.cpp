#include "BeTransform.hpp"

BeTransform::BeTransform() {
    orientation = BeQuaternion(0, 0, 0, 0);
    position    = BeVector3(0, 0, 0);
}

BeTransform::BeTransform(BeVector3 position, BeQuaternion orientation) {
    orientation = orientation;
    position    = position;

    auto *pos =
        new rp3d::Vector3(position.GetX(), position.GetY(), position.GetZ());
    auto *direction = new rp3d::Quaternion(orientation.GetX(), orientation.GetY(),
                                           orientation.GetZ(), orientation.GetW());
    transform       = rp3d::Transform(*pos, *direction);

    delete pos;
    delete direction;
}

BeTransform::BeTransform(const BeTransform &inputTransform) {
    position    = inputTransform.position;
    orientation = inputTransform.orientation;

    auto *pos = new rp3d::Vector3(inputTransform.position.GetX(),
                                  inputTransform.position.GetY(),
                                  inputTransform.position.GetZ());

    auto *direction = new rp3d::Quaternion(
        inputTransform.orientation.GetX(), inputTransform.orientation.GetY(),
        inputTransform.orientation.GetZ(), inputTransform.orientation.GetW());

    transform = rp3d::Transform(*pos, *direction);

    delete pos;
    delete direction;
}

BeTransform::BeTransform(const rp3d::Transform &inputTransform) {
    transform = inputTransform;
    position =
        BeVector3(inputTransform.getPosition().x, inputTransform.getPosition().y,
                  inputTransform.getPosition().z);
    orientation = BeQuaternion(transform.getOrientation());
}

BeTransform::~BeTransform() {}

BeQuaternion BeTransform::GetOrientation() {
    orientation =
        BeQuaternion(transform.getOrientation().x, transform.getOrientation().y,
                     transform.getOrientation().z, transform.getOrientation().w);

    return orientation;
}

void BeTransform::SetOrientation(BeQuaternion inputOrientation) {
    orientation = inputOrientation;

    auto *dir =
        new rp3d::Quaternion(inputOrientation.GetX(), inputOrientation.GetY(),
                             inputOrientation.GetZ(), inputOrientation.GetW());

    transform.setOrientation(*dir);
}

void BeTransform::SetPosition(const BeVector3 &inputPosition) {
    position = inputPosition;

    auto *pos = new rp3d::Vector3(inputPosition.GetX(), inputPosition.GetY(),
                                  inputPosition.GetZ());

    transform.setPosition(*pos);
}

BeVector3 BeTransform::GetPosition() const {

    BeVector3 pos = BeVector3(transform.getPosition().x, transform.getPosition().y,
                              transform.getPosition().z);

    return pos;
}

void BeTransform::SetToIdentity() {
    transform.setToIdentity();
    position    = BeVector3(transform.getPosition());
    orientation = BeQuaternion(transform.getOrientation());
}

BeTransform BeTransform::GetInverse() {
    BeTransform result = BeTransform(transform.getInverse());
    return result;
}

BeTransform &BeTransform::operator=(const BeTransform &rhs) {
    orientation = rhs.orientation;
    position    = rhs.position;
    rp3d::Vector3 targetPosition =
        rp3d::Vector3(position.GetX(), position.GetY(), position.GetZ());
    rp3d::Quaternion targetQuaternion =
        rp3d::Quaternion(orientation.GetX(), orientation.GetY(),
                         orientation.GetZ(), orientation.GetW());
    rp3d::Transform target = rp3d::Transform(targetPosition, targetQuaternion);
    transform              = target;
    return *this;
}

BeTransform &BeTransform::operator*(const BeTransform &rhs) {
    BeVector3 posResult = position * rhs.position;
    BeQuaternion quatResult = orientation * rhs.orientation;
    rp3d::Vector3 posTemp = rp3d::Vector3(posResult.GetX(), posResult.GetY(), posResult.GetZ());
    rp3d::Quaternion quatTemp = rp3d::(quatResult.GetX(), quatResult.GetY(), quatResult.GetZ(), quatResult.GetW());
    rp3d::Transform temp = rp3d::Transform(posTemp, quatTemp);
    transform = temp;
    BeTransform result = BeTransform(transform);
    return result;
}