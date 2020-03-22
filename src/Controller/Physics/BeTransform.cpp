#include "BeTransform.hpp"

BeTransform::BeTransform() {
    orientation = new BeQuaternion(0, 0, 0, 0);
    position    = new BeVector3(0, 0, 0);
}

BeTransform::BeTransform(BeVector3 position, BeQuaternion orientation) {
    orientation = orientation;
    position    = position;

    auto *pos =
        new rp3d::Vector3(position.GetX(), position.GetY(), position.GetZ());
    auto *direction = new rp3d::Quaternion(orientation.GetX(), orientation.GetY(),
                                           orientation.GetZ(), orientation.GetW());
    transform       = new rp3d::Transform(*pos, *direction);

    delete pos;
    delete direction;
}

BeTransform::BeTransform(const BeTransform &inputTransform) {
    position    = inputTransform.position;
    orientation = inputTransform.orientation;

    auto *pos = new rp3d::Vector3(inputTransform.position->GetX(),
                                  inputTransform.position->GetY(),
                                  inputTransform.position->GetZ());

    auto *direction = new rp3d::Quaternion(
        inputTransform.orientation->GetX(), inputTransform.orientation->GetY(),
        inputTransform.orientation->GetZ(), inputTransform.orientation->GetW());

    transform = new rp3d::Transform(*pos, *direction);

    delete pos;
    delete direction;
}

BeTransform::BeTransform(const rp3d::Transform &inputTransform) {
    *transform = inputTransform;
    position = new BeVector3(inputTransform.getPosition().x,
                        inputTransform.getPosition().y,
                        inputTransform.getPosition().z);
    orientation = new BeQuaternion(transform->getOrientation());
}

BeTransform::~BeTransform() {
    delete transform;
}

BeQuaternion BeTransform::GetOrientation() const{
    orientation = new BeQuaternion(transform->getOrientation().x, transform->getOrientation().y,
                   transform->getOrientation().z, transform->getOrientation().w);

    return *orientation;
}

void BeTransform::SetOrientation(BeQuaternion inputOrientation) {
    *orientation = inputOrientation;

    auto *dir =
        new rp3d::Quaternion(inputOrientation.GetX(), inputOrientation.GetY(),
                             inputOrientation.GetZ(), inputOrientation.GetW());

    transform->setOrientation(*dir);
}

void BeTransform::SetPosition(const BeVector3 &inputPosition) {
    *position = inputPosition;

    auto *pos = new rp3d::Vector3(  inputPosition.GetX(),
                                    inputPosition.GetY(),
                                    inputPosition.GetZ());

    transform->setPosition(*pos);
}

BeVector3 BeTransform::GetPosition() const{

    BeVector3 pos =
        BeVector3(transform->getPosition().x,
                           transform->getPosition().y,
                           transform->getPosition().z);

    return pos;
}

void BeTransform::SetToIdentity(){
    transform->setToIdentity();
    position = new BeVector3(transform->getPosition());
    orientation = new BeQuaternion(transform->getOrientation());
}

BeTransform BeTransform::GetInverse() {
    BeTransform result = BeTransform(transform->getInverse());
    return result;
}

