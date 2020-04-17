#include "BeMaterial.hpp"

BeMaterial::BeMaterial(){
    material = nullptr;
}

BeMaterial::BeMaterial(BeMaterial *mat) {
    material = mat->GetMaterial();
}

BeMaterial::BeMaterial(rp3d::Material mat) {
    material = &mat;
}

void BeMaterial::SetMaterial(rp3d::Material *target){
    material = target;
}

BeMaterial::~BeMaterial() {
    delete material;
}

rp3d::Material *BeMaterial::GetMaterial() const {
    return material;
}

void BeMaterial::SetBounciness(float bounciness) {
    material->setBounciness(bounciness);
}

BeMaterial &BeMaterial::operator=(const BeMaterial &rhs) {
    if (&rhs == this) {
        return *this;
    }
    material = rhs.material;
    return *this;
}

