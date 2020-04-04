#include "BeBoxBody.hpp"

void BeBoxBody::CreateBody(glm::vec3 position, glm::quat rotation, BeCollisionWorld *world) {
    rp3d::Vector3 pos = rp3d::Vector3(position.x, position.y, position.z);
    rp3d::Quaternion rot = rp3d::Quaternion(rotation.x, rotation.y,
        rotation.z, rotation.w);
    rp3d::Transform transform = rp3d::Transform(pos, rot);
    body = world->createCollisionBody(transform);
    rp3d::Vector3 extent = rp3d::Vector3(1,1,1);
    shape = new rp3d::BoxShape(extent);
    body->addCollisionShape(shape, transform);
}

