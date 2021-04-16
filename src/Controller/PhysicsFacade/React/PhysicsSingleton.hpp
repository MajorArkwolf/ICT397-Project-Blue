#pragma once
#include <reactphysics3d/reactphysics3d.h>

class PhysicsSingleton {
public:
    static PhysicsSingleton& getInstance() {
        static PhysicsSingleton pe;
        return pe;
    }

    ~PhysicsSingleton() = default;
    rp3d::PhysicsCommon& getPhysicsCommon() {
        return physicsCommon;
    }

private:
    PhysicsSingleton() = default;
    rp3d::PhysicsCommon physicsCommon;
};

