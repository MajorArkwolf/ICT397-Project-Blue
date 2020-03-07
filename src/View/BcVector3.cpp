#include "BcVector3.hpp"

BcVector3::BcVector3(BcFloat x, BcFloat y, BcFloat z) {
    bcVector3 = new btVector3(x, y, z);
}

BcVector3 BcVector3::Cross(BcVector3 rhs) {
    btVector3 temp = rhs;

    return bcVector3->cross((btVector3)rhs);
}