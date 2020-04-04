#include "BeCollisionBody.hpp"

#include "BeCollisionWorld.hpp"

BeCollisionBody::BeCollisionBody() {}

BeCollisionBody::BeCollisionBody(BeTransform targetTransform,
                                 BeCollisionWorld *targetWorld, beBodyId targetID) {

    rp3d::Vector3 pos = rp3d::Vector3(targetTransform.GetPosition().GetX(),
                                      targetTransform.GetPosition().GetY(),
                                      targetTransform.GetPosition().GetY());

    rp3d::Quaternion orient =
        rp3d::Quaternion(targetTransform.GetOrientation().GetX(),
                         targetTransform.GetOrientation().GetY(),
                         targetTransform.GetOrientation().GetZ(),
                         targetTransform.GetOrientation().GetW());

    rp3d::Transform currentTransform = rp3d::Transform(pos, orient);
    world                            = targetWorld;
    rp3d::CollisionWorld currentWorld =
        rp3d::CollisionWorld(targetWorld->GetConfig().beSettings);

    id = targetID;

    collisionBodyRaw = new rp3d::CollisionBody(currentTransform, currentWorld, id);
}

void BeCollisionBody::SetTransform(const BeTransform &targetTransform) {
    transform = targetTransform;
}

BeTransform BeCollisionBody::GetTransform() {
    return transform;
}

BeCollisionWorld *BeCollisionBody::GetWorld() {
    return world;
}

beBodyId BeCollisionBody::GetId() {
    return id;
}
