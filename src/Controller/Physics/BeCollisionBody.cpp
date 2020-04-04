#include "BeCollisionBody.hpp"
#include "BeCollisionWorld.hpp"

BeReact::BeCollisionBody::BeCollisionBody(){

}

BeReact::BeCollisionBody(rp3d::CollisionBody *body) {

}


BeReact::BeCollisionBody::BeCollisionBody(BeTransform targetTransform,
                                 BeReact::BeCollisionWorld *targetWorld,
                                 beBodyId targetID) {

    rp3d::Vector3 pos = rp3d::Vector3(targetTransform.GetPosition().GetX(),
                                      targetTransform.GetPosition().GetY(),
                                      targetTransform.GetPosition().GetY());

    rp3d::Quaternion orient =
        rp3d::Quaternion(targetTransform.GetOrientation().GetX(),
                         targetTransform.GetOrientation().GetY(),
                         targetTransform.GetOrientation().GetZ(),
                         targetTransform.GetOrientation().GetW());

    rp3d::Transform currentTransform = rp3d::Transform(pos, orient);
    world = targetWorld;
    rp3d::CollisionWorld currentWorld = rp3d::CollisionWorld(targetWorld->GetConfig().beSettings);

    id = targetID;

    collisionBodyRaw = new rp3d::CollisionBody(currentTransform, currentWorld, id);
}

void BeReact::BeCollisionBody::SetTransform(const BeTransform &targetTransform) {
    transform = targetTransform;
}

BeReact::BeTransform BeReact::BeCollisionBody::GetTransform() {
    return transform;
}

BeReact::BeCollisionWorld *BeReact::BeCollisionBody::GetWorld() {
    return world;
}

beBodyId BeReact::BeCollisionBody::GetId() {
    return id;
}

