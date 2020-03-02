//
// Created by becky on 1/03/2020.
//

#include "BcVector4.hpp"

BcVector4::BcVector4(BcFloat inputX, BcFloat inputY, BcFloat inputZ,
                     BcFloat inputW) {
    bcVec4 = new btQuadWord(inputX, inputY, inputZ, inputW);
}


void BcVector4::SetX(BcFloat inputX) {
    bcVec4->setX(inputX);
}

void BcVector4::SetY(BcFloat inputY) {
    bcVec4->setY(inputY);
}

void BcVector4::SetZ(BcFloat inputZ) {
    bcVec4->setZ(inputZ);
}

void BcVector4::SetW(BcFloat inputW) {
    bcVec4->setW(inputW);
}

BcFloat BcVector4::GetX() {
    return bcVec4->x();
}

BcFloat BcVector4::GetY() {
    return bcVec4->y();
}

BcFloat BcVector4::GetZ() {
    return bcVec4->z();
}

BcFloat BcVector4::GetW() {
    return bcVec4->w();
}

