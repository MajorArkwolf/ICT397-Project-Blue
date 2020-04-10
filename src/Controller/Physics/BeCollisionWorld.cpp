#include "BeCollisionWorld.hpp"

#include "BeAbstractCollision.hpp"

BeCollisionWorld::BeCollisionWorld() {
    beCollisionWorld = nullptr;
}

BeCollisionWorld::BeCollisionWorld(const BeSettings &worldSettings) {

    beConfig         = worldSettings;
    beCollisionWorld = new rp3d::CollisionWorld(worldSettings.beSettings);

}

BeSettings BeCollisionWorld::GetConfig() {
    return beConfig;
}

bool BeCollisionWorld::TestAABBOverlap(rp3d::CollisionBody *body1, rp3d::CollisionBody *body2) {


    return beCollisionWorld->testAABBOverlap(body1, body2);
}


bool BeCollisionWorld::TestAABBOverlap(BeAbstractCollision *target1,
                                       BeAbstractCollision *target2) {

    return beCollisionWorld->testAABBOverlap(target1->GetBody(), target2->GetBody());
}

bool BeCollisionWorld::TestOverLap(rp3d::CollisionBody *body1, rp3d::CollisionBody *body2) {
    return beCollisionWorld->testOverlap(body1, body2);
}

bool BeCollisionWorld::TestOverLap(BeAbstractCollision *target1, BeAbstractCollision *target2) {

    return beCollisionWorld->testOverlap(target1->GetBody(), target2->GetBody());
}

rp3d::CollisionBody *BeCollisionWorld::CreateCollisionBody(rp3d::Transform transform) {
    rp3d::CollisionBody *body = beCollisionWorld->createCollisionBody(transform);

    return body;
}