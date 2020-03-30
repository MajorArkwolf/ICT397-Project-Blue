#include "BeCollisionWorld.hpp"

BeReact::BeCollisionWorld::BeCollisionWorld() {
    beCollisionWorld = nullptr;
}

BeReact::BeCollisionWorld::BeCollisionWorld(const BeSettings &worldSettings) {
    beConfig         = worldSettings;
    beCollisionWorld = new rp3d::CollisionWorld(worldSettings.beSettings);
}

BeSettings BeReact::BeCollisionWorld::GetConfig() {
    return beConfig;
}

bool BeReact::BeCollisionWorld::TestAABBOverlap(BeCollisionBody *target1,
                                       BeCollisionBody *target2, BeSettings worldSettings) {

    rp3d::Vector3 vec1 =
        rp3d::Vector3(target1.GetTransform()->GetPosition().GetX(),
                      target1.GetTransform()->GetPosition().GetY(),
                      target1.GetTransform()->GetPosition().GetZ());
    rp3d::Quaternion quat1 =
        rp3d::Quaternion(target1.GetTransform()->GetOrientation().GetX(),
                         target1.GetTransform()->GetOrientation().GetY(),
                         target1.GetTransform()->GetOrientation().GetZ(),
                         target1.GetTransform()->GetOrientation().GetW());
    rp3d::Transform transform1 = rp3d::Transform(vec1, quat1);
    rp3d::CollisionWorld world1 = rp3d::CollisionWorld(worldSettings.beSettings);
    rp3d::CollisionBody *body1 = world1.createCollisionBody(transform1);

    rp3d::Vector3 vec2 =
        rp3d::Vector3(target2.GetTransform()->GetPosition().GetX(),
                      target2.GetTransform()->GetPosition().GetY(),
                      target2.GetTransform()->GetPosition().GetZ());
    rp3d::Quaternion quat2 =
        rp3d::Quaternion(target2.GetTransform()->GetOrientation().GetX(),
                         target2.GetTransform()->GetOrientation().GetY(),
                         target2.GetTransform()->GetOrientation().GetZ(),
                         target2.GetTransform()->GetOrientation().GetW());
    rp3d::Transform transform2 = rp3d::Transform(vec2, quat2);
    rp3d::CollisionWorld world2 = rp3d::CollisionWorld(worldSettings.beSettings);
    rp3d::CollisionBody *body2 = world2.createCollisionBody(transform2);

    return beCollisionWorld->testAABBOverlap(body1, body2);
}

bool BeReact::BeCollisionWorld::TestOverLap(BeCollisionBody target1, BeCollisionBody target2, BeSettings worldSettings) {

    rp3d::Vector3 vec1 =
        rp3d::Vector3(target1.GetTransform().GetPosition().GetX(),
                      target1.GetTransform().GetPosition().GetY(),
                      target1.GetTransform().GetPosition().GetZ());
    rp3d::Quaternion quat1 =
        rp3d::Quaternion(target1.GetTransform().GetOrientation().GetX(),
                         target1.GetTransform().GetOrientation().GetY(),
                         target1.GetTransform().GetOrientation().GetZ(),
                         target1.GetTransform().GetOrientation().GetW());
    rp3d::Transform transform1 = rp3d::Transform(vec1, quat1);
    rp3d::CollisionWorld world1 = rp3d::CollisionWorld(worldSettings.beSettings);
    rp3d::CollisionBody *body1 = world1.createCollisionBody(transform1);

    rp3d::Vector3 vec2 =
        rp3d::Vector3(target2.GetTransform().GetPosition().GetX(),
                      target2.GetTransform().GetPosition().GetY(),
                      target2->GetTransform().GetPosition().GetZ());
    rp3d::Quaternion quat2 =
        rp3d::Quaternion(target2.GetTransform().GetOrientation().GetX(),
                         target2.GetTransform().GetOrientation().GetY(),
                         target2.GetTransform().GetOrientation().GetZ(),
                         target2.GetTransform().GetOrientation().GetW());
    rp3d::Transform transform2 = rp3d::Transform(vec2, quat2);
    rp3d::CollisionWorld world2 = rp3d::CollisionWorld(worldSettings.beSettings);
    rp3d::CollisionBody *body2 = world2.createCollisionBody(transform2);

    return beCollisionWorld->testOverlap(body1, body2);
}

