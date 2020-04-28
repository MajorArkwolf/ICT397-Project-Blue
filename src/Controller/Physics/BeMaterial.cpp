#include "BeMaterial.hpp"

BeMaterial::BeMaterial(const BeMaterial &mat) : material(mat.material) {

}

BeMaterial::BeMaterial(const rp3d::Material &mat) : material(mat){

}

void BeMaterial::SetMaterial(rp3d::Material target){
    material = target;
}

BeMaterial::~BeMaterial() {

}

rp3d::Material BeMaterial::GetMaterial() const {
    return material;
}

void BeMaterial::SetBounciness(float bounciness) {
    material.setBounciness(bounciness);
}

BeMaterial &BeMaterial::operator=(const BeMaterial &rhs) {
    if (&rhs == this) {
        return *this;
    }
    material = rhs.material;
    return *this;
}

