#include "BeCollisionBody.hpp"

BeCollisionBody::BeCollisionBody(const BeTransform &targetTransform,
                                 const BeCollisionWorld &targetWorld,
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

    rp3d::CollisionWorld currentWorld = rp3d::CollisionWorld();


    beCollisionBody = rp3d::CollisionBody(currentTransform, targetWorld, targetID);
}
