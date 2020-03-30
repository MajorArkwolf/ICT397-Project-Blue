#include "BeTransform.hpp"

#include <glm/detail/type_quat.hpp>

BeReact::BeTransform::BeTransform() {
    orientation = BeQuaternion(0, 0, 0, 0);
    position    = BeVector3(0, 0, 0);
}

BeReact::BeTransform::BeTransform(BeVector3 position, BeQuaternion orientation) {
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

BeReact::BeTransform::BeTransform(glm::vec3 position, glm::quat orientation){
    auto *pos =
        new rp3d::Vector3(position.x, position.y, position.z);
    auto *direction = new rp3d::Quaternion(orientation.x, orientation.y,
                                           orientation.z, orientation.w);
    transform       = rp3d::Transform(*pos, *direction);

    delete pos;
    delete direction;
}




BeReact::BeTransform::BeTransform(const BeReact::BeTransform &inputTransform) {
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

BeReact::BeTransform::BeTransform(const rp3d::Transform &inputTransform) {
    transform = inputTransform;
    position =
        BeVector3(inputTransform.getPosition().x, inputTransform.getPosition().y,
                  inputTransform.getPosition().z);
    orientation = BeQuaternion(transform.getOrientation());
}

BeReact::BeTransform::~BeTransform() {}

BeQuaternion BeReact::BeTransform::GetOrientation() {
    orientation =
        BeQuaternion(transform.getOrientation().x, transform.getOrientation().y,
                     transform.getOrientation().z, transform.getOrientation().w);

    return orientation;
}

void BeReact::BeTransform::SetOrientation(BeQuaternion inputOrientation) {
    orientation = inputOrientation;

    auto *dir =
        new rp3d::Quaternion(inputOrientation.GetX(), inputOrientation.GetY(),
                             inputOrientation.GetZ(), inputOrientation.GetW());

    transform.setOrientation(*dir);
}

void BeReact::BeTransform::SetPosition(const BeVector3 &inputPosition) {
    position = inputPosition;

    auto *pos = new rp3d::Vector3(inputPosition.GetX(), inputPosition.GetY(),
                                  inputPosition.GetZ());

    transform.setPosition(*pos);
}

BeVector3 BeReact::BeTransform::GetPosition() const {

    BeVector3 pos = BeVector3(transform.getPosition().x, transform.getPosition().y,
                              transform.getPosition().z);

    return pos;
}

void BeReact::BeTransform::SetToIdentity() {
    transform.setToIdentity();
    position    = BeVector3(transform.getPosition());
    orientation = BeQuaternion(transform.getOrientation());
}

BeReact::BeTransform BeReact::BeTransform::GetInverse() {
    BeTransform result = BeTransform(transform.getInverse());
    return result;
}

BeReact::BeTransform &BeReact::BeTransform::operator=(const BeReact::BeTransform &rhs) {
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

BeReact::BeTransform &BeReact::BeTransform::operator*(const BeReact::BeTransform &rhs) {
    BeVector3 posResult = position * rhs.position;
    BeQuaternion quatResult = orientation * rhs.orientation;
    rp3d::Vector3 posTemp = rp3d::Vector3(posResult.GetX(), posResult.GetY(), posResult.GetZ());
    rp3d::Quaternion quatTemp = rp3d::Quaternion(quatResult.GetX(), quatResult.GetY(), quatResult.GetZ(), quatResult.GetW());
    rp3d::Transform temp = rp3d::Transform(posTemp, quatTemp);
    transform = temp;
    BeTransform result = BeTransform(transform);
    return result;
}