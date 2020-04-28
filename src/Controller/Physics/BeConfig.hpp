#pragma once

#include <reactphysics3d.h>

enum class ShapeType { Box, Height, Sphere, Capsule };

typedef rp3d::BodyType BeBodyType;

struct BeSettings {
    rp3d::WorldSettings beSettings;
};
