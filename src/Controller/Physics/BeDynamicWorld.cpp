#include "BeDynamicWorld.hpp"
#include "BeAbstractPhysics.hpp"

BeDynamicWorld::BeDynamicWorld(){
    bePhysicsWorld = nullptr;
}


BeDynamicWorld::BeDynamicWorld(const glm::vec3 &gravity, const BeSettings &settings) {

    worldGravity = new rp3d::Vector3(gravity.x, gravity.y, gravity.z);
    bePhysicsWorld = new rp3d::DynamicsWorld(*worldGravity);
}

BeDynamicWorld::~BeDynamicWorld(){
    delete worldGravity;
    delete bePhysicsWorld;
}

glm::vec3 BeDynamicWorld::GetGravity() {
    return glm::vec3(worldGravity->x, worldGravity->y, worldGravity->z);
}

bool BeDynamicWorld::TestAABBOverlap(rp3d::RigidBody *body1, rp3d::RigidBody *body2) {


    return bePhysicsWorld->testAABBOverlap(body1, body2);
}


bool BeDynamicWorld::TestAABBOverlap(BeAbstractPhysics *target1,
                                       BeAbstractPhysics *target2) {

    return bePhysicsWorld->testAABBOverlap(target1->GetBody(), target2->GetBody());
}

bool BeDynamicWorld::TestOverLap(rp3d::RigidBody *body1, rp3d::RigidBody *body2) {
    return bePhysicsWorld->testOverlap(body1, body2);
}

bool BeDynamicWorld::TestOverLap(BeAbstractPhysics *target1, BeAbstractPhysics *target2) {

    return bePhysicsWorld->testOverlap(target1->GetBody(), target2->GetBody());
}

rp3d::RigidBody *BeDynamicWorld::CreateRigidBody(rp3d::Transform transform) {
    rp3d::RigidBody *body = bePhysicsWorld->createRigidBody(transform);

    return body;
}

void BeDynamicWorld::DestroyRigidBody(rp3d::RigidBody *body){
    bePhysicsWorld->destroyCollisionBody(body);
}

void BeDynamicWorld::EnableGravity(bool toggle) {
    bePhysicsWorld->setIsGratityEnabled(toggle);
}

void BeDynamicWorld::SetGravity(glm::vec3 gravity) {
    rp3d::Vector3 grav(gravity.x, gravity.y, gravity.z);
    bePhysicsWorld->setGravity(grav);
}

void BeDynamicWorld::EnableSleeping(bool toggle) {
    bePhysicsWorld->enableSleeping(toggle);
}

void BeDynamicWorld::SetSleepLinearVelocity(float velocity) {
    bePhysicsWorld->setSleepLinearVelocity(velocity);
}

void BeDynamicWorld::SetSleepAngularVelocity(float velocity) {
    bePhysicsWorld->setSleepAngularVelocity(velocity);
}

void BeDynamicWorld::SetNumIterationPositionSolver(int iterations) {
    bePhysicsWorld->setNbIterationsPositionSolver(iterations);
}

void BeDynamicWorld::SetNumIterationVelocitySolver(int iterations) {
    bePhysicsWorld->setNbIterationsVelocitySolver(iterations);
}

void BeDynamicWorld::Update(float timeStep) {
    bePhysicsWorld->update(timeStep);
}