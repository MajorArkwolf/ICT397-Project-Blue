//
// Created by becky on 26/02/2020.
//

#include "BcQuaternion.hpp"

BcQuaternion::BcQuaternion(BcFloat scalarX, BcFloat scalarY, BcFloat scalarZ, BcFloat scalarW)
{
    bcQuaternion = new btQuaternion(scalarX, scalarY, scalarZ, scalarW);
}

BcQuaternion &BcQuaternion::operator=(btQuaternion rhs) {
    std::swap(*bcQuaternion, rhs);
    return *this;
}

